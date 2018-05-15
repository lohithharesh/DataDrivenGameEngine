#include "pch.h"
#include "ScopeParseHelper.h"
#include "World.h"
#include "ActionListIf.h"

using namespace FieaGameEngine;
using ScopeSharedData = ScopeParseHelper::ScopeSharedData;

RTTI_DEFINITIONS(ScopeParseHelper::ScopeSharedData);

void SetIntegerDatum(const Json::Value& value, uint32_t index, Datum& datum)
{
	datum.Set(value.asInt(), index);
}

void SetFloatDatum(const Json::Value& value, uint32_t index, Datum& datum)
{
	datum.Set(value.asFloat(), index);
}

void SetStringDatum(const Json::Value& value, uint32_t index, Datum& datum)
{
	datum.SetFromString(value.asString(), index);
}

void(*SetDatum[])(const Json::Value& value, uint32_t index, Datum& datum) = { SetIntegerDatum, SetIntegerDatum, SetFloatDatum, SetStringDatum, SetStringDatum, SetStringDatum, SetStringDatum };

ScopeSharedData::ScopeSharedData(Scope& scope) : SharedData(), mScopePointer(&scope)
{

}

void ScopeSharedData::Initialize()
{
	SharedData::Initialize();
}

ScopeSharedData* ScopeSharedData::Clone()
{
	ScopeSharedData* s = new ScopeSharedData(*mScopePointer);
	return s;
}

ScopeParseHelper::ScopeParseHelper() : mStack()
{

}

void ScopeParseHelper::Initialize()
{

}

bool ScopeParseHelper::StartHandler(const Json::Value& value, const std::string& key, JsonParseMaster::SharedData& sharedData)
{
	ScopeSharedData* mSharedData = sharedData.As<ScopeSharedData>();
	if (mSharedData == nullptr)
	{
		return false;
	}
	if (key == "Value")
	{
		return true;
	}
	if (value["Value"].isObject())
	{
		std::string type = value["Type"].asString();
		if (type == "Scope")
		{
			mSharedData->mScopePointer = &mSharedData->mScopePointer->AppendScope(key);
		}

		else if (type == "Sector")
		{
			assert(mSharedData->mScopePointer->Is(World::TypeName()));
			World* world = static_cast<World*>(mSharedData->mScopePointer);
			mSharedData->mScopePointer = world->CreateSector(key);
		}

		else if (type == "Entity")
		{
			assert(mSharedData->mScopePointer->Is(Sector::TypeName()));
			Sector* sector = static_cast<Sector*>(mSharedData->mScopePointer);
			mSharedData->mScopePointer = sector->CreateEntity(value["ClassName"].asString(), key);
		}

		else if (type == "Action")
		{
			assert(mSharedData->mScopePointer->Is(Entity::TypeName()) || mSharedData->mScopePointer->Is(ActionList::TypeName()));
			ActionList* action = mSharedData->mScopePointer->As<ActionList>();
			if (action != nullptr)
			{
				mSharedData->mScopePointer = action->CreateAction(value["ClassName"].asString(), key);
			}
			else
			{
				Entity* entity = static_cast<Entity*>(mSharedData->mScopePointer);
				mSharedData->mScopePointer = entity->CreateAction(value["ClassName"].asString(), key);
			}
		}

		else if (type == "ActionIf" || type == "ActionElse")
		{
			assert(mSharedData->mScopePointer->Is(ActionListIf::TypeName()));
			ActionListIf* action = static_cast<ActionListIf*>(mSharedData->mScopePointer);
			mSharedData->mScopePointer = action->CreateAction(value["ClassName"].asString(), key, type);
		}

		else if (type == "Reaction")
		{
			assert(mSharedData->mScopePointer->Is(World::TypeName()));
			World* world = static_cast<World*>(mSharedData->mScopePointer);
			mSharedData->mScopePointer = world->CreateReaction(value["ClassName"].asString(), key);
		}
		mStack.push(key);
	}
	mElement.mName = key;
	return true;
}

bool ScopeParseHelper::DataHandler(const Json::Value& value, const std::string& key, JsonParseMaster::SharedData& sharedData)
{
	ScopeSharedData* mSharedData = sharedData.As<ScopeSharedData>();
	if (mSharedData == nullptr)
	{
		return false;
	}
	if (key == "Type")
	{
		mElement.mType = mTypeMap[value.asString()];
	}

	else if (key == "Value")
	{
		mElement.mValue = value;
	}
	return true;
}

bool ScopeParseHelper::EndHandler(const std::string& key, JsonParseMaster::SharedData& sharedData)
{
	ScopeSharedData* mSharedData = sharedData.As<ScopeSharedData>();
	if (mSharedData == nullptr)
	{
		return false;
	}
	if (key != "Value")
	{
		if (!mStack.empty() && key == mStack.top())
		{
			mStack.pop();
			mSharedData->mScopePointer = mSharedData->mScopePointer->GetParent();
			return true;
		}
		Datum& d = mSharedData->mScopePointer->Append(mElement.mName);
		if (d.Type() == DatumTypeEnum::Unknown)
		{
			d.SetType(mElement.mType);
		}
		if (mElement.mValue.isArray())
		{
			uint32_t size = mElement.mValue.size();
			if (d.IsInternal())
			{
				d.Resize(size);
			}
			for (uint32_t i = 0; i < size; i++)
			{
				SetDatum[static_cast<int>(d.Type())](mElement.mValue[i], i, d);
			}
		}
		else
		{
			if (d.IsInternal())
			{
				d.Resize(1);
			}
			SetDatum[static_cast<int>(d.Type())](mElement.mValue, 0, d);
		}
	}
	return true;
}

ScopeParseHelper* ScopeParseHelper::Clone()
{
	ScopeParseHelper* s = new ScopeParseHelper();
	s->mIsClone = true;
	return s;
}

ScopeParseHelper::~ScopeParseHelper()
{

}

inline bool isOperator(const std::string & s)
{
	return (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/' || s[0] == '%');
}

std::string ScopeParseHelper::StringToRPN(const std::string& expression)
{
	std::stack<std::string> operatorStack;
	std::string rpnString;
	std::string temp;
	Vector<std::string> tokens;
	size_t i = 0;
	auto pos = expression.find(' ');
	while (pos != std::string::npos)
	{
		tokens.PushBack(expression.substr(i, pos - i));
		i = ++pos;
		pos = expression.find(' ', pos);

		if (pos == std::string::npos)
		{
			tokens.PushBack(expression.substr(i, expression.length()));
		}
	}
	Vector<std::string> output;
	for (auto token : tokens)
	{
		if (token == ")")
		{
			while(operatorStack.top() != "(")
			{
				output.PushBack(operatorStack.top());
				operatorStack.pop();
			}
			operatorStack.pop();
		}
		else if (token == "(")
		{
			operatorStack.push(token);
		}
		else if (!isOperator(token))
		{
			output.PushBack(token);
		}
		else if (operatorStack.empty())
		{
			operatorStack.push(token);
		}
		else
		{
			while (!operatorStack.empty() && mOperatorPrecedenceMap[token] <= mOperatorPrecedenceMap[operatorStack.top()])
			{
				output.PushBack(operatorStack.top());
				operatorStack.pop();
			}
			operatorStack.push(token);
		}
	}
	while (!operatorStack.empty())
	{
		output.PushBack(operatorStack.top());
		operatorStack.pop();
	}

	uint32_t size = 0;
	for (auto token : output)
	{
		size++;
		rpnString.append(token);
		if (size < output.Size())
		{
			rpnString.append(" ");
		}
	}
	return rpnString;
}
