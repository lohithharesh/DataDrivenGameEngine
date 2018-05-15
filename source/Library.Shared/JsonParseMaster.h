#pragma once
#include "RTTI.h"
#include "json\json.h"
#include "Vector.h"
namespace FieaGameEngine
{
	//Forward Declare the Abstract helper Class
	class IJsonParseHelper;
	//!Parse Master class
	class JsonParseMaster final
	{
	public:
		//!Abstract Shared Data Base class
		/*!
			This class will represent data that all helpers share with each other and with the master parser.
			This is a base class.
		*/
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)
		public:
			//!Default Constructor
			SharedData();
			//!Clone function
			/*!
				“virtual constructor” which returns the address of a SharedData object
				which has the same internal state as “this” except ready for a fresh file.
				\return a shareddata pointer to the clone
			*/
			virtual SharedData* Clone() = 0;
			//!SetJsonParseMaster function
			/*!
				set the parse master that is associated with the shared data
				\return a const reference to the jsonparsemaster
			*/
			void SetJsonParseMaster(JsonParseMaster& master);
			//!GetJsonParseMaster function
			/*!
				Get the parse master that is associated with the shared data
				\return a pointer to the JsonParseMaster
			*/
			JsonParseMaster* GetJsonParseMaster() const;
			//!IncrementDepth Function
			/*!
				increment a “nesting depth” counter. This gets incremented upon the start of each element.
			*/
			void IncrementDepth();
			//!DecrementDepth Function
			/*!
				decrement a “nesting depth” counter. This gets decremented upon the end of each element.
			*/
			void DecrementDepth();
			//!Initialize Function
			/*!
				Called before each parse. Initialize any data necessary for the parsing
			*/
			virtual void Initialize();
			//!Depth function
			/*!
				return the current nesting depth.
				\return a uint32_t which is the current depth
			*/
			uint32_t Depth() const;
		private:
			uint32_t mDepth;
			JsonParseMaster* mMaster;
		};

		//!Parameterized Constructor
		/*!
			\parameter shared data reference
		*/
		JsonParseMaster(SharedData& sharedData);
		//!Clone Function
		/*!
			duplicate this object and return its address
			\return a jsonparsemaster pointer to the cloned object.
		*/
		JsonParseMaster* Clone();
		//!AddHelper function
		/*!
			Add a concrete parse helper to the master.
			\parameter helper, a reference to the helper
		*/
		void AddHelper(IJsonParseHelper& helper);
		//!RemoveHelper function
		/*!
			Remove a concrete parse helper From the master.
			\parameter helper, a reference to the helper
		*/
		void RemoveHelper(IJsonParseHelper& helper);
		//!ParseFromFile function
		/*!
			given the file path, parse the json file and fill up the corresponding shared data.
			\parameter filePath, a const string reference to the filepath
		*/
		void ParseFromFile(const std::string& filePath);
		//!GetFileName function
		/*!
			returns the filename of the current file being parsed
			\return a const string reference to the file name
		*/
		const std::string& GetFileName() const;
		//!GetSharedData function
		/*!
			Return the sharedData associated with this master
			\return a sharedData pointer
		*/
		SharedData* GetSharedData();
		//!SetSharedData function
		/*!
			Set the sharedData associated with the master
			\parameter a shareddata reference s
		*/
		void SetSharedData(SharedData& sharedData);
		//!Parse function
		/*!
			Given the json string, parse the json string and fill up the corresponding shared data.
			\parameter jsonString, a const string reference to the json string
		*/
		void Parse(const std::string& jsonString);
		//!IsClone function
		/*!
			returns true if the master is a clone
			\return bool, true if it is a clone.
		*/
		bool IsClone() const;
		//!Reset Method
		/*!
			Called before each parse. Sets the master and all its helpers to its default state and
			makes them ready to parse.
		*/
		void Reset();
		//!Destructor
		~JsonParseMaster();
	private:
		void Parse(std::istream& stream);
		void HandleData(const Json::Value& value);
		bool mIsClone;
		SharedData* mSharedData;
		Vector<IJsonParseHelper*> mHelperList;
		std::string mFilePath;
	};
}
