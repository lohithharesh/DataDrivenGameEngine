#include "pch.h"
#include "Scope.h"
#include "Foo.h"
#include "AbstractFactory.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(FactoryTest)
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

		TEST_METHOD(CreateTest)
		{
			ConcreteFactory(Scope, RTTI);
			ConcreteScopeFactory s;
			RTTI* test = AbstractFactory<RTTI>::Create("Test");
			Assert::IsNull(test);
			Scope* scope = AbstractFactory<RTTI>::Create("Scope")->As<Scope>();
			Assert::AreEqual(1U, AbstractFactory<RTTI>::mFactoryMap.Size());
			scope;
			delete scope;
			Assert::IsTrue(AbstractFactory<RTTI>::Find("Scope")->ClassName() == "Scope");
			ConcreteFactory(Foo, RTTI);
			ConcreteFooFactory f;
			Foo* foo = AbstractFactory<RTTI>::Create("Foo")->As<Foo>();
			Assert::AreEqual(2U, AbstractFactory<RTTI>::mFactoryMap.Size());
			Assert::AreEqual(10, foo->Data());
			delete foo;
			
		}

	private:
		static _CrtMemState sStartMemState;
	};
	_CrtMemState FactoryTest::sStartMemState;
}