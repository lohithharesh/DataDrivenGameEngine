#include "pch.h"
#include "JsonParseMaster.h"
#include "IJsonParseHelper.h"
#include <fstream>

using namespace FieaGameEngine;
using SharedData = JsonParseMaster::SharedData;

RTTI_DEFINITIONS(SharedData)

JsonParseMaster::JsonParseMaster(SharedData& sharedData) : mSharedData(&sharedData), mIsClone(false),
mHelperList(2)
{
	mSharedData->SetJsonParseMaster(*this);
}

JsonParseMaster* JsonParseMaster::Clone()
{
	JsonParseMaster* newMaster = new JsonParseMaster(*mSharedData->Clone());
	newMaster->mSharedData->SetJsonParseMaster(*newMaster);
	newMaster->mIsClone = true;
	newMaster->mFilePath = mFilePath;
	Vector<IJsonParseHelper*> newHelperList(mHelperList.Size());
	for (const auto& helper : mHelperList)
	{
		newHelperList.PushBack(helper->Clone());
	}
	newMaster->mHelperList = newHelperList;
	return newMaster;
}

void JsonParseMaster::AddHelper(IJsonParseHelper& helper)
{
	if (!mIsClone)
	{
		if (mHelperList.Find(&helper) == mHelperList.end())
		{
			mHelperList.PushBack(&helper);
		}
	}
}

void JsonParseMaster::RemoveHelper(IJsonParseHelper& helper)
{
	if (!mIsClone)
	{
		mHelperList.Remove(&helper);
	}
}

void JsonParseMaster::Parse(std::istream& stream)
{
	Reset();
	Json::Value root;
	stream >> root;
	HandleData(root);
}

void JsonParseMaster::ParseFromFile(const std::string& filePath)
{
	if (!filePath.empty())
	{
		std::ifstream inFile(filePath, std::ifstream::binary);
		if (!inFile.fail())
		{
		
			mFilePath = filePath;
			Parse(inFile);
			inFile.close();
		}
	}
}

void JsonParseMaster::Parse(const std::string& jsonString)
{
	if (!jsonString.empty())
	{
		std::stringstream jsonStream;
		jsonStream << jsonString;
		Parse(jsonStream);
	}
}

void JsonParseMaster::HandleData(const Json::Value& value)
{
	std::vector<std::string> memberList = value.getMemberNames();
	for (auto& member : memberList)
	{
		Json::Value temp = value[member];
		if (temp.isObject())
		{
			
			for (auto& helper : mHelperList)
			{
				if (helper->StartHandler(temp, member, *mSharedData))
				{
					mSharedData->IncrementDepth();
					break;
				}
			}
			HandleData(temp);

			for (auto& helper : mHelperList)
			{
				if (helper->EndHandler(member, *mSharedData))
				{
					mSharedData->DecrementDepth();
					break;
				}
			}	
		}

		else
		{
			for (auto& helper : mHelperList)
			{
				if (helper->DataHandler(temp, member, *mSharedData))
				{
					break;
				}
			}
		}
	}
}


const std::string& JsonParseMaster::GetFileName() const
{
	return mFilePath;
}


SharedData* JsonParseMaster::GetSharedData()
{
	return mSharedData;
}

void JsonParseMaster::SetSharedData(SharedData& sharedData)
{
	if (mIsClone)
	{
		delete mSharedData;
	}
	mSharedData = &sharedData;
}



bool JsonParseMaster::IsClone() const
{
	return mIsClone;
}

void JsonParseMaster::Reset()
{
 	mSharedData->Initialize();
	for (const auto& helper : mHelperList)
	{
		helper->Initialize();
	}
}
JsonParseMaster::~JsonParseMaster()
{
	if (mIsClone)
	{
		delete mSharedData;
		for (const auto& helper : mHelperList)
		{
			delete helper;
		}
	}
}

SharedData::SharedData() : mDepth(0)
{

}


void SharedData::SetJsonParseMaster(JsonParseMaster& master)
{
	mMaster = &master;
}

JsonParseMaster* SharedData::GetJsonParseMaster() const
{
	return mMaster;
}

void SharedData::IncrementDepth()
{
	mDepth++;
}

void SharedData::DecrementDepth()
{
	mDepth--;
}

uint32_t SharedData::Depth() const
{
	return mDepth;
}

void SharedData::Initialize()
{
	mDepth = 0;
}