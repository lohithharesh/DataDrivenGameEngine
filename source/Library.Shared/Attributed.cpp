#include "pch.h"
#include "Attributed.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(Attributed);

Attributed::Attributed(uint64_t id)
{
	RTTI* temp = this;
	Append("this") = temp;
	mTypeId = id;
	populate(id);
}

Attributed::Attributed(Attributed&& rhs)
{
	operator=(std::move(rhs));
}

Attributed& Attributed::operator=(Attributed&& rhs)
{
	if (this != &rhs)
	{
		Scope::operator=(std::move(rhs));
		mTypeId = std::move(rhs.mTypeId);
		(*this)["this"] = static_cast<RTTI*>(this);
		UpdateSignatures(mTypeId);
	}
	return *this;
}

Attributed::Attributed(const Attributed& rhs)
{
	operator=(rhs);
}

Attributed& Attributed::operator=(const Attributed& rhs)
{
	if (this != &rhs)
	{
		Scope::operator=(rhs);
		mTypeId = std::move(rhs.mTypeId);
		(*this)["this"] = static_cast<RTTI*>(this);
		UpdateSignatures(mTypeId);
	}
	return *this;
}

bool Attributed::IsAttribute(const std::string& key) const
{
	return (Find(key) != nullptr);
}

bool Attributed::IsPrescribed(const std::string& key) const
{
	if (key == "this")
	{
		return true;
	}
	auto signatures = AttributedTypeManager::GetSignatures(mTypeId);
	for (auto signature : signatures)
	{
		if (signature.mName == key)
		{
			return true;
		}
	}
	return false;
}

bool Attributed::IsAuxillary(const std::string& key) const
{
	return (IsAttribute(key) && !IsPrescribed(key));
}

Datum& Attributed::AppendAuxillaryAttribute(const std::string& key)
{
	if (IsPrescribed(key))
	{
		throw std::exception("It is a prescribed attribute");
	}
	return Append(key);
}

const Vector<std::string> Attributed::Attributes() const
{
	const Vector<ScopePairType*>& orderedVector = this->GetOrderedVector();
	uint32_t size = orderedVector.Size();
	Vector<std::string> temp(size);
	for (const auto& data : orderedVector)
	{
		temp.PushBack(data->first);
	}
	return temp;
}

const Vector<std::string> Attributed::Prescribed() const
{
	const Vector<ScopePairType*>& orderedVector = this->GetOrderedVector();
	uint32_t size = orderedVector.Size();
	Vector<std::string> temp(size);
	for (const auto& data : orderedVector)
	{
		if (IsPrescribed(data->first))
		{
			temp.PushBack(data->first);
		}
	}
	return temp;
}

const Vector<std::string> Attributed::Auxillary() const
{
	const Vector<ScopePairType*>& orderedVector = this->GetOrderedVector();
	uint32_t size = orderedVector.Size();
	Vector<std::string> temp(size);
	for (const auto& data : orderedVector)
	{
		if (IsAuxillary(data->first))
		{
			temp.PushBack(data->first);
		}
	}
	return temp;
}


void Attributed::populate(uint64_t typeId)
{
	auto Signatures = AttributedTypeManager::GetSignatures(typeId);
	for (auto signature : Signatures)
	{
		if (signature.mName != "this")
		{
			Datum& datum = Append(signature.mName);
			datum.SetType(signature.mType);
			if (signature.mType != DatumTypeEnum::Table)
			{
				void* data = reinterpret_cast<uint8_t*>(this) + signature.mOffset;
				datum.SetStorage(data, signature.mSize);
			}
		}
	}
}

void Attributed::UpdateSignatures(uint64_t typeId)
{
	auto Signatures = AttributedTypeManager::GetSignatures(typeId);
	for (auto signature : Signatures)
	{
		if (signature.mName != "this" && signature.mType != DatumTypeEnum::Table)
		{
			Datum& datum = *Find(signature.mName);
			void* data = reinterpret_cast<uint8_t*>(this) + signature.mOffset;
			datum.SetStorage(data, signature.mSize);
		}
	}
}

Scope* Attributed::Clone(const Scope& rhs)
{
	return new Attributed(*(rhs.As<Attributed>()));
}

const Vector<std::pair<std::string, Datum>*> Attributed::AuxillaryPairs() const
{
	const Vector<ScopePairType*>& orderedVector = this->GetOrderedVector();
	uint32_t size = orderedVector.Size();
	Vector<ScopePairType*> temp(size);
	for (const auto& data : orderedVector)
	{
		if (IsAuxillary(data->first))
		{
			temp.PushBack(data);
		}
	}
	return temp;
}