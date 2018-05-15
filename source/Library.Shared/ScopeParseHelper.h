#pragma once
#include "IJsonParseHelper.h"
#include "Scope.h"

namespace FieaGameEngine
{
	//!Concrete helper to parse a scope from json file.
	class ScopeParseHelper final : public IJsonParseHelper
	{
	public:
		//!Shared data class that contains a pointer to the scope we r currently populating
		class ScopeSharedData : public JsonParseMaster::SharedData
		{
			//RTTI declarations to make this a rtti type
			RTTI_DECLARATIONS(ScopeSharedData, JsonParseMaster::SharedData)
				//!Make the helper friend so it can access private members
				friend ScopeParseHelper;
		public:
			//!Parameterised constructor
			/*!
				\param Scope reference to the scope it has to point to
			*/
			ScopeSharedData(Scope& scope);
			//!Clone function
			/*!
				override the clone function to make a clone of this shared data
			*/
			virtual ScopeSharedData* Clone() override;
			//!Intialize function
			/*!
				Intialize the data necessary for the sharedata to parse the data.
			*/
			virtual void Initialize() override;
			//!Desctuctor
			~ScopeSharedData() = default;
		private:
			Scope * mScopePointer;
		};

		//!Constructor
		ScopeParseHelper();
		//!Intialize function
		/*!
			intialize the necessary data so the Helper is ready to parse the file.
			called before each parse.
		*/
		virtual void Initialize() override;
		//!Data Handler function
		/*!
			called to handle the json data. Populates the element structure based on the value
			that is passed.
			\param value, a json::value reference
			\key, a string of the key that is being parsed currently
			\sharedData, a reference to the shareddata that is being currently populated
		*/
		virtual bool DataHandler(const Json::Value& value, const std::string& key, JsonParseMaster::SharedData& sharedData) override;
		//!Start Handler function
		/*!
			Called at the start of each element in the json file. Stores the name of the element in the struct.
			If it is a nested scope, calls append scope.
			\param value, a json::value reference
			\key, a string of the key that is being parsed currently
			\sharedData, a reference to the shareddata that is being currently populated
		*/
		virtual bool StartHandler(const Json::Value& value, const std::string& key, JsonParseMaster::SharedData& sharedData) override;
		//!End Handler function
		/*!
			Called at the end of each element. creates a datum and adds it to scope based on
			the data stored in the element struct.
			\key, a string of the key that is being parsed currently
			\sharedData, a reference to the shareddata that is being currently populated
		*/
		virtual bool EndHandler(const std::string& key, JsonParseMaster::SharedData& sharedData) override;
		//!Clone function
		/*!
			override the clone function so we can create a clone of this helper.
		*/
		virtual ScopeParseHelper* Clone() override;
		~ScopeParseHelper();
		std::string StringToRPN(const std::string& expression);
		
	private:
		bool mIsClone = false;
		struct Element {
			std::string mName;
			DatumTypeEnum mType;
			Json::Value mValue;
		};
		Element mElement;
		HashMap<std::string, DatumTypeEnum> mTypeMap = { {"Unknown", DatumTypeEnum::Unknown}, {"Integer", DatumTypeEnum::Integer}, {"Float", DatumTypeEnum::Float} , {"String", DatumTypeEnum::String}, {"Vector", DatumTypeEnum::Vector}, {"Matrix", DatumTypeEnum::Matrix}, {"RTTI", DatumTypeEnum::RTTI}, {"Table", DatumTypeEnum::Table} };
		std::stack<std::string> mStack;
		
		HashMap<std::string, int32_t> mOperatorPrecedenceMap = { {"+" , 0 }, {"-" , 0}, {"*" , 1}, {"/" , 1 }, {"(", -1}, {"%", 1} };
	};
}

