#include "pch.h"
#include "Vector.h"
#include "CppUnitTest.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace UnitTestLibraryDesktop
{
	class CustomIncrementor
	{
	public:
		//! Funtion to overload the () operator
		/*!
		Overload the () operator so we can call the object as a function.
		\param size, a unsigned integer which is the current size of the vector
		\param capacity, a unsigned integer which is the current capacity of the vector
		\return a unsigned int, which is the new capacity to reserve for the vector
		*/
		uint32_t operator()(uint32_t size, uint32_t capacity) const
		{
			size++;
			return capacity + 7;
		}
	};

	TEST_CLASS(VectorTest)
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
			int a = 5;
			int b = 10;
			Vector<int> intVector;
			intVector.PushBack(a);
			Assert::AreEqual(a, intVector.Back());
			Assert::AreEqual(intVector.Back(), intVector.Back());
			intVector.PushBack(b);
			Assert::AreEqual(b, intVector.Back());
			Assert::AreEqual(2U, intVector.Size());

			//Primitive pointer
			int* aP = &a;
			int* bP = &b;
			Vector<int*> intPointerVector;
			intPointerVector.PushBack(aP);
			Assert::AreEqual(aP, intPointerVector.Back());
			Assert::AreEqual(intPointerVector.Back(), intPointerVector.Back());
			*aP = 10;
			Assert::AreEqual(aP, intPointerVector.Back());
			Assert::AreEqual(*aP, *(intPointerVector.Back()));
			aP = bP;
			Assert::AreNotSame(aP, intPointerVector.Back());

			//User definied Data type
			Foo fooObject1(a);
			Foo fooObject2(b);
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, fooVector.Back());
			Assert::AreEqual(fooVector.Back(), fooVector.Back());
			fooVector.PushBack(fooObject2);
			Assert::AreEqual(fooObject2, fooVector.Back());
			Assert::AreEqual(2U, fooVector.Size());
		}


		TEST_METHOD(ClearFunctionTest)
		{
			//Primitive Datatypes
			int a = 5;
			int b = 10;
			Vector<int> intVector;
			intVector.PushBack(a);
			intVector.PushBack(b);
			Assert::AreEqual(2U, intVector.Size());
			Assert::IsFalse(intVector.IsEmpty());
			intVector.Clear();
			Assert::IsTrue(intVector.IsEmpty());

			//Primitive Pointer types
			int* aP = &a;
			int* bP = &b;
			Vector<int*> intPointerVector;
			intPointerVector.PushBack(aP);
			intPointerVector.PushBack(bP);
			Assert::AreEqual(2U, intPointerVector.Size());
			Assert::IsFalse(intPointerVector.IsEmpty());
			intPointerVector.Clear();
			Assert::IsTrue(intPointerVector.IsEmpty());

			//User Defined Data type
			Foo fooObject1(a);
			Foo fooObject2(b);
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			fooVector.PushBack(fooObject2);
			Assert::AreEqual(2U, fooVector.Size());
			Assert::IsFalse(fooVector.IsEmpty());
			fooVector.Clear();
			Assert::IsTrue(fooVector.IsEmpty());
		}

		TEST_METHOD(SizeFunctionTest)
		{
			//primitive datatype
			int a = 5;
			int b = 10;
			Vector<int> intVector;
			Assert::AreEqual(0U, intVector.Size());
			intVector.PushBack(a);
			intVector.PushBack(b);
			Assert::AreEqual(2U, intVector.Size());
			intVector.PopBack();
			Assert::AreEqual(1U, intVector.Size());

			//primitive pointer
			int* aP = &a;
			int* bP = &b;
			Vector<int*> intPointerVector;
			Assert::AreEqual(0U, intPointerVector.Size());
			intPointerVector.PushBack(aP);
			intPointerVector.PushBack(bP);
			Assert::AreEqual(2U, intPointerVector.Size());
			intPointerVector.PopBack();
			Assert::AreEqual(1U, intPointerVector.Size());

			//user defined data types
			Foo fooObject1(a);
			Foo fooObject2(b);
			Vector<Foo> fooVector;
			Assert::AreEqual(0U, fooVector.Size());
			fooVector.PushBack(fooObject1);
			fooVector.PushBack(fooObject2);
			Assert::AreEqual(2U, fooVector.Size());
			fooVector.PopBack();
			Assert::AreEqual(1U, fooVector.Size());
		}

		TEST_METHOD(CapacityFunctionTest)
		{
			int a = 5;
			int b = 10;
			int c = 50;
			Vector<int, CustomIncrementor> intVector(2);
			intVector.PushBack(a);
			intVector.PushBack(b);
			Assert::AreEqual(2U, intVector.Capacity());
			intVector.PushBack(c);
			Assert::AreEqual(9U, intVector.Capacity());

			//primitive pointer
			int* aP = &a;
			int* bP = &b;
			Vector<int*> intPointerVector(2);
			intPointerVector.PushBack(aP);
			intPointerVector.PushBack(bP);
			Assert::AreEqual(2U, intPointerVector.Capacity());
			intPointerVector.PushBack(bP);
			Assert::AreEqual(7U, intPointerVector.Capacity());
			
			//User Defined Data type
			Foo fooObject1(a);
			Foo fooObject2(b);
			Vector<Foo, CustomIncrementor> fooVector(2);
			fooVector.PushBack(fooObject1);
			fooVector.PushBack(fooObject2);
			Assert::AreEqual(2U, fooVector.Capacity());
			fooVector.PushBack(fooObject1);
			Assert::AreEqual(9U, fooVector.Capacity());
		}


		TEST_METHOD(BackFunctionTest)
		{
			//Primitive data types
			int a = 5;
			int b = 10;
			Vector<int> intVector;
			auto expression = [&intVector] {intVector.Back(); };
			Assert::ExpectException<std::exception>(expression);
			intVector.PushBack(a);
			Assert::AreEqual(a, intVector.Back());
			intVector.PushBack(b);
			Assert::AreEqual(b, intVector.Back());

			//Check the const Back function works
			const Vector<int>& constIntVector = intVector;
			Assert::AreEqual(b, constIntVector.Back());
			intVector.PopBack();
			intVector.PopBack();
			Assert::AreEqual(0U, constIntVector.Size());
			auto constExpression = [&constIntVector] {constIntVector.Back(); };
			Assert::ExpectException<std::exception>(constExpression);

			//Primitive Pointer types
			int* aP = &a;
			int* bP = &b;
			Vector<int*> intPointerVector;
			intPointerVector.PushBack(aP);
			Assert::AreEqual(aP, intPointerVector.Back());
			intPointerVector.PushBack(bP);
			Assert::AreEqual(bP, intPointerVector.Back());
			const Vector<int*> constIntPointerVector = intPointerVector;
			Assert::AreEqual(bP, constIntPointerVector.Back());

			//User defined datatype
			Foo fooObject1(a);
			Foo fooObject2(b);
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, fooVector.Back());
			fooVector.PushBack(fooObject2);
			Assert::AreEqual(fooObject2, fooVector.Back());
			const Vector<Foo> constFooVector = fooVector;	
		}

		TEST_METHOD(ConstDereferenceTest)
		{
			int x = 10;
			int y = 20;
			Vector<int> a;
			a.PushBack(x);
			a.PushBack(y);
			const Vector<int> &b = a;
			const Vector<int>::Iterator it = b.begin();
			Assert::AreEqual(x, *it);
			a.PopBack();
			a.PopBack();
			const Vector<int>::Iterator it1 = b.begin();
			auto Expression = [&it1] {*it1; };
			Assert::ExpectException<std::exception>(Expression);
		}

		TEST_METHOD(IteratorEqualityTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			Vector<int> a;
			a.PushBack(x);
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
			Vector<int> b;
			b.PushBack(x);
			it1 = b.begin();
			Assert::IsFalse(it == it1);

			//Primitive Pointer Test
			int* aP = &x;
			int* bP = &y;
			int* cP = &z;
			Vector<int*> pointerVector;
			pointerVector.PushBack(aP);
			pointerVector.PushBack(bP);
			pointerVector.PushBack(cP);
			auto itP = pointerVector.begin();
			auto it1P = pointerVector.begin();
			Assert::IsTrue(itP == it1P);
			itP++;
			Assert::IsTrue(itP != it1P);
			itP = pointerVector.end();
			it1P = pointerVector.end();
			Assert::IsTrue(itP == it1P);
			Vector<int*> pointerVector1;
			pointerVector1.PushBack(aP);
			it1P = pointerVector1.begin();
			Assert::IsFalse(itP == it1P);

			//User Defined Datatype
			Foo fooObject1(x);
			Foo fooObject2(y);
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			fooVector.PushBack(fooObject2);
			auto itF = fooVector.begin();
			auto it1F = fooVector.begin();
			Assert::IsTrue(itF == it1F);
			itF++;
			Assert::IsTrue(itF != it1F);
			itF = fooVector.end();
			it1F = fooVector.end();
			Assert::IsTrue(itF == it1F);
			Vector<Foo> fooVector1;
			fooVector1.PushBack(fooObject1);
			it1F = fooVector1.begin();
			Assert::IsFalse(itF == it1F);
		}

		TEST_METHOD(IteratorIncrementTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			Vector<int> a;
			a.PushBack(x);
			a.PushBack(y);
			a.PushBack(z);
			Vector<int>::Iterator it;
			auto Expression = [&it] {*it; };
			Assert::ExpectException<std::exception>(Expression);
			it = a.begin();
			Assert::AreEqual(y, *(++it));
			it++;
			Assert::AreEqual(z, *it);
			++it;
			Assert::ExpectException<std::exception>(Expression);
			auto Expression1 = [&it] {++it; };
			Assert::ExpectException<std::exception>(Expression1);

			//Primitive Pointer type
			Vector<int*> pointerVector;
			int* aP = &x;
			int* bP = &y;
			int* cP = &z;
			pointerVector.PushBack(aP);
			pointerVector.PushBack(bP);
			pointerVector.PushBack(cP);
			auto itP = pointerVector.begin();
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
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			fooVector.PushBack(fooObject2);
			auto itF = fooVector.begin();
			Assert::AreEqual(fooObject2, *(++itF));
			itF++;
			auto fooExpression = [&itF] {*itF; };
			Assert::ExpectException<std::exception>(fooExpression);
		}

		TEST_METHOD(FindTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			Vector<int> a;
			a.PushBack(x);
			a.PushBack(x);
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
			Vector<int*> pointerVector;
			pointerVector.PushBack(aP);
			pointerVector.PushBack(bP);
			auto itP = pointerVector.Find(aP);
			Assert::AreEqual(aP, *(itP));
			pointerVector.Remove(bP);
			itP = pointerVector.Find(bP);
			Assert::IsTrue(itP == pointerVector.end());

			//User Defined datatype
			Foo fooObject1(x);
			Foo fooObject2(y);
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			fooVector.PushBack(fooObject2);
			auto itF = fooVector.Find(fooObject1);
			Assert::AreEqual(fooObject1, *itF);
			fooVector.Remove(fooObject2);
			itF = fooVector.Find(fooObject2);
			Assert::IsTrue(itF == fooVector.end());
		}


		TEST_METHOD(beginFunctionTest)
		{
			int x = 5;
			int y = 10;
			Vector<int> a;
			a.PushBack(x);
			auto it = a.begin();
			Assert::AreEqual(x, *it);
			a.PushBack(y);
			it = a.begin();
			Assert::AreEqual(x, *it);
			const Vector<int> &constA = a;
			it = constA.begin();
			Assert::AreEqual(x, *it);
		}


		TEST_METHOD(AssignmentOperatorTest)
		{
			//primitive types
			int a = 5;
			int b = 10;
			Vector<int> intVector;
			intVector.PushBack(a);
			intVector.PushBack(b);
			Vector<int> intVectorCopy;
			intVectorCopy = intVector;
			Assert::AreEqual(intVectorCopy.Back(), intVector.Back());
			Assert::AreEqual(intVectorCopy.Size(), intVector.Size());
			intVector.PopBack();
			Assert::AreNotEqual(intVectorCopy.Back(), intVector.Back());
			Assert::AreNotEqual(intVectorCopy.Size(), intVector.Size());
			Vector<int> j;
			j = Vector<int>(5);
			j.PushBack(5);
			Assert::AreEqual(j.Front(), 5);
			Assert::AreEqual(j.Capacity(), 5U);
			//Primitive pointer types
			int* aP = &a;
			int* bP = &b;
			Vector<int*> intPointerVector;
			intPointerVector.PushBack(aP);
			intPointerVector.PushBack(bP);
			Vector<int*> intPointerVectorCopy;
			intPointerVectorCopy = intPointerVector;
			Assert::AreEqual(intPointerVectorCopy.Back(), intPointerVector.Back());
			Assert::AreEqual(intPointerVectorCopy.Size(), intPointerVector.Size());
			intPointerVector.PopBack();
			Assert::AreNotEqual(intPointerVectorCopy.Back(), intPointerVector.Back());
			Assert::AreNotEqual(intPointerVectorCopy.Size(), intPointerVector.Size());

			//User Defined DataTypes
			Foo fooObject1(5);
			Foo fooObject2(50);
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			fooVector.PushBack(fooObject2);
			Vector<Foo> fooVectorCopy;
			fooVectorCopy = fooVector;
			Assert::AreEqual(fooVectorCopy.Back(), fooVector.Back());
			Assert::AreEqual(fooVectorCopy.Size(), fooVector.Size());
			fooVector.PopBack();
			Assert::AreNotEqual(fooVectorCopy.Back(), fooVector.Back());
			Assert::AreNotEqual(fooVectorCopy.Size(), fooVector.Size());
		}



		TEST_METHOD(FrontFunctionTest)
		{
			//Primitive data types
			int a = 5;
			int b = 10;
			Vector<int> intVector;
			auto expression = [&intVector] {intVector.Front(); };
			Assert::ExpectException<std::exception>(expression);
			intVector.PushBack(a);
			Assert::AreEqual(a, intVector.Back());
			intVector.PopBack();
			intVector.PushBack(b);
			Assert::AreEqual(b, intVector.Back());
			
			//Check the const Back function works
			const Vector<int>& constIntVector = intVector;
			Assert::AreEqual(b, constIntVector.Back());
			intVector.PopBack();
			Assert::AreEqual(0U, constIntVector.Size());
			auto constExpression = [&constIntVector] {constIntVector.Back(); };
			Assert::ExpectException<std::exception>(constExpression);

			//Primitive Pointer types
			int* aP = &a;
			int* bP = &b;
			Vector<int*> intPointerVector;
			intPointerVector.PushBack(aP);
			Assert::AreEqual(aP, intPointerVector.Back());
			intPointerVector.PopBack();
			intPointerVector.PushBack(bP);
			Assert::AreEqual(bP, intPointerVector.Back());
			const Vector<int*> constIntPointerVector = intPointerVector;
			Assert::AreEqual(bP, constIntPointerVector.Back());

			//User defined datatype
			Foo fooObject1(a);
			Foo fooObject2(b);
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, fooVector.Back());
			fooVector.PopBack();
			fooVector.PushBack(fooObject2);
			Assert::AreEqual(fooObject2, fooVector.Back());
			const Vector<Foo> constFooVector = fooVector;
			Assert::AreEqual(fooObject2, fooVector.Back());
		}

		TEST_METHOD(VectorCopyConstructor)
		{
			//primitive types
			int a = 5;
			int b = 10;
			Vector<int> intVector;
			intVector.PushBack(a);
			intVector.PushBack(b);
			Vector<int> intVectorCopy = intVector;
			Assert::AreEqual(intVectorCopy.Back(), intVector.Back());
			Assert::AreEqual(intVectorCopy.Size(), intVector.Size());
			intVector.PopBack();
			Assert::AreNotEqual(intVectorCopy.Back(), intVector.Back());
			Assert::AreNotEqual(intVectorCopy.Size(), intVector.Size());

			//Primitive pointer types
			int* aP = &a;
			int* bP = &b;
			Vector<int*> intPointerVector;
			intPointerVector.PushBack(aP);
			intPointerVector.PushBack(bP);
			Vector<int*> intPointerVectorCopy = intPointerVector;
			Assert::AreEqual(intPointerVectorCopy.Back(), intPointerVector.Back());
			Assert::AreEqual(intPointerVectorCopy.Size(), intPointerVector.Size());
			intPointerVector.PopBack();
			Assert::AreNotEqual(intPointerVectorCopy.Back(), intPointerVector.Back());
			Assert::AreNotEqual(intPointerVectorCopy.Size(), intPointerVector.Size());

			//User Defined DataTypes
			Foo fooObject1(5);
			Foo fooObject2(50);
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			fooVector.PushBack(fooObject2);
			Vector<Foo> fooVectorCopy = fooVector;
			Assert::AreEqual(fooVectorCopy.Back(), fooVector.Back());
			Assert::AreEqual(fooVectorCopy.Size(), fooVector.Size());
			fooVector.PopBack();
			Assert::AreNotEqual(fooVectorCopy.Back(), fooVector.Back());
			Assert::AreNotEqual(fooVectorCopy.Size(), fooVector.Size());
		}

		TEST_METHOD(RemoveFunctionTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			int w = 200;
			Vector<int> a;
			a.PushBack(x);
			a.PushBack(y);
			a.PushBack(z);
			a.Remove(w);
			Assert::AreEqual(3U, a.Size());
			a.Remove(y);
			Assert::AreEqual(z, a.Back());
			Assert::AreEqual(2U, a.Size());
			Assert::AreEqual(x, *(a.begin()));
			a.Remove(a.begin());
			Assert::AreEqual(1U, a.Size());
			Assert::AreEqual(z, a.Front());
			Assert::AreEqual(z, a.Back());
			a.Remove(z);
			Assert::AreEqual(0U, a.Size());

			//Primitive pointer type
			Vector<int*> pointerVector;
			int* aP = &x;
			int* bP = &y;
			int* cP = &z;
			int* dP = &w;
			pointerVector.PushBack(aP);
			pointerVector.PushBack(bP);
			pointerVector.PushBack(cP);
			pointerVector.Remove(dP);
			Assert::AreEqual(3U, pointerVector.Size());
			pointerVector.Remove(bP);
			Assert::AreEqual(cP, pointerVector.Back());
			Assert::AreEqual(2U, pointerVector.Size());
			Assert::AreEqual(aP, *(pointerVector.begin()));
			pointerVector.Remove(pointerVector.begin());
			Assert::AreEqual(1U, pointerVector.Size());
			Assert::AreEqual(cP, pointerVector.Front());
			Assert::AreEqual(cP, pointerVector.Back());
			pointerVector.Remove(cP);
			Assert::AreEqual(0U, pointerVector.Size());

			//User Defined DataTypes
			Foo fooObject1(x);
			Foo fooObject2(y);
			Vector<Foo> fooVector;
			fooVector.PushBack(fooObject1);
			fooVector.PushBack(fooObject2);
			fooVector.Remove(fooObject1);
			Assert::AreEqual(1U, fooVector.Size());
			Assert::AreEqual(fooObject2, fooVector.Back());
			fooVector.Remove(fooObject2);
			Assert::AreEqual(0U, fooVector.Size());
		}


		TEST_METHOD(RangeRemoveFunctionTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			Vector<int> a;
			a.PushBack(x);
			a.PushBack(y);
			a.PushBack(z);
			Assert::IsTrue(a.Remove(a.begin(), a.begin() + 1));
			Assert::IsFalse(a.Remove(a.begin(), a.end()));
			Assert::IsFalse(a.Remove(a.begin() + 2, a.begin()));
			Assert::IsTrue(a.Remove(a.begin(), a.begin()));
			Assert::IsTrue(a.IsEmpty());
		}

		TEST_METHOD(VectorofVectorTest)
		{
			int x = 5;
			int y = 10;
			int z = 20;
			Vector<int> a;
			a.PushBack(x);
			a.PushBack(y);
			a.PushBack(z);
			Vector<Vector<int>> b;
			b.PushBack(a);
			/*b.PushBack(a);
			b.PushBack(a);
			b.PushBack(a);
			b.PushBack(a);*/
		/*	Assert::IsFalse(b.Reserve(2));
			Assert::AreEqual(8U, b.Capacity());
			Assert::AreEqual(x, b[0].Front());
			auto expression = [&b] { b[10].Front(); };
			Assert::ExpectException<std::exception>(expression);
			b.ShrinkToFit();
			Assert::AreEqual(5U, b.Capacity());*/

		}
	};
_CrtMemState VectorTest::sStartMemState;
}
