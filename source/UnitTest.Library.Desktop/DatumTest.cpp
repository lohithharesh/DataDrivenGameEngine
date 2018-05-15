#include "pch.h"
#include "Foo.h"
#include "Datum.h"
#include "Scope.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace glm;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(DatumTest)
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
			Datum d;
			Assert::AreEqual(0U, d.Size());
			Assert::IsTrue(DatumTypeEnum::Unknown == d.Type());
			d.SetType(DatumTypeEnum::Integer);
			d.Resize(10);
			Assert::AreEqual(10U, d.Size());

			Datum d1;
			Assert::AreEqual(0U, d1.Size());
			Assert::IsTrue(DatumTypeEnum::Unknown == d1.Type());
			d1.SetType(DatumTypeEnum::Float);
			d1.Resize(10);
			Assert::AreEqual(10U, d1.Size());

			Datum d2;
			Assert::AreEqual(0U, d2.Size());
			Assert::IsTrue(DatumTypeEnum::Unknown == d2.Type());
			d2.SetType(DatumTypeEnum::RTTI);
			d2.Resize(10);
			Assert::AreEqual(10U, d2.Size());
		}

		TEST_METHOD(CopyConstructorTest)
		{
			Datum d = 10;
			Assert::AreEqual(10, d.Get<int32_t>());
			Datum d1 = d;
			Assert::IsTrue(d1.Type() == d.Type());
			Assert::IsTrue(d1.Size() == d.Size());
			Assert::AreEqual(10, d1.Get<int32_t>());

			Datum d2 = 10.1f;
			Assert::AreEqual(10.1f, d2.Get<float>());
			Datum d3 = d2;
			Assert::IsTrue(d3.Type() == d2.Type());
			Assert::IsTrue(d3.Size() == d2.Size());
			Assert::AreEqual(10.1f, d3.Get<float>());
			Assert::IsTrue(d3 == d2);

			string s1 = "hello";
			string s2 = "blah";
			Datum ds;
			ds.SetType(DatumTypeEnum::String);
			ds.PushBack(s1);
			ds.PushBack(s2);
			Datum ds1(ds);
			Assert::IsTrue(ds1 == ds);

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			Datum dv = v1;
			Datum dv1 = dv;
			Assert::IsTrue(dv1.Get<vec4>() == dv.Get<vec4>());
			Assert::IsTrue(dv1 == dv);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			Datum dm = m1;
			Datum dm1 = dm;
			Assert::IsTrue(dm1.Get<mat4>() == dm.Get<mat4>());
			Assert::IsTrue(dm1 == dm);

			Foo foo(10);
			RTTI* r = &foo;
			Datum dr = r;
			Assert::IsTrue(dr.Get<RTTI*>(0) == r);
			Assert::IsTrue(dr == r);
			Datum dr1 = dr;
			Assert::IsTrue(dr1 == dr);
		}

		TEST_METHOD(AssignmentOperatorTest)
		{
			Datum d = 10;
			Assert::AreEqual(10, d.Get<int32_t>());
			Datum d1 = d;
			Assert::IsTrue(d1.Type() == d.Type());
			Assert::IsTrue(d1.Size() == d.Size());
			Assert::AreEqual(10, d1.Get<int32_t>());
			d.PushBack(20);
			d.PushBack(30);
			Assert::AreEqual(20, d.Get<int32_t>(1));
			auto Expression = [&d1] {d1.Get<int32_t>(1); };
			Assert::ExpectException<std::exception>(Expression);
			d1 = d;
			Assert::AreEqual(20, d.Get<int32_t>(1));
			
			Datum j;
			j = Datum();
			j.PushBack(10);
			
			
			float f = 15.54f;
			Datum d2 = f;
			Assert::AreEqual(f, d2.Get<float>());
			d1 = d2;
			Assert::AreEqual(f, d1.Get<float>());
			Assert::IsTrue(d1.Size() == d2.Size());
			d1.PushBack(10.2f);

			std::string s = "hello";
			Datum d3 = s;
			std::string s1 = "blah";
			d3.PushBack(s1);
			Assert::IsTrue(s == d3.Get<std::string>());
			Assert::IsTrue(s1 == d3.Get<std::string>(1));
			d1 = d3;
			Assert::IsTrue(s == d1.Get<std::string>());
			Assert::IsTrue(s1 == d1.Get<std::string>(1));
			Assert::IsTrue(DatumTypeEnum::String == d1.Type());

			int intArray[5] = { 1, 2, 3, 4 ,5 };
			Datum de;
			de.SetStorage(intArray, 5);
			d1 = de;
			Assert::AreEqual(1, d1.Get<int32_t>());
			Datum du;
			d1 = du;
			Assert::IsTrue(du == d1);
			Assert::IsTrue(DatumTypeEnum::Unknown == d1.Type());

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr = r;
			dr.PushBack(r1);
			Datum dr1 = dr;
			Assert::IsTrue(r == dr.Get<RTTI*>());

		}

		TEST_METHOD(TypeCastFunctionTests)
		{
			Datum d = 10;
			Assert::AreEqual(1U, d.Size());
			Assert::IsTrue(DatumTypeEnum::Integer == d.Type());
			Assert::AreEqual(10, d.Get<int32_t>());


			float f = 15.54f;
			Datum d2 = f;
			Assert::AreEqual(f, d2.Get<float>());

			std::string s = "hello";
			Datum d3 = s;
			Assert::IsTrue(s == d3.Get<std::string>());

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			Datum dv = v1;
			Assert::IsTrue(dv.Get<vec4>() == v1);


			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			Datum dm = m1;
			Assert::IsTrue(dm.Get<mat4>() == m1);

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			Datum dr = r;
			Assert::IsTrue(dr == r);
		}


		TEST_METHOD(ScalarAssignmentTests)
		{
			Datum d = 10;
			Assert::AreEqual(10, d.Get<int32_t>());
			d = 20;
			Assert::AreEqual(20, d.Get<int32_t>());
			Assert::AreEqual(1U, d.Size());
			auto expression = [&d] {d = 20.4f; };
			Assert::ExpectException<std::exception>(expression);
			d.PushBack(20);
			d.Set(40);
			Assert::AreEqual(40, d.Get<int32_t>());
			Assert::AreEqual(20, d.Get<int32_t>(1));
			
			float f = 15.54f;
			Datum d2 = f;
			Assert::AreEqual(f, d2.Get<float>());
			d2 = 20.94f;
			Assert::AreEqual(20.94f, d2.Get<float>());
			
			std::string s = "hello";
			Datum d3 = s;
			Assert::IsTrue(s == d3.Get<std::string>());
			d3 = "lalala";
			Assert::IsTrue("lalala" == d3.Get<std::string>());
			
			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };
			Datum dv = v1;
			Assert::IsTrue(dv.Get<vec4>() == v1);
			dv = v2;
			Assert::IsTrue(dv.Get<vec4>() == v2);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}

			Datum dm = m1;
			Assert::IsTrue(dm.Get<mat4>() == m1);
			dm = m2;
			Assert::IsTrue(dm.Get<mat4>() == m2);

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr = r;
			Assert::IsTrue(r == dr.Get<RTTI*>());
			dr = r1;
			Assert::IsTrue(r1 == dr.Get<RTTI*>());
		}

		TEST_METHOD(SetTests)
		{
			Datum d;
			auto expression = [&d] {d.Set(1); };
			Assert::ExpectException<std::exception>(expression);
			d.SetType(DatumTypeEnum::Integer);
			d.PushBack(10);
			d.PushBack(20);
			Assert::AreEqual(10, d.Get<int32_t>());
			Assert::AreEqual(20, d.Get<int32_t>(1));
			d.Set(5);
			Assert::AreEqual(5, d.Get<int32_t>());
			d.Set(10, 1);
			Assert::AreEqual(10, d.Get<int32_t>(1));
			auto expression1 = [&d] {d.Set(1.1f); };
			Assert::ExpectException<std::exception>(expression1);
			auto expression2 = [&d] {d.Set(10 , 2); };
			Assert::ExpectException<std::exception>(expression2);

			float f = 15.54f;
			Datum d2 = f;
			Assert::AreEqual(f, d2.Get<float>());
			d2.Set(10.5f);
			Assert::AreEqual(10.5f, d2.Get<float>());
			d2.PushBack(9.0f);
			d2.Set(9.75f, 1);
			Assert::AreEqual(9.75f, d2.Get<float>(1));

			std::string s = "hello";
			Datum d3 = s;
			Assert::IsTrue(s == d3.Get<std::string>());
			d3.Set("lalala");
			Assert::IsTrue("lalala" == d3.Get<std::string>());

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };
			Datum dv = v1;
			Assert::IsTrue(dv.Get<vec4>() == v1);
			dv.Set(v2);
			Assert::IsTrue(dv.Get<vec4>() == v2);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}

			Datum dm = m1;
			Assert::IsTrue(dm.Get<mat4>() == m1);
			dm.Set(m2);
			Assert::IsTrue(dm.Get<mat4>() == m2);

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr = r;
			Assert::IsTrue(r == dr.Get<RTTI*>());
			dr.Set(r1);
			Assert::IsTrue(r1 == dr.Get<RTTI*>());
		}

		TEST_METHOD(GetTests)
		{
			Datum d;
			auto expression = [&d] {d.Get<int32_t>(); };
			Assert::ExpectException<std::exception>(expression);
			d.SetType(DatumTypeEnum::Integer);
			d.PushBack(10);
			d.PushBack(20);
			Assert::AreEqual(10, d.Get<int32_t>());
			Assert::AreEqual(20, d.Get<int32_t>(1));
			d.Set(5);
			Assert::AreEqual(5, d.Get<int32_t>());
			d.Set(10, 1);
			Assert::AreEqual(10, d.Get<int32_t>(1));
			auto expression1 = [&d] {d.Get<float>(); };
			Assert::ExpectException<std::exception>(expression1);
			auto expression2 = [&d] {d.Get<int32_t>(2); };
			Assert::ExpectException<std::exception>(expression2);

			float f = 15.54f;
			Datum d2 = f;
			Assert::AreEqual(f, d2.Get<float>());
			d2.Set(10.5f);
			Assert::AreEqual(10.5f, d2.Get<float>());
			d2.PushBack(9.0f);
			d2.Set(9.75f, 1);
			Assert::AreEqual(9.75f, d2.Get<float>(1));

			std::string s = "hello";
			Datum d3 = s;
			Assert::IsTrue(s == d3.Get<std::string>());
			d3.Set("lalala");
			Assert::IsTrue("lalala" == d3.Get<std::string>());

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };
			Datum dv = v1;
			Assert::IsTrue(dv.Get<vec4>() == v1);
			dv.Set(v2);
			Assert::IsTrue(dv.Get<vec4>() == v2);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}

			Datum dm = m1;
			Assert::IsTrue(dm.Get<mat4>() == m1);
			dm.Set(m2);
			Assert::IsTrue(dm.Get<mat4>() == m2);

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr = r;
			Assert::IsTrue(r == dr.Get<RTTI*>());
			dr.Set(r1);
			Assert::IsTrue(r1 == dr.Get<RTTI*>());
		}

		TEST_METHOD(ConstGetTests)
		{
			Datum d;
			auto expression = [&d] {d.Get<int32_t>(); };
			Assert::ExpectException<std::exception>(expression);
			d.SetType(DatumTypeEnum::Integer);
			d.PushBack(10);
			d.PushBack(20);
			Assert::AreEqual(10, d.Get<int32_t>());
			Assert::AreEqual(20, d.Get<int32_t>(1));
			d.Set(5);
			Assert::AreEqual(5, d.Get<int32_t>());
			d.Set(10, 1);
			const Datum dc = d;
			Assert::AreEqual(10, dc.Get<int32_t>(1));
			auto expression1 = [&dc] {dc.Get<float>(); };
			Assert::ExpectException<std::exception>(expression1);
			auto expression2 = [&dc] {dc.Get<int32_t>(2); };
			Assert::ExpectException<std::exception>(expression2);

			float f = 15.54f;
			Datum d2 = f;
			const Datum randomDatum;
			auto expression5 = [&randomDatum] {randomDatum.Get<int32_t>(); };
			Assert::ExpectException<std::exception>(expression5);
			Assert::AreEqual(f, d2.Get<float>());
			d2.Set(10.5f);
			Assert::AreEqual(10.5f, d2.Get<float>());
			d2.PushBack(9.0f);
			d2.Set(9.75f, 1);
			const Datum dfc = d2;
			Assert::AreEqual(9.75f, dfc.Get<float>(1));

			std::string s = "hello";
			Datum d3 = s;
			Assert::IsTrue(s == d3.Get<std::string>());
			d3.Set("lalala");
			const Datum dsc = d3;
			Assert::IsTrue("lalala" == dsc.Get<std::string>());

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };
			Datum dv = v1;
			Assert::IsTrue(dv.Get<vec4>() == v1);
			dv.Set(v2);
			const Datum dvc = dv;
			Assert::IsTrue(dvc.Get<vec4>() == v2);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}

			Datum dm = m1;
			Assert::IsTrue(dm.Get<mat4>() == m1);
			dm.Set(m2);
			const Datum dmc = dm;
			Assert::IsTrue(dmc.Get<mat4>() == m2);

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr = r;
			Assert::IsTrue(r == dr.Get<RTTI*>());
			dr.Set(r1);
			Assert::IsTrue(r1 == dr.Get<RTTI*>());
		}




		TEST_METHOD(PushBackTests)
		{
			Datum d;
			auto Expression = [&d] {d.PushBack(20); };
			d.SetType(DatumTypeEnum::Integer);
			d.PushBack(20);
			d.PushBack(30);
			d.PushBack(40);
			Assert::AreEqual(20, d.Get<int32_t>());
			Assert::AreEqual(30, d.Get<int32_t>(1));
			Assert::AreEqual(40, d.Get<int32_t>(2));
			auto expression2 = [&d] {d.PushBack(1.5f); };
			Assert::ExpectException<std::exception>(expression2);
			int intArray[5] = { 1, 2, 3, 4, 5 };
			d.SetStorage(intArray, 5);
			Assert::ExpectException<std::exception>(Expression);

			float f = 15.54f;
			Datum d2 = f;
			Assert::AreEqual(f, d2.Get<float>());
			d2.PushBack(9.0f);
			Assert::AreEqual(9.0f, d2.Get<float>(1));

			std::string s = "hello";
			Datum d3 = s;
			Assert::IsTrue(s == d3.Get<std::string>());
			d3.PushBack("lalala");
			Assert::IsTrue("lalala" == d3.Get<std::string>(1));

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };
			Datum dv = v1;
			Assert::IsTrue(dv.Get<vec4>() == v1);
			dv.PushBack(v2);
			Assert::IsTrue(dv.Get<vec4>(1) == v2);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}

			Datum dm = m1;
			Assert::IsTrue(dm.Get<mat4>() == m1);
			dm.PushBack(m2);
			Assert::IsTrue(dm.Get<mat4>(1) == m2);

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr;
			dr.SetType(DatumTypeEnum::RTTI);
			dr.PushBack(r);
			Assert::IsTrue(r == dr.Get<RTTI*>());
			dr.PushBack(r1);
			Assert::IsTrue(r1 == dr.Get<RTTI*>(1));


		}

		TEST_METHOD(PopBackTests)
		{
			Datum d;
			auto expression1 = [&d] {d.PopBack(); };
			Assert::ExpectException<std::exception>(expression1);
			d.SetType(DatumTypeEnum::Integer);
			d.PushBack(20);
			d.PushBack(30);
			d.PushBack(40);
			Assert::AreEqual(3U, d.Size());
			d.PopBack();
			Assert::AreEqual(2U, d.Size());
			auto Expression = [&d] {d.Get<int32_t>(2); };
			Assert::ExpectException<std::exception>(Expression);
			d.PopBack();
			d.PopBack();
			Assert::ExpectException<std::exception>(expression1);
			int intArray[3] = { 1, 2, 3 };
			d.SetStorage(intArray, 3);
			Assert::ExpectException<std::exception>(expression1);

			std::string s = "hello";
			Datum d3 = s;
			Assert::IsTrue(s == d3.Get<std::string>());
			d3.PushBack("lalala");
			Assert::IsTrue("lalala" == d3.Get<std::string>(1));
			d3.PopBack();
		}

		TEST_METHOD(ReserveFunctionTest)
		{
			Datum d;
			auto expression = [&d] {d.Reserve(5); };
			Assert::ExpectException<std::exception>(expression);
			d.SetType(DatumTypeEnum::Integer);
			d.Reserve(3);
			Assert::IsFalse(d.Reserve(2));
			int intArray[2] = { 1, 2 };
			d.SetStorage(intArray, 2);
			Assert::ExpectException<std::exception>(expression);
		}

		TEST_METHOD(ResizeFunctionTest)
		{
			Datum d = 10;
			d.PushBack(20);
			d.PushBack(30);
			d.PushBack(40);
			d.Resize(2);
			auto Expression = [&d] {d.Get<int32_t>(2); };
			Assert::ExpectException<std::exception>(Expression);
			Assert::AreEqual(10, d.Get<int32_t>());
			Assert::AreEqual(20, d.Get<int32_t>(1));
			Assert::AreEqual(2U, d.Size());
			d.Resize(5);
			Assert::AreEqual(5U, d.Size());

			string s = "hello";
			Datum d1 = s;
			d1.Resize(3);
		}

		TEST_METHOD(ScalarEqualityOperatorTest)
		{
			Datum d = 10;
			Assert::IsTrue(d == 10);
			Assert::IsFalse(d == 20.5f);

			Datum d1 = 10.5f;
			Assert::IsTrue(d1 == 10.5f);
			Assert::IsFalse(d1 == 20.5f);
			Assert::IsFalse(d1 == 5);

			string s = "Hello";
			Datum d2 = s;
			Assert::IsTrue(d2 == s);
			Assert::IsFalse(d2 == "bleh");

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };
			Datum dv = v1;
			Assert::IsTrue(dv == v1);
			Assert::IsFalse(dv == v2);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}

			Datum dm = m1;
			Assert::IsTrue(dm == m1);
			Assert::IsFalse(dm == m2);

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr = r;
			Assert::IsTrue(dr == r);
			dr.Set(r1);
			Assert::IsTrue(dr == r1);
			Assert::IsFalse(dr == r);
		}

		TEST_METHOD(ScalarInEqualityTest)
		{
			Datum d = 10;
			Assert::IsFalse(d != 10);
			Assert::IsTrue(d != 20.5f);

			Datum d1 = 10.5f;
			Assert::IsFalse(d1 != 10.5f);
			Assert::IsTrue(d1 != 20.5f);
			Assert::IsTrue(d1 != 5);

			string s = "Hello";
			Datum d2 = s;
			Assert::IsFalse(d2 != s);
			Assert::IsTrue(d2 != "bleh");

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };
			Datum dv = v1;
			Assert::IsFalse(dv != v1);
			Assert::IsTrue(dv != v2);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}

			Datum dm = m1;
			Assert::IsFalse(dm != m1);
			Assert::IsTrue(dm != m2);

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr = r;
			Assert::IsFalse(dr != r);
			dr.Set(r1);
			Assert::IsFalse(dr != r1);
			Assert::IsTrue(dr != r);
		}

		TEST_METHOD(EqualityOperatorTest)
		{
			Datum d = 10;
			d.PushBack(20);
			d.PushBack(30);
			Datum d1 = d;
			Assert::IsTrue(d1 == d);
			d.Resize(5);
			Assert::IsFalse(d1 == d);
			d1.Resize(5);
			Assert::IsTrue(d1 == d);
			float f = 15.54f;
			Datum d2 = f;
			Assert::AreEqual(f, d2.Get<float>());
			Assert::IsFalse(d2 == d1);
			d1 = d2;
			Assert::AreEqual(f, d1.Get<float>());
			Assert::IsTrue(d1.Size() == d2.Size());
			d1.PushBack(10.2f);

			std::string s = "hello";
			Datum d3 = s;
			std::string s1 = "blah";
			d3.PushBack(s1);
			Assert::IsTrue(s == d3.Get<std::string>());
			Assert::IsTrue(s1 == d3.Get<std::string>(1));
			d1 = d3;
			Assert::IsTrue(s == d1.Get<std::string>());
			Assert::IsTrue(s1 == d1.Get<std::string>(1));
			Assert::IsTrue(DatumTypeEnum::String == d1.Type());
			Assert::IsTrue(d1 == d3);
			d1.PushBack("lalala");
			d3.PushBack("lel");
			Assert::IsFalse(d3 == d1);

			int intArray[5] = { 1, 2, 3, 4 ,5 };
			Datum de;
			de.SetStorage(intArray, 5);
			d1 = de;
			Assert::AreEqual(1, d1.Get<int32_t>());
			Datum du;
			d1 = du;
			Assert::IsTrue(du == d1);
			Assert::IsTrue(DatumTypeEnum::Unknown == d1.Type());

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr = r;
			dr.PushBack(r1);
			d1 = dr;
			Assert::IsTrue(dr == d1);
			dr.PushBack(r);
			d1.PushBack(r1);
			Assert::IsFalse(dr == d1);
		}


		TEST_METHOD(InEqualityOperatorTest)
		{
			Datum d = 10;
			d.PushBack(20);
			d.PushBack(30);
			Datum d1 = d;
			Assert::IsFalse(d1 != d);
			d.Resize(5);
			Assert::IsTrue(d1 != d);
			d1.Resize(5);
			Assert::IsFalse(d1 != d);

			float f = 15.54f;
			Datum d2 = f;
			Assert::AreEqual(f, d2.Get<float>());
			Assert::IsTrue(d2 != d1);
			
			std::string s = "hello";
			Datum d3 = s;
			std::string s1 = "blah";
			d3.PushBack(s1);
			d1 = d3;
			Assert::IsFalse(d1 != d3);

			int intArray[5] = { 1, 2, 3, 4 ,5 };
			Datum de;
			de.SetStorage(intArray, 5);
			d1 = de;
			Datum du;
			d1 = du;
			Assert::IsFalse(du != d1);

			Foo foo(10);
			Foo foo1(20);
			RTTI* r = &foo;
			RTTI* r1 = &foo1;
			Datum dr = r;
			dr.PushBack(r1);
			d1 = dr;
			Assert::IsFalse(dr != d1);
		}

		TEST_METHOD(SetStorageTest)
		{
			Datum d;
			int intArray[5] = { 1, 2, 3, 4, 5 };
			d.SetStorage(intArray, 5);
			d.Set(5);
			Assert::AreEqual(5, intArray[0]);
			auto e1 = [&d] {d.Remove(1); };
			Assert::ExpectException<std::exception>(e1);
			auto w1 = [&d] {d.RemoveAtIndex(1); };
			Assert::ExpectException<std::exception>(w1);
			
			float floatArray[5] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
			auto Expression = [&d, &floatArray] {d.SetStorage(floatArray, 5); };
			Assert::ExpectException < std::exception>(Expression);
			Datum d1;
			d1.SetStorage(floatArray, 5);
			d = d1;
			Assert::IsTrue(d1.Type() == d.Type());
			auto e2 = [&d1] {d1.Remove(1.0f); };
			Assert::ExpectException<std::exception>(e2);
			auto w2 = [&d1] {d1.RemoveAtIndex(1); };
			Assert::ExpectException<std::exception>(e1);

			string stringArray[2] = { "hello", "blah" };
			Datum d2 = "bye";
			auto Expression1 = [&d2, &stringArray] {d2.SetStorage(stringArray, 0); };
			Assert::ExpectException < std::exception>(Expression1);
			d2.SetStorage(stringArray, 2);
			Assert::IsTrue(stringArray[0] == d2.Get<string>());
			auto e3 = [&d2] {d2.Remove("hello"); };
			Assert::ExpectException<std::exception>(e3);
			auto w3 = [&d2] {d2.RemoveAtIndex(1); };
			Assert::ExpectException<std::exception>(w3);

			vec4 v1[2] = { { 1.0f, 2.0f, 3.0f, 4.0f },{ 5.0f, 6.0f, 7.0f, 8.0f } };
			Datum d3;
			d3.SetStorage(v1, 2);
			Assert::IsTrue(v1[0] == d3.Get<vec4>());
			auto e4 = [&d3,&v1] {d3.Remove(v1[0]); };
			Assert::ExpectException<std::exception>(e4);
			auto w4 = [&d3] {d3.RemoveAtIndex(1); };
			Assert::ExpectException<std::exception>(w4);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}

			mat4 matrixArray[2] = { m1, m2 };
			Datum d5;
			d5.SetStorage(matrixArray, 2);
			Assert::IsTrue(d5.Get<mat4>() == matrixArray[0]);
			auto e5 = [&d5, &m1] {d5.Remove(m1); };
			Assert::ExpectException<std::exception>(e5);
			auto w5 = [&d5] {d5.RemoveAtIndex(1); };
			Assert::ExpectException<std::exception>(w5);


			Foo foo(10);
			Foo foo1(20);
			RTTI* r[2] = { &foo, &foo1};
			Datum d4;
			d4.SetStorage(r, 2);
			Assert::IsTrue(r[0] == d4.Get<RTTI*>());
			auto e6 = [&d4, &r] {d4.Remove(r[0]); };
			Assert::ExpectException<std::exception>(e6);
			auto w6 = [&d4] {d4.RemoveAtIndex(1); };
			Assert::ExpectException<std::exception>(w6);
		}

		TEST_METHOD(SetTypeFunctionTest)
		{
			Datum d;
			d.SetType(DatumTypeEnum::Integer);
			Assert::IsTrue(DatumTypeEnum::Integer == d.Type());
			auto expression = [&d] {d.SetType(DatumTypeEnum::String);  };
			Assert::ExpectException <std::exception>(expression);
			Datum d1 = 20.0f;
			auto expression1 = [&d1] {d1.SetType(DatumTypeEnum::String);  };
			Assert::ExpectException <std::exception>(expression1);
		}

		TEST_METHOD(ToStringTest)
		{
			Datum d;
			int32_t n = 10;
			auto expression = [&d] {d.ToString(0); };
			Assert::ExpectException<std::exception>(expression);
			d.SetType(DatumTypeEnum::Integer);
			d.PushBack(n);
			std::string s = d.ToString();
			Assert::AreEqual(stoi(s), n);

			float f = 15.54f;
			Datum d2 = f;
			Assert::AreEqual(stof(d2.ToString()), f);

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			Datum d3 = v1;
			Assert::IsTrue(glm::to_string(v1) == d3.ToString());

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			Datum d4 = m1;
			Assert::IsTrue(glm::to_string(m1) == d4.ToString());

			string s1 = "hello";
			Datum d6 = s1;
			d6.ToString();


			Foo foo(10);
			RTTI* r = &foo;
			Datum dr = r;
			Assert::IsTrue(dr.ToString() == r->ToString());
		}


		TEST_METHOD(SetFromString)
		{
			Datum d;
			int n = 20;
			string s = std::to_string(n);
			auto expression = [&d, &s] {d.SetFromString(s); };
			Assert::ExpectException<std::exception>(expression);
			d.SetType(DatumTypeEnum::Integer);
			d = 10;
			Assert::AreEqual(d.Get<int32_t>(), 10);
			d.SetFromString(s);
			Assert::AreEqual(d.Get<int32_t>(), n);

			Datum d1 = 10.9f;
			s = std::to_string(11.9f);
			d1.SetFromString(s);
			auto expression1 = [&d1, &s] {d1.SetFromString(s,20); };
			Assert::ExpectException<std::exception>(expression1);
			Assert::IsTrue(d1.Get<float>() == 11.9f);

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };
			Datum d2 = v1;
			s = glm::to_string(v2);
			d2.SetFromString(s);
			Assert::IsTrue(d2.Get<vec4>() == v2);

			string s1 = "hello";
			Datum d6 = s1;
			d6.SetFromString(s1);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}
			Datum dm = m1;
			s = glm::to_string(m2);
			dm.SetFromString(s);
			Assert::IsTrue(dm.Get<mat4>() == m2);
		}

		TEST_METHOD(RemoveTest)
		{
			Datum d = 10;
			d.PushBack(20);
			auto e = [&d] {d.Remove(10.6f); };
			Assert::ExpectException<std::exception>(e);
			auto ex = [&d] {d.RemoveAtIndex(10); };
			Assert::ExpectException<std::exception>(ex);
			d.Remove(50);
			d.Remove(10);
			d.RemoveAtIndex(0);
			
			Datum d1 = 10.0f;
			d1.PushBack(20.0f);
			auto e1 = [&d1] {d1.Remove(10); };
			Assert::ExpectException<std::exception>(e1);
			auto ex1 = [&d1] {d1.RemoveAtIndex(10); };
			Assert::ExpectException<std::exception>(ex1);
			d1.Remove(50.0f);
			d1.Remove(20.0f);
			d1.RemoveAtIndex(0);

			std::string s = "hello";
			std::string a = "bye";
			Datum d2 = s;
			d2.PushBack(a);
			auto e2 = [&d2] {d2.Remove(10.6f); };
			Assert::ExpectException<std::exception>(e2);
			auto ex2 = [&d2] {d2.RemoveAtIndex(10); };
			Assert::ExpectException<std::exception>(ex2);
			d2.Remove("blah");
			d2.Remove(s);
			d2.RemoveAtIndex(0);

			vec4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };
			vec4 v3 = { 5.0f, 6.0f, 7.0f, 9.0f };
			Datum d3 = v1;
			d3.PushBack(v2);
			auto e3 = [&d3] {d3.Remove(10.6f); };
			Assert::ExpectException<std::exception>(e3);
			auto ex3 = [&d3] {d3.RemoveAtIndex(10); };
			Assert::ExpectException<std::exception>(ex3);
			d3.Remove(v3);
			d3.Remove(v2);
			d3.RemoveAtIndex(0);

			mat4 m1;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m1[i][j] = 1.4f;
				}
			}
			mat4 m2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 2.4f;
				}
			}
			mat4 m3;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2[i][j] = 3.4f;
				}
			}

			Datum d4 = m1;
			d4.PushBack(m2);
			auto e4 = [&d4] {d4.Remove(10.6f); };
			Assert::ExpectException<std::exception>(e3);
			auto ex4 = [&d4] {d4.RemoveAtIndex(10); };
			Assert::ExpectException<std::exception>(ex4);
			d4.Remove(m3);
			d4.Remove(m2);
			d4.RemoveAtIndex(0);


			Foo foo(10);
			Foo foo1(20);
			Foo foo2(20);
			RTTI* r1 = &foo;
			RTTI* r2 = &foo1;
			RTTI* r3 = &foo2;
			Datum d5 = r1;
			d5.PushBack(r2);
			auto e5 = [&d5] {d5.Remove(10.6f); };
			Assert::ExpectException<std::exception>(e5);
			auto ex5 = [&d5] {d5.RemoveAtIndex(10); };
			Assert::ExpectException<std::exception>(ex5);
			d5.Remove(r3);
			d5.Remove(r2);
			d5.RemoveAtIndex(0);

			Scope s1;
			Scope s2;
			Scope s3;
			s3.Append("lol");
			Datum d6 = &s1;
			d6.PushBack(&s2);
			auto e6 = [&d6] {d6.Remove(10.6f); };
			Assert::ExpectException<std::exception>(e6);
			auto ex6 = [&d6] {d6.RemoveAtIndex(10); };
			Assert::ExpectException<std::exception>(ex6);
			d6.Remove(&s3);
			d6.Remove(&s2);
			d6.RemoveAtIndex(0);
		}
	private:
		static _CrtMemState sStartMemState;
	};
	_CrtMemState DatumTest::sStartMemState;
}


