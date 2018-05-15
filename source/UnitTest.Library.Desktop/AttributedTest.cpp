#include "pch.h"
#include "Attributed.h"
#include "AttributedFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace glm;

namespace UnitTestLibraryDesktop
{
	
	TEST_CLASS(AttributedTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			RegisterType(AttributedFoo)
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

		TEST_METHOD(AttributedFooTest)
		{
			AttributedFoo f1;
			Assert::IsTrue(f1.IsPrescribed("this"));
			Assert::IsTrue(f1.IsPrescribed("ExternalIntValue"));
			Assert::IsTrue(f1.IsPrescribed("ExternalMatrixValue"));
			Assert::IsFalse(f1.Find("ExternalIntValue") == nullptr);
			int a; a;
			f1["ExternalIntValue"].Set(10, 0);
			Assert::IsTrue(f1["ExternalIntValue"] == 10);
			f1.mIntegerArray[0] = 100;
			Assert::IsTrue(f1["ExternalIntArray"].Get<int32_t>() == 100);
			Assert::IsTrue(f1.IsPrescribed("ExternalIntValue"));
			Datum& d = f1.AppendAuxillaryAttribute("AuxillaryAttribute");
			d = 20;
			Assert::IsTrue(f1.IsAuxillary("AuxillaryAttribute"));
			AttributedFoo f2 = f1;
			Assert::IsTrue(f2["ExternalIntArray"].Get<int32_t>() == 100);
			f2.mIntegerArray[0] = 200;
			Assert::IsTrue(f2["ExternalIntArray"].Get<int32_t>() == 200);
			Assert::IsTrue(f1["ExternalIntArray"].Get<int32_t>() == 100);
			AttributedFoo f3 = std::move(f1);
			Assert::IsTrue(f3["ExternalIntArray"].Get<int32_t>() == 100);
			auto expression = [&f1] {f1.AppendAuxillaryAttribute("ExternalIntArray"); };
			Assert::ExpectException<std::exception>(expression);
		}

		TEST_METHOD(HelperFunctionsTest)
		{
			AttributedFoo f1;
			Vector<std::string> names = f1.Prescribed();
			Assert::AreEqual(13U, names.Size());
			f1.AppendAuxillaryAttribute("AuxillaryAttribute1") = 20;
			f1.AppendAuxillaryAttribute("AuxillaryAttribute2") = 10.0f;
			Vector<std::string>auxillaryAttributes = f1.Auxillary();
			Assert::AreEqual(2U, auxillaryAttributes.Size());
			Vector<std::string>attributes = f1.Attributes();
			Assert::AreEqual(15U, attributes.Size());

		}

		TEST_METHOD(RTTIFunctionsTest)
		{
			AttributedFoo s;
			uint64_t id = s.TypeIdClass();
			Assert::IsTrue(s.Is(id));
			Assert::IsTrue(&s == s.QueryInterface(id));
			Assert::IsTrue("AttributedFoo" == s.TypeName());
			RTTI* r = &s;
			Assert::IsTrue(id = r->TypeIdInstance());
			Assert::IsTrue(id = Scope::TypeIdClass());
			Assert::IsTrue(r->QueryInterface(Scope::TypeIdClass()) == r);
			Assert::IsTrue(r->Is("AttributedFoo"));
			Assert::IsFalse(r->Is("waha"));
			Assert::IsNotNull(r->As<Scope>());
			Assert::IsNotNull(r->As<AttributedFoo>());
			Assert::IsTrue("this" == r->ToString());
		}


	private:
		static _CrtMemState sStartMemState;
	};
	_CrtMemState AttributedTest::sStartMemState;
}