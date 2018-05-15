#include "pch.h"
#include <fstream>
#include "ScopeParseHelper.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ParsingTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(RTTIFunctionsTest)
		{
			Scope scope;
			JsonParseMaster::SharedData* s = new ScopeParseHelper::ScopeSharedData(scope);
			uint64_t id = s->TypeIdClass();
			Assert::IsTrue(s->Is(id));
			Assert::IsTrue(s == s->QueryInterface(id));
			Assert::IsTrue("SharedData" == s->TypeName());
			RTTI* r = s;
			Assert::IsNull(r->RTTI::QueryInterface(0));
			Assert::IsTrue(r->RTTI::ToString() == "RTTI");
			Assert::IsTrue(r->RTTI::Equals(s));
			Assert::IsTrue(id = r->TypeIdInstance());
			Assert::IsTrue(id = ScopeParseHelper::ScopeSharedData::TypeIdClass());
			Assert::IsTrue(r->QueryInterface(ScopeParseHelper::ScopeSharedData::TypeIdClass()) == r);
			Assert::IsTrue(r->Is("ScopeSharedData"));
			Assert::IsFalse(r->Is("waha"));
			Assert::IsNotNull(r->As<ScopeParseHelper::ScopeSharedData>());
			Assert::IsNotNull(r->As<JsonParseMaster::SharedData>());
			Assert::IsTrue("RTTI" == r->ToString());
			delete s;
		}

		TEST_METHOD(ScopeParseTest)
		{
			Scope s;
			Scope s2;
			JsonParseMaster::SharedData* sharedData = new ScopeParseHelper::ScopeSharedData(s);
			JsonParseMaster::SharedData* sharedData1 = new ScopeParseHelper::ScopeSharedData(s2);
			JsonParseMaster master(*sharedData);
			ScopeParseHelper sh;
			master.AddHelper(sh);
			master.Parse(R"({ "Name": {"Type": "String", "Value" : "Player1" } } )");
			Datum ds = *s.Find("Name");
			Assert::IsTrue(ds.Get<std::string>() == "Player1");
			master.ParseFromFile("Script/Scope.json");
			Datum d = *s.Find("Health");
			Assert::AreEqual(100, d.Get<int32_t>());
			Assert::AreEqual(200, d.Get<int32_t>(1U));
			Datum d1 = *s.Find("Power");
			Scope& s1 = d1.Get<Scope>();
			Datum nestedDatum = *s1.Find("MoreNesting");
			Scope& s3 = nestedDatum.Get<Scope>();
			Assert::IsNotNull(s3.Find("Name"));
			Assert::AreEqual(0U, sharedData->Depth());
			Assert::IsNotNull(s1.Find("Name"));
			Datum temp = *s1.Find("Name");
			Assert::IsTrue(temp.Get<std::string>() == "Fireball");
			Datum temp1 = *s1.Find("Damage");
			Assert::IsTrue(temp1.Get<float>() == 10.0f);
			JsonParseMaster* clone = master.Clone();
			clone->SetSharedData(*sharedData1);
			Assert::IsTrue(clone->IsClone());
			clone->ParseFromFile("Script/ScopeClone.json");
			sharedData1->GetJsonParseMaster();
			Datum d2 = *s2.Find("Health");
			Assert::AreEqual(200, d2.Get<int32_t>());
			master.SetSharedData(*sharedData1);
			master.ParseFromFile("Script/Scope.json");
			d = *s2.Find("Health");
			Assert::AreEqual(100, d.Get<int32_t>());
			Assert::IsTrue(master.GetFileName() == "Script/Scope.json");
			Assert::IsTrue(master.GetSharedData() == sharedData1);
			master.RemoveHelper(sh);
			delete clone;
			delete sharedData;
		}


	private:
		static _CrtMemState sStartMemState;
	};
	_CrtMemState ParsingTest::sStartMemState;
}
