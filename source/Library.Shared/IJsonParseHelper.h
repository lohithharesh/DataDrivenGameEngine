#pragma once
#include "JsonParseMaster.h"
namespace FieaGameEngine {
	//!Abstract class for the helpers.
	class IJsonParseHelper
	{
	public:
		//!Initialize function
		virtual void Initialize() = 0;
		//!start handler function that is called during parse at the start of each element.
		virtual bool StartHandler(const Json::Value& value, const std::string& key, JsonParseMaster::SharedData& sharedData) = 0;
		//!Data handler function that is called during parse to handle the data being parsed.
		virtual bool DataHandler(const Json::Value& value, const std::string& key, JsonParseMaster::SharedData& sharedData) = 0;
		//!End handler function that is called during parse when an element has been parsed fully.
		virtual bool EndHandler(const std::string& key, JsonParseMaster::SharedData& sharedData) = 0;
		//!clone function
		virtual IJsonParseHelper* Clone() = 0;
		//!Destructor
		virtual ~IJsonParseHelper() = default;
	};

}