#include "pch.h"
#include "Scope.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(Scope);

Scope::Scope(uint32_t size) : mTableMap(10), mOrderedVector(size), mParent(nullptr)
{

}

Scope::Scope(const Scope& rhs) : Scope()
{
	operator=(rhs);
}

Scope::Scope(Scope&& rhs)
{
	operator=(std::move(rhs));
}

Scope& Scope::operator=(Scope&& rhs)
{
	if (this != &rhs)
	{
		Clear();
		mOrderedVector = std::move(rhs.mOrderedVector);
		mTableMap = std::move(rhs.mTableMap);
		mParent = std::move(rhs.mParent);
		if (mParent != nullptr)
		{
			Datum* d = nullptr;
			uint32_t index = 0;
			mParent->FindName(rhs, d, index);
			d->Set(this, index);
			rhs.mParent = nullptr;
		}
		uint32_t size = mOrderedVector.Size();
		for (uint32_t i = 0; i < size; i++)
		{
			Datum& datum = mOrderedVector[i]->second;
			if (datum.Type() == DatumTypeEnum::Table)
			{
				for (uint32_t j = 0; j < datum.Size(); j++)
				{
					datum[j].mParent = this;
				}
			}
		}
	}
	return *this;
}

Scope& Scope::operator=(const Scope& rhs)
{
	if (this != &rhs)
	{
		Clear();
		mParent = nullptr;
		mOrderedVector.Reserve(rhs.mOrderedVector.Size());
		for (auto& value : rhs.mOrderedVector)
		{
			if (value->second.Type() == DatumTypeEnum::Table)
			{
				for (uint32_t i = 0; i < value->second.Size(); i++)
				{
					Scope* temp = Clone(value->second.Get<Scope>(i));
					Adopt(*temp, value->first);
				}
			}
			else
			{
				Append(value->first) = value->second;
			}
		}
	}
	return *this;
}

Datum* Scope::Find(const std::string& key) const
{
	auto it = mTableMap.Find(key);
	if (it != mTableMap.end())
	{
		return &it->second;
	}
	return nullptr;
}

Datum& Scope::Append(const std::string& key, bool& wasInserted)
{
	if (key.empty())
	{
		throw std::exception("Cannot have empty string as a key");
	}
	auto it = mTableMap.Insert(std::make_pair(key, Datum()), wasInserted);
	if (wasInserted)
	{
		mOrderedVector.PushBack(&(*it));
	}
	return it->second;
}

Datum& Scope::Append(const std::string& key)
{
	bool wasInserted;
	return Append(key, wasInserted);
}

Scope& Scope::AppendScope(const std::string& key)
{
	Datum& temp = Append(key);
	if (temp.Type() != DatumTypeEnum::Unknown && temp.Type() != DatumTypeEnum::Table)
	{
		throw std::exception("Datum for the corresponding type is not a scope type");
	}
	Scope* tempScope = new Scope();
	tempScope->mParent = this;
	temp.PushBack(tempScope);
	return *tempScope;
}

Datum& Scope::operator[](const std::string& key)
{
	return Append(key);
}

Datum& Scope::operator[](uint32_t index)
{
	return mOrderedVector[index]->second;
}

std::string Scope::Orphan(Scope& child)
{
	if (child.mParent != this)
	{
		throw std::exception("wrong parent");
	}
	uint32_t index;
	Datum *datum = nullptr;
	std::string name = FindName(child, datum, index);
	if (!name.empty())
	{
		(*datum).RemoveAtIndex(index);
		child.mParent = nullptr;
	}
	return name;
}

void Scope::Adopt(Scope& child, const std::string& key)
{
	if (&child == this)
	{
		throw std::exception("cannot adopt yourself -_-");
	}
	bool wasInserted;
	Datum& d = Append(key, wasInserted);
	if (wasInserted)
	{
		if (d.Type() != DatumTypeEnum::Unknown && d.Type() != DatumTypeEnum::Table)
		{
			throw std::exception("wrong datum type");
		}
	}
	if (child.mParent != nullptr)
	{
		child.mParent->Orphan(child);
	}
	child.mParent = this;
	d.PushBack(&child);
}

bool Scope::operator==(const Scope& rhs) const
{
	uint32_t size = mOrderedVector.Size();
	uint32_t rhsSize = rhs.mOrderedVector.Size();
	if (size != rhsSize)
	{
		return false;
	}
	for (const auto& temp : mOrderedVector)
	{
		Datum& lhsDatum = temp->second;
		Datum rhsDatum;
		rhs.mTableMap.ContainsKey(temp->first, rhsDatum);
		if (lhsDatum != rhsDatum)
		{
			return false;
		}
	}
	return true;


}

bool Scope::operator!=(const Scope& rhs) const
{
	return !operator==(rhs);
}

std::string Scope::FindName(const Scope& value) const
{
	Datum* uselessDatum;
	uint32_t index;
	return FindName(value, uselessDatum, index);
}

std::string Scope::FindName(const Scope& value, Datum*& datumRef, uint32_t& index) const
{
	uint32_t size = mOrderedVector.Size();
	for (uint32_t i = 0; i < size; i++)
	{
		datumRef = &mOrderedVector[i]->second;
		if (datumRef->Type() == DatumTypeEnum::Table)
		{
			for (uint32_t j = 0; j < datumRef->Size(); j++)
			{
				if (&datumRef->Get<Scope>(j) == &value)
				{
					index = j;
					return mOrderedVector[i]->first;
				}
			}
		}
	}
	return std::string();
}

void Scope::Clear()
{
	uint32_t size = mOrderedVector.Size();
	for (uint32_t index = 0; index < size; index++)
	{
		Datum& datum = mOrderedVector[index]->second;
		if (datum.Type() == DatumTypeEnum::Table)
		{
			for (uint32_t i = 0; i < datum.Size(); i++)
			{
				Scope& temp = datum.Get<Scope>(i);
				temp.mParent = nullptr;
				delete &temp;
			}
		}
	}
	mOrderedVector.Clear();
	mTableMap.Clear();
}

Scope::~Scope()
{
	Clear();
	if (mParent != nullptr)
	{
		mParent->Orphan(*this);
	}
}

Scope* Scope::GetParent() const
{
	return mParent;
}

Datum* Scope::Search(const std::string& key, Scope*& foundScope) const
{
	Datum* temp = Find(key);
	if (temp == nullptr)
	{
		if (mParent != nullptr)
		{
			temp = mParent->Search(key, foundScope);
		}
	}
	else
	{
		foundScope = const_cast<Scope*>(this);
	}
	return temp;
}

Datum* Scope::Search(const std::string& key) const
{
	Scope* uselessScope;
	return Search(key, uselessScope);
}

std::string Scope::ToString() const
{
	return mOrderedVector.Size() > 0 ? mOrderedVector[0]->first : std::string();
}

bool Scope::Equals(const RTTI* rhs) const
{
	Scope* temp = rhs->As<Scope>();
	if (temp != nullptr)
	{
		return operator==(*temp);
	}
	return false;
}

const Vector<Scope::ScopePairType*>& Scope::GetOrderedVector() const
{
	return mOrderedVector;
}

Scope* Scope::Clone(const Scope& rhs)
{
	return new Scope(rhs);
}