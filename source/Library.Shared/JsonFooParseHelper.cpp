#include "pch.h"
#include "JsonFooParseHelper.h"
#include "FooSharedData.h"

using namespace FieaGameEngine;

JsonFooParseHelper::JsonFooParseHelper()
{

}

void JsonFooParseHelper::Initialize()
{
	
}

bool JsonFooParseHelper::DataHandler(Json::Value root, JsonParseMaster::SharedData& sharedData)
{
	FooSharedData* mSharedData = sharedData.As<FooSharedData>();
	if (mSharedData == nullptr)
	{
		return false;
	}
	Json::Value foo = root["Foo"];
	mSharedData->foo->mName = foo.get("Name", "").asString();
	mSharedData->foo->mHealth = foo.get("Health", 0).asInt();
	return true;
}

 JsonFooParseHelper* JsonFooParseHelper::Clone()
{
	 JsonFooParseHelper* newHelper = new JsonFooParseHelper();
	 newHelper->mIsClone = true;
	 return newHelper;
}


JsonFooParseHelper::~JsonFooParseHelper()
{

}
