#include "pch.h"
#include "Foo.h"
#include "Scope.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace glm;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ScopeTest)
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

		TEST_METHOD(DefaultConstructorTest)
		{
			Scope s;
			Datum d = 10;
			s["First"] = d;
			Assert::IsTrue(d == *s.Find("First"));
			auto e = [&s] {s.Adopt(s, "lel"); };
			Assert::ExpectException<std::exception>(e);
			Scope* ns = new Scope();
			Datum &d1 = ns->Append("Float");
			d1.SetType(DatumTypeEnum::Float);
			d1 = 5.5f;
			Assert::IsTrue(d1 == *ns->Find("Float"));
			(*ns)["Float"].PushBack(10.0f);
			Assert::IsTrue((*ns)["Float"].Get<float>(1) == 10.0f);
			s.Adopt(*ns, "Scope");
			Assert::IsTrue("Scope" == s.FindName(*ns));
			Datum& d2 = s.Find("Scope")->Get<Scope>().Append("Int");
			d2.PushBack(5);
			Assert::AreEqual(5, ns->Find("Int")->Get<int32_t>());
			Scope* s2;
			Datum* d3 = s.Search("Scope", s2);
			Assert::IsTrue(d3 == s.Find("Scope"));
			Assert::IsTrue(&s == s2);
			Assert::IsTrue(s[0U] == d);
			d3 = ns->Search("Scope", s2);
			Assert::IsTrue(s2 == &s);
		}

		TEST_METHOD(ScopeAssignmentTest)
		{
			Scope *S1 = new Scope();
			S1->Append("Health") = 100;
			Assert::IsTrue((*S1)[0] == 100);
			S1->Append("Position") = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			Assert::IsTrue((*S1)[1] == glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
			S1->AppendScope("Player Details").Append("Player Number");
			Scope S2 = *S1;
			Scope *S3 = new Scope(((*S1)["Player Details"].Get<Scope>(0)));
			Assert::IsTrue(*S1 == S2);
			Assert::IsTrue(((*S1)["Player Details"].Get<Scope>(0)) == *S3);
			Assert::IsTrue(*S1 != *S3);
			Assert::IsTrue(S1->Equals(&S2));
			S1->Append("Damage") = 400;
			S2.Append("Speed") = 200;
			Assert::IsFalse(*S1 == S2);
			Scope* s5 = new Scope();
			s5->Append("lol").PushBack(1);
			S1->Adopt(*s5, "lala");
			Scope* s4 = new Scope(std::move(*s5));
			Assert::IsTrue(s4->Find("lol") != nullptr);
			delete S1;
			delete S3;
			delete s5;
		}

		TEST_METHOD(RTTIFunctionsTest)
		{
			Scope s;
			uint64_t id = s.TypeIdClass();
			Assert::IsTrue(s.Is(id));
			Assert::IsTrue(&s == s.QueryInterface(id));
			Assert::IsTrue("Scope" == s.TypeName());
			RTTI* r = &s;
			Assert::IsNull(r->RTTI::QueryInterface(0));
			Assert::IsTrue(r->RTTI::ToString() == "RTTI");
			Assert::IsTrue(r->RTTI::Equals(&s));
			Assert::IsTrue(id = r->TypeIdInstance());
			Assert::IsTrue(id = Scope::TypeIdClass());
			Assert::IsTrue(r->QueryInterface(Scope::TypeIdClass()) == r);
			Assert::IsTrue(r->Is("Scope"));
			Assert::IsFalse(r->Is("waha"));
			Assert::IsNotNull(r->As<Scope>());
			Assert::IsNull(r->As<Foo>());
			Assert::IsTrue("" == r->ToString());
		}

		TEST_METHOD(ScopeSearchTest)
		{
			Scope s;
			Datum d = 10;
			s["First"] = d;
			Scope* ns = new Scope();
			Datum &d1 = ns->Append("Float");
			d1.SetType(DatumTypeEnum::Float);
			d1 = 5.5f;
			Assert::IsTrue(d1 == *ns->Find("Float"));
			(*ns)["Float"].PushBack(10.0f);
			s.Adopt(*ns, "Scope");
			Datum& d2 = s.Find("Scope")->Get<Scope>().Append("Int");
			d2.PushBack(5);
			Scope* s2;
			Datum* d3 = s.Search("Scope", s2);
			Assert::IsTrue(d3 == s.Find("Scope"));
			Assert::IsTrue(&s == s2);
			Assert::IsTrue(s[0U] == d);
			d3 = ns->Search("Scope", s2);
			Assert::IsTrue(s2 == &s);
			Scope* s3 = nullptr;
			d3 = s.Search("Float", s3);
			Assert::IsTrue(s3 == nullptr);
			d3 = ns->Search("Float", s3);
			Assert::IsTrue(s3 == ns);
			Assert::IsTrue(d3->Get<float>(1) = 10.0f);
		}

		TEST_METHOD(AppendFunctionTest)
		{
			Scope* ns = new Scope();
			Datum &d1 = ns->Append("Float");
			d1 = 5.5f;
			Assert::IsTrue(d1 == *ns->Find("Float"));
			Datum& d2 = ns->Append("Int");
			d2 = 10;
			Assert::IsTrue(d2 == *ns->Find("Int"));
			ns->Append("Int").PushBack(20);
			Assert::AreEqual(20, d2.Get<int32_t>(1));
			int32_t intArray[2] = { 10, 20 };
			Datum& d3 = ns->Append("IntArray");
			d3.SetStorage(intArray, 2);
			Assert::AreEqual(20, (*ns)["IntArray"].Get<int32_t>(1));
			auto expression = [&ns] {ns->Append(std::string()); };
			Assert::ExpectException<std::exception>(expression);
			Assert::IsTrue("Float" == ns->ToString());
			delete ns;
		}

		TEST_METHOD(AdoptTest)
		{
			Scope s;
			Datum d = 10;
			s["First"] = d;
			Assert::IsTrue(d == *s.Find("First"));
			auto e = [&s] {s.Adopt(s, "lel"); };
			Assert::ExpectException<std::exception>(e);
			Scope* ns = new Scope();
			Datum &d1 = ns->Append("Float");
			d1.SetType(DatumTypeEnum::Float);
			d1 = 5.5f;
			Assert::IsTrue(d1 == *ns->Find("Float"));
			(*ns)["Float"].PushBack(10.0f);
			Assert::IsTrue((*ns)["Float"].Get<float>(1) == 10.0f);
			s.Adopt(*ns, "Scope");
			Assert::IsTrue("Scope" == s.FindName(*ns));
			Datum& d2 = s.Find("Scope")->Get<Scope>().Append("Int");
			d2.PushBack(5);
			Assert::AreEqual(5, ns->Find("Int")->Get<int32_t>());
			Scope* s2;
			Datum* d3 = s.Search("Scope", s2);
			Assert::IsTrue(d3 == s.Find("Scope"));
			Assert::IsTrue(&s == s2);
			Assert::IsTrue(s[0U] == d);
			d3 = ns->Search("Scope", s2);
			Assert::IsTrue(s2 == &s);
			Scope s3;
			s3.Adopt(*ns, "AdoptedChild");
			Assert::IsTrue("AdoptedChild" == s3.FindName(*ns));
			Assert::IsTrue(std::string() == s.FindName(*ns));
			Assert::AreEqual(5.5f , ns->Search("Float")->Get<float>(0));
			delete ns;
		}

		TEST_METHOD(OprhanTest)
		{
			Scope s;
			Datum d = 10;
			s["First"] = d;
			Assert::IsTrue(d == *s.Find("First"));
			auto e = [&s] {s.Adopt(s, "lel"); };
			Assert::ExpectException<std::exception>(e);
			Scope* ns = new Scope();
			Datum &d1 = ns->Append("Float");
			d1.SetType(DatumTypeEnum::Float);
			d1 = 5.5f;
			Assert::IsTrue(d1 == *ns->Find("Float"));
			(*ns)["Float"].PushBack(10.0f);
			Assert::IsTrue((*ns)["Float"].Get<float>(1) == 10.0f);
			s.Adopt(*ns, "Scope");
			Assert::IsTrue("Scope" == s.FindName(*ns));
			Datum& d2 = s.Find("Scope")->Get<Scope>().Append("Int");
			d2.PushBack(5);
			Assert::AreEqual(5, ns->Find("Int")->Get<int32_t>());
			Scope* s2;
			Datum* d3 = s.Search("Scope", s2);
			Assert::IsTrue(d3 == s.Find("Scope"));
			Assert::IsTrue(&s == s2);
			Assert::IsTrue(s[0U] == d);
			d3 = ns->Search("Scope", s2);
			Assert::IsTrue(s2 == &s);
			auto ex = [&ns] {ns->Orphan(*ns); };
			Assert::ExpectException<std::exception>(ex);
			s.Orphan(*ns);
			Assert::IsTrue(std::string() == s.FindName(*ns));
			delete ns;
		}

		TEST_METHOD(AppendScopeTest)
		{
			Scope *S1 = new Scope();
			S1->Append("Health") = 100;
			Assert::IsTrue((*S1)[0] == 100);
			S1->Append("Position") = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			Assert::IsTrue((*S1)[1] == glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
			S1->AppendScope("Player Details").Append("Player Number");
			S1->AppendScope("Player Details").Append("Player Name");
			auto e = [&S1] {S1->AppendScope("Position"); };
			Assert::ExpectException<std::exception>(e);
			Scope S2 = *S1;
			Scope *S3 = new Scope(((*S1)["Player Details"].Get<Scope>(0)));
			Assert::IsTrue(*S1 == S2);
			Assert::IsTrue(((*S1)["Player Details"].Get<Scope>(0)) == *S3);
			Assert::IsFalse(*S1 == *S3);
			Assert::IsTrue(S1->Equals(&S2));
			delete S1;
			delete S3;
		}

		TEST_METHOD(FindTest)
		{
			Scope s;
			Datum d = 10;
			s["First"] = d;
			auto ex = [&s] {s[5]; };
			s.GetParent();
			Assert::ExpectException<std::exception>(ex);
			s[0];
			Assert::IsTrue(d == *s.Find("First"));
			auto e = [&s] {s.Adopt(s, "lel"); };
			Assert::ExpectException<std::exception>(e);
			Scope* ns = new Scope();
			Datum &d1 = ns->Append("Float");
			d1.SetType(DatumTypeEnum::Float);
			d1 = 5.5f;
			Assert::IsTrue(d1 == *ns->Find("Float"));
			delete ns;
		}

	private:
		static _CrtMemState sStartMemState;
	};
	_CrtMemState ScopeTest::sStartMemState;
}