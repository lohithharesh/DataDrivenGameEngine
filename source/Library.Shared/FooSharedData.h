#pragma once
#include "JsonParseMaster.h"
#include "ParseTestFoo.h"
namespace FieaGameEngine
{
	class FooSharedData : public JsonParseMaster::SharedData
	{
		RTTI_DECLARATIONS(FooSharedData, JsonParseMaster::SharedData)
		friend class JsonFooParseHelper;
	public:
		FooSharedData(ParseTestFoo& f);
		virtual FooSharedData* Clone() override;
		virtual void Initialize() override;
		ParseTestFoo* getFooPointer();
		~FooSharedData();
	private:
		ParseTestFoo* foo;
	};

}