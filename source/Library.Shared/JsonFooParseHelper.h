#pragma once
#include "IJsonParseHelper.h"
#include "FooSharedData.h"

namespace FieaGameEngine
{
	//!Concrete parse helper
	class JsonFooParseHelper : public IJsonParseHelper
	{
	public:
		//!Constructor
		JsonFooParseHelper();
		//!Intialize function
		/*!
			Initialize all the data to make it ready for parsing
		*/
		virtual void Initialize() override;
		//!Destructor
		virtual ~JsonFooParseHelper();
		//!DataHandler function
		/*!
			Called during parsing. Checks if the handler can handle the data and if so ,
			Sets the values of the associated shared data class which has been parsed from the json file.
			\param root, the json::value object
			\shared data, a reference to the shared data whose data has to be set
			\return bool, true if the handler handles the data
		*/
		virtual bool DataHandler(Json::Value root, JsonParseMaster::SharedData& sharedData) override;
		//!Clone function
		/*!
			Clone the helper.
		*/
		virtual JsonFooParseHelper* Clone() override;
	private:
		bool mIsClone;
	};
}

