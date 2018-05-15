#include "pch.h"
#include "SList.h"
#include "CppUnitTest.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(SListTest)
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

	private:
		static _CrtMemState sStartMemState;
		
		TEST_METHOD(PushBackTest)
		{
			//Primitive type
			int a = 5;
			int b = 10;
			SList<int> intList;
			intList.PushBack(a);
			Assert::AreEqual(a, intList.Front());
			Assert::AreEqual(intList.Front(), intList.Back());
			intList.PushBack(b);
			Assert::AreEqual(b, intList.Back());
			Assert::AreNotEqual(intList.Front(), intList.Back());
			Assert::AreEqual(2U, intList.Size());

			//Primitive pointer
			int* aP = &a;
			int* bP = &b;
			SList<int*> intPointerList;
			intPointerList.PushBack(aP);
			Assert::AreEqual(aP, intPointerList.Front());
			Assert::AreEqual(intPointerList.Front(), intPointerList.Back());
			*aP = 10;
			Assert::AreEqual(aP, intPointerList.Front());
			Assert::AreEqual(*aP, *(intPointerList.Front()));
			aP = bP;
			Assert::AreNotSame(aP, intPointerList.Front());

			//User definied Data type
			Foo fooObject1(5);
			Foo fooObject2(50);
			SList<Foo> fooList;
			fooList.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, fooList.Front());
			Assert::AreEqual(fooList.Front(), fooList.Back());
			fooList.PushBack(fooObject2);
			Assert::AreEqual(fooObject2, fooList.Back());
			Assert::AreNotEqual(fooList.Front(), fooList.Back());
			Assert::AreEqual(2U, fooList.Size());
		}

		TEST_METHOD(PushFrontTest)
		{

			//Primitive type
			int a = 5;
			int b = 10;
			SList<int> intList;
			Assert::AreEqual(a, *(intList.PushFront(a)));
			Assert::AreEqual(a, intList.Front());
			Assert::AreEqual(intList.Front(), intList.Back());
			Assert::AreEqual(b, *(intList.PushFront(b)));
			Assert::AreEqual(b, intList.Front());
			Assert::AreNotEqual(intList.Front(), intList.Back());
			Assert::AreEqual(2U, intList.Size());

			//Primitive pointer
			int* aP = &a;
			int* bP = &b;
			SList<int*> intPointerList;
			intPointerList.PushFront(aP);
			Assert::AreEqual(aP, intPointerList.Front());
			Assert::AreEqual(intPointerList.Front(), intPointerList.Back());
			*aP = 10;
			Assert::AreEqual(aP, intPointerList.Front());
			Assert::AreEqual(*aP, *(intPointerList.Front()));
			aP = bP;
			Assert::AreNotEqual(aP, intPointerList.Front());

			//User definied Data type
			Foo fooObject1(5);
			Foo fooObject2(50);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			Assert::AreEqual(fooObject1, fooList.Front());
			Assert::AreEqual(fooList.Front(), fooList.Back());
			fooList.PushFront(fooObject2);
			Assert::AreEqual(fooObject2, fooList.Front());
			Assert::AreNotEqual(fooList.Front(), fooList.Back());
			Assert::AreEqual(2U, fooList.Size());
		}

		TEST_METHOD(PopFrontTest)
		{
			//primitive type
			int a = 5;
			int b = 10;
			SList<int> intList;
			intList.PushFront(a);
			intList.PushFront(b);
			Assert::AreEqual(2U, intList.Size());
			Assert::AreEqual(b, intList.Front());
			intList.PopFront();
			Assert::AreEqual(a, intList.Front());
			Assert::AreEqual(1U, intList.Size());
			intList.PopFront();
			Assert::AreEqual(0U, intList.Size());
			Assert::IsTrue(intList.IsEmpty());

			//Primitive pointer
			int* aP = &a;
			int* bP = &b;
			SList<int*> intPointerList;
			Assert::IsTrue(intPointerList.IsEmpty());
			intPointerList.PopFront();
			Assert::IsTrue(intPointerList.IsEmpty());
			intPointerList.PushFront(aP);
			intPointerList.PushFront(bP);
			Assert::IsFalse(intPointerList.IsEmpty());
			Assert::AreEqual(2U, intPointerList.Size());
			Assert::AreEqual(bP, intPointerList.Front());
			intPointerList.PopFront();
			Assert::AreEqual(aP, intPointerList.Front());
			intPointerList.PopFront();
			Assert::IsTrue(intPointerList.IsEmpty());
			
			//User Defined Datatype
			Foo fooObject1(5);
			Foo fooObject2(50);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			Assert::AreEqual(fooObject2, fooList.Front());
			fooList.PopFront();
			Assert::AreEqual(fooObject1, fooList.Front());
			fooList.PopFront();
			Assert::IsTrue(fooList.IsEmpty());
		}

		TEST_METHOD(SlistCopyConstructor)
		{
			//primitive types
			int a = 5;
			int b = 10;
			SList<int> intList;
			intList.PushFront(a);
			intList.PushFront(b);
			SList<int> intListCopy = intList;
			Assert::AreEqual(intListCopy.Front(), intList.Front());
			Assert::AreEqual(intListCopy.Size(), intList.Size());
			intList.PopFront();
			Assert::AreNotEqual(intListCopy.Front(), intList.Front());
			Assert::AreNotEqual(intListCopy.Size(), intList.Size());

			//Primitive pointer types
			int* aP = &a;
			int* bP = &b;
			SList<int*> intPointerList;
			intPointerList.PushFront(aP);
			intPointerList.PushFront(bP);
			SList<int*> intPointerListCopy = intPointerList;
			Assert::AreEqual(intPointerListCopy.Front(), intPointerList.Front());
			Assert::AreEqual(intPointerListCopy.Size(), intPointerList.Size());
			intPointerList.PopFront();
			Assert::AreNotEqual(intPointerListCopy.Front(), intPointerList.Front());
			Assert::AreNotEqual(intPointerListCopy.Size(), intPointerList.Size());

			//User Defined DataTypes
			Foo fooObject1(5);
			Foo fooObject2(50);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			SList<Foo> fooListCopy = fooList;
			Assert::AreEqual(fooListCopy.Front(), fooList.Front());
			Assert::AreEqual(fooListCopy.Size(), fooList.Size());
			fooList.PopFront();
			Assert::AreNotEqual(fooListCopy.Front(), fooList.Front());
			Assert::AreNotEqual(fooListCopy.Size(), fooList.Size());
		}

		TEST_METHOD(ClearFunctionTest)
		{
			//Primitive Datatypes
			int a = 5;
			int b = 10;
			SList<int> intList;
			intList.PushFront(a);
			intList.PushFront(b);
			Assert::AreEqual(2U, intList.Size());
			Assert::IsFalse(intList.IsEmpty());
			intList.Clear();
			Assert::IsTrue(intList.IsEmpty());
		
			//Primitive Pointer types
			int* aP = &a;
			int* bP = &b;
			SList<int*> intPointerList;
			intPointerList.PushFront(aP);
			intPointerList.PushFront(bP);
			Assert::AreEqual(2U, intPointerList.Size());
			Assert::IsFalse(intPointerList.IsEmpty());
			intPointerList.Clear();
			Assert::IsTrue(intPointerList.IsEmpty());
			
			//User Defined Data type
			Foo fooObject1(5);
			Foo fooObject2(50);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			Assert::AreEqual(2U, fooList.Size());
			Assert::IsFalse(fooList.IsEmpty());
			fooList.Clear();
			Assert::IsTrue(fooList.IsEmpty());
		}

		TEST_METHOD(SizeFunctionTest)
		{
			//primitive datatype
			int a = 5;
			int b = 10;
			SList<int> intList;
			Assert::AreEqual(0U, intList.Size());
			intList.PushFront(a);
			intList.PushFront(b);
			Assert::AreEqual(2U, intList.Size());
			intList.PopFront();
			Assert::AreEqual(1U, intList.Size());

			//primitive pointer
			int* aP = &a;
			int* bP = &b;
			SList<int*> intPointerList;
			Assert::AreEqual(0U, intPointerList.Size());
			intPointerList.PushFront(aP);
			intPointerList.PushFront(bP);
			Assert::AreEqual(2U, intPointerList.Size());
			intPointerList.PopFront();
			Assert::AreEqual(1U, intPointerList.Size());

			//user defined data types
			Foo fooObject1(5);
			Foo fooObject2(50);
			SList<Foo> fooList;
			Assert::AreEqual(0U, fooList.Size());
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			Assert::AreEqual(2U, fooList.Size());
			fooList.PopFront();
			Assert::AreEqual(1U, fooList.Size());
		}

		TEST_METHOD(FrontTest)
		{
			//Primitive data types
			int a = 5;
			int b = 10;
			SList<int> intList;
			auto expression = [&intList] {intList.Front(); };
			Assert::ExpectException<std::exception>(expression);
			intList.PushFront(a);
			Assert::AreEqual(a, intList.Front());
			intList.PushFront(b);
			Assert::AreEqual(b, intList.Front());

			//Check the const front function works
			const SList<int>& constIntList = intList;
			Assert::AreEqual(b, constIntList.Front());
			intList.PopFront();
			intList.PopFront();
			Assert::AreEqual(0U, constIntList.Size());
			auto constExpression = [&constIntList] {constIntList.Front(); };
			Assert::ExpectException<std::exception>(constExpression);
			
			//Primitive Pointer types
			int* aP = &a;
			int* bP = &b;
			SList<int*> intPointerList;
			intPointerList.PushFront(aP);
			Assert::AreEqual(aP, intPointerList.Front());
			intPointerList.PushFront(bP);
			Assert::AreEqual(bP, intPointerList.Front());
			const SList<int*> constIntPointerList = intPointerList;
			Assert::AreEqual(bP, constIntPointerList.Front());

			//User defined datatype
			Foo fooObject1(5);
			Foo fooObject2(50);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			Assert::AreEqual(fooObject1, fooList.Front());
			fooList.PushFront(fooObject2);
			Assert::AreEqual(fooObject2, fooList.Front());
			const SList<Foo> constFooList = fooList;
			Assert::AreEqual(fooObject2, fooList.Front());
		}

		TEST_METHOD(BackTest)
		{
			//Primitive data types
			int a = 5;
			int b = 10;
			SList<int> intList;
			auto expression = [&intList] {intList.Back(); };
			Assert::ExpectException<std::exception>(expression);
			intList.PushBack(a);
			Assert::AreEqual(a, intList.Back());
			intList.PushBack(b);
			Assert::AreEqual(b, intList.Back());
			
			//Check the const front function works
			const SList<int>& constIntList = intList;
			Assert::AreEqual(b, constIntList.Back());
			intList.PopFront();
			intList.PopFront();
			Assert::AreEqual(0U, constIntList.Size());
			auto constExpression = [&constIntList] {constIntList.Back(); };
			Assert::ExpectException<std::exception>(constExpression);

			//Primitive Pointer types
			int* aP = &a;
			int* bP = &b;
			SList<int*> intPointerList;
			intPointerList.PushBack(aP);
			Assert::AreEqual(aP, intPointerList.Back());
			intPointerList.PushBack(bP);
			Assert::AreEqual(bP, intPointerList.Back());
			const SList<int*> constIntPointerList = intPointerList;
			Assert::AreEqual(bP, constIntPointerList.Back());

			//User defined datatype
			Foo fooObject1(5);
			Foo fooObject2(50);
			SList<Foo> fooList;
			fooList.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, fooList.Back());
			fooList.PushBack(fooObject2);
			Assert::AreEqual(fooObject2, fooList.Back());
			const SList<Foo> constFooList = fooList;
			Assert::AreEqual(fooObject2, fooList.Back());

		}

		TEST_METHOD(AssignmentOperatorTest)
		{
			//primitive types
			int a = 5;
			int b = 10;
			SList<int> intList;
			intList.PushFront(a);
			intList.PushFront(b);
			SList<int> intListCopy;
			intListCopy = intList;
			Assert::AreEqual(intListCopy.Front(), intList.Front());
			Assert::AreEqual(intListCopy.Size(), intList.Size());
			intList.PopFront();
			Assert::AreNotEqual(intListCopy.Front(), intList.Front());
			Assert::AreNotEqual(intListCopy.Size(), intList.Size());
			
			SList<int> j;
			j = SList<int>();

			//Primitive pointer types
			int* aP = &a;
			int* bP = &b;
			SList<int*> intPointerList;
			intPointerList.PushFront(aP);
			intPointerList.PushFront(bP);
			SList<int*> intPointerListCopy;
			intPointerListCopy = intPointerList;
			Assert::AreEqual(intPointerListCopy.Front(), intPointerList.Front());
			Assert::AreEqual(intPointerListCopy.Size(), intPointerList.Size());
			intPointerList.PopFront();
			Assert::AreNotEqual(intPointerListCopy.Front(), intPointerList.Front());
			Assert::AreNotEqual(intPointerListCopy.Size(), intPointerList.Size());

			//User Defined DataTypes
			Foo fooObject1(5);
			Foo fooObject2(50);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			SList<Foo> fooListCopy;
			fooListCopy = fooList;
			Assert::AreEqual(fooListCopy.Front(), fooList.Front());
			Assert::AreEqual(fooListCopy.Size(), fooList.Size());
			fooList.PopFront();
			Assert::AreNotEqual(fooListCopy.Front(), fooList.Front());
			Assert::AreNotEqual(fooListCopy.Size(), fooList.Size());
		}

		TEST_METHOD(PointerDestructorTest)
		{
			SList<int>* a = new SList<int>();
			delete a;
		}

		TEST_METHOD(IteratorRemoveTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			int w = 200;
			SList<int> a;
			a.PushFront(x);
			a.PushFront(y);
			a.PushBack(z);
			a.Remove(w);
			Assert::AreEqual(3U, a.Size());
			a.Remove(y);
			Assert::AreEqual(z, a.Back());
			Assert::AreEqual(2U, a.Size());
			Assert::AreEqual(x, *(a.begin()));
			Assert::AreEqual(z, a.Back());
			a.Remove(x);
			Assert::AreEqual(1U, a.Size());
			Assert::AreEqual(z, a.Front());
			Assert::AreEqual(z, a.Back());
			a.Remove(z);
			Assert::AreEqual(0U, a.Size());
			auto Expression = [&a, &y] {a.Remove (y); };
			Assert::ExpectException<std::exception>(Expression);
			a.PushBack(y);
			a.PushBack(z);
			a.Remove(z);
			
			//Primitive pointer type
			SList<int*> pointerList;
			int* aP = &x;
			int* bP = &y;
			int* cP = &z;
			int* dP = &w;
			pointerList.PushFront(aP);
			pointerList.PushFront(bP);
			pointerList.PushBack(cP);
			pointerList.Remove(dP);
			Assert::AreEqual(3U, pointerList.Size());
			pointerList.Remove(bP);
			Assert::AreEqual(cP, pointerList.Back());
			Assert::AreEqual(2U, pointerList.Size());
			Assert::AreEqual(aP, *(pointerList.begin()));
			Assert::AreEqual(cP, pointerList.Back());
			pointerList.Remove(aP);
			Assert::AreEqual(1U, pointerList.Size());
			Assert::AreEqual(cP, pointerList.Front());
			Assert::AreEqual(cP, pointerList.Back());
			pointerList.Remove(cP);
			Assert::AreEqual(0U, pointerList.Size());
			auto pointerExpression = [&pointerList, &bP] {pointerList.Remove(bP); };
			Assert::ExpectException<std::exception>(pointerExpression);
			pointerList.PushBack(bP);
			pointerList.PushBack(cP);
			pointerList.Remove(cP);

			//User Defined DataTypes
			Foo fooObject1(x);
			Foo fooObject2(y);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			fooList.Remove(fooObject1);
			Assert::AreEqual(1U, fooList.Size());
			Assert::AreEqual(fooObject2, fooList.Back());
			fooList.Remove(fooObject2);
			Assert::AreEqual(0U, fooList.Size());
		}

		TEST_METHOD(InsertAfterTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			int w = 50;
			SList<int> a;
			a.InsertAfter(a.begin(), x);
			a.PushFront(y);
			a.PushBack(z);
			auto it = a.begin();
			a.InsertAfter(it, w);
			++it;
			Assert::AreEqual(w, *it);
			++it;
			a.InsertAfter(a.end(), x);
			Assert::AreEqual(x, a.Back());

			//Primitive Pointer 
			SList<int*> pointerList;
			int* aP = &x;
			int* bP = &y;
			int* cP = &z;
			int* dP = &w;
			pointerList.PushFront(aP);
			pointerList.PushFront(bP);
			auto itP = pointerList.begin();
			pointerList.InsertAfter(itP, dP);
			itP++;
			Assert::AreEqual(dP, *(itP));
			pointerList.InsertAfter(pointerList.end(), cP);
			Assert::AreEqual(cP, pointerList.Back());

			//User Defined data type
			Foo fooObject1(x);
			Foo fooObject2(y);
			Foo fooObject3(z);
			Foo fooObject4(w);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			auto itF = fooList.begin();
			fooList.InsertAfter(itF, fooObject3);
			itF++;
			Assert::AreEqual(fooObject3, *(itF));
			fooList.InsertAfter(fooList.end(), fooObject4);
			Assert::AreEqual(fooObject4, fooList.Back());
		}

		TEST_METHOD(beginFunctionTest)
		{
			int x = 5;
			int y = 10;
			SList<int> a;
			a.PushFront(x);
			auto it = a.begin();
			Assert::AreEqual(x, *it);
			a.PushFront(y);
			it = a.begin();
			Assert::AreEqual(y, *it);
			const SList<int> &constA = a;
			it = constA.begin();
			Assert::AreEqual(y, *it);
		}

		TEST_METHOD(endFunctionTest)
		{
			int x = 5;
			SList<int> a;
			a.PushFront(x);
			auto it = a.end();
			const SList<int> &constA = a;
			it = constA.end();
		}

		TEST_METHOD(RemoveAllTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			int w = 200;
			SList<int> a;
			a.PushFront(x);
			a.PushFront(x);
			a.PushBack(y);
			a.PushBack(z);
			a.RemoveAll(w);
			Assert::AreEqual(4U, a.Size());
			a.RemoveAll(x);
			Assert::AreEqual(y, a.Front());
			Assert::AreEqual(2U, a.Size());
			Assert::AreEqual(z, a.Back());
			a.RemoveAll(y);
			Assert::AreEqual(1U, a.Size());
			Assert::AreEqual(z, a.Front());
			Assert::AreEqual(z, a.Back());
			a.RemoveAll(z);
			Assert::AreEqual(0U, a.Size());
			auto Expression = [&a, &y] {a.RemoveAll(y); };
			Assert::ExpectException<std::exception>(Expression);
			a.PushBack(y);
			a.PushBack(z);
			a.PushBack(x);
			a.PushBack(w);
			a.RemoveAll(z);
			a.RemoveAll(w);
			a.RemoveAll(x);

			//Primitive pointer type
			SList<int*> pointerList;
			int* aP = &x;
			int* bP = &y;
			int* cP = &z;
			int* dP = &w;
			pointerList.PushFront(aP);
			pointerList.PushFront(bP);
			pointerList.PushBack(cP);
			pointerList.RemoveAll(dP);
			Assert::AreEqual(3U, pointerList.Size());
			pointerList.RemoveAll(bP);
			Assert::AreEqual(cP, pointerList.Back());
			Assert::AreEqual(2U, pointerList.Size());
			Assert::AreEqual(aP, *(pointerList.begin()));
			Assert::AreEqual(cP, pointerList.Back());
			pointerList.RemoveAll(aP);
			Assert::AreEqual(1U, pointerList.Size());
			Assert::AreEqual(cP, pointerList.Front());
			Assert::AreEqual(cP, pointerList.Back());
			pointerList.RemoveAll(cP);
			Assert::AreEqual(0U, pointerList.Size());
			auto pointerExpression = [&pointerList, &bP] {pointerList.RemoveAll(bP); };
			Assert::ExpectException<std::exception>(pointerExpression);
			pointerList.PushBack(bP);
			pointerList.PushBack(cP);
			pointerList.RemoveAll(cP);

			//User Defined DataTypes
			Foo fooObject1(x);
			Foo fooObject2(y);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			fooList.RemoveAll(fooObject1);
			Assert::AreEqual(1U, fooList.Size());
			Assert::AreEqual(fooObject2, fooList.Back());
			fooList.RemoveAll(fooObject2);
			Assert::AreEqual(0U, fooList.Size());
		}

		TEST_METHOD(FindTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			SList<int> a;
			a.PushFront(x);
			a.PushFront(x);
			a.PushBack(y);
			a.PushBack(z);
			auto it = a.Find(x);
			Assert::AreEqual(x, *(it));
			a.Remove(y);
			it = a.Find(y);
			Assert::IsTrue(it == a.end());
			
			//Primitive Pointer type
			int* aP = &x;
			int* bP = &y;
			SList<int*> pointerList;
			pointerList.PushFront(aP);
			pointerList.PushBack(bP);
			auto itP = pointerList.Find(aP);
			Assert::AreEqual(aP, *(itP));
			pointerList.Remove(bP);
			itP = pointerList.Find(bP);
			Assert::IsTrue(itP == pointerList.end());

			//User Defined datatype
			Foo fooObject1(x);
			Foo fooObject2(y);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			auto itF = fooList.Find(fooObject1);
			Assert::AreEqual(fooObject1, *itF);
			fooList.Remove(fooObject2);
			itF = fooList.Find(fooObject2);
			Assert::IsTrue(itF == fooList.end());
		}

		TEST_METHOD(IteratorIncrementTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			SList<int> a;
			a.PushFront(x);
			a.PushBack(y);
			a.PushBack(z);
			auto it = a.begin();
			Assert::AreEqual(y, *(++it));
			it++;
			Assert::AreEqual(z, *it);
			++it;
			auto Expression = [&it] {*it; };
			Assert::ExpectException<std::exception>(Expression);
			auto Expression1 = [&it]{++it; };
			Assert::ExpectException<std::exception>(Expression1);

			//Primitive Pointer type
			SList<int*> pointerList;
			int* aP = &x;
			int* bP = &y;
			int* cP = &z;
			pointerList.PushFront(aP);
			pointerList.PushBack(bP);
			pointerList.PushBack(cP);
			auto itP = pointerList.begin();
			Assert::AreEqual(bP, *(++itP));
			itP++;
			Assert::AreEqual(cP, *itP);
			++itP;
			auto pointerExpression = [&itP] {*itP; };
			Assert::ExpectException<std::exception>(pointerExpression);
			auto pointerExpression1 = [&it] {it++; };
			Assert::ExpectException<std::exception>(pointerExpression1);

			//User Defined Type
			Foo fooObject1(x);
			Foo fooObject2(y);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			auto itF = fooList.begin();
			Assert::AreEqual(fooObject1, *(++itF));
			itF++;
			auto fooExpression = [&itF] {*itF; };
			Assert::ExpectException<std::exception>(fooExpression);
		}

		TEST_METHOD(IteratorEqualityTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			SList<int> a;
			a.PushFront(x);
			a.PushBack(y);
			a.PushBack(z);
			auto it = a.begin();
			auto it1 = a.begin();
			Assert::IsTrue(it == it1);
			it++;
			Assert::IsTrue(it != it1);
			it = a.end();
			it1 = a.end();
			Assert::IsTrue(it == it1);
			SList<int> b;
			b.PushFront(x);
			it1 = b.begin();
			Assert::IsFalse(it == it1);

			//Primitive Pointer Test
			int* aP = &x;
			int* bP = &y;
			int* cP = &z;
			SList<int*> pointerList;
			pointerList.PushFront(aP);
			pointerList.PushBack(bP);
			pointerList.PushBack(cP);
			auto itP = pointerList.begin();
			auto it1P = pointerList.begin();
			Assert::IsTrue(itP == it1P);
			itP++;
			Assert::IsTrue(itP != it1P);
			itP = pointerList.end();
			it1P = pointerList.end();
			Assert::IsTrue(itP == it1P);
			SList<int*> pointerList1;
			pointerList1.PushFront(aP);
			it1P = pointerList1.begin();
			Assert::IsFalse(itP == it1P);

			//User Defined Datatype
			Foo fooObject1(x);
			Foo fooObject2(y);
			SList<Foo> fooList;
			fooList.PushFront(fooObject1);
			fooList.PushFront(fooObject2);
			auto itF = fooList.begin();
			auto it1F = fooList.begin();
			Assert::IsTrue(itF == it1F);
			itF++;
			Assert::IsTrue(itF != it1F);
			itF = fooList.end();
			it1F = fooList.end();
			Assert::IsTrue(itF == it1F);
			SList<Foo> fooList1;
			fooList1.PushFront(fooObject1);
			it1F = fooList1.begin();
			Assert::IsFalse(itF == it1F);
		}

		TEST_METHOD(ConstDereferenceTest)
		{
			int x = 10;
			int y = 20;
			SList<int> a;
			a.PushFront(x);
			a.PushFront(y);
			const SList<int> &b = a;
			const SList<int>::Iterator it = b.begin();
			Assert::AreEqual(y, *it);
			a.PopFront();
			a.PopFront();
			const SList<int>::Iterator it1 = b.begin();
			auto Expression = [&it1] {*it1; };
			Assert::ExpectException<std::exception>(Expression);
		}
	};
	_CrtMemState SListTest::sStartMemState;
}
