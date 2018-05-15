#include "pch.h"
#include "HashMap.h"
#include "CppUnitTest.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace UnitTestLibraryDesktop
{
	class CustomHash
	{
	public:
		uint32_t operator()(int data) const
		{
			return data + 1;
		}
	};

	class FooHash
	{
	public:
		uint32_t operator()(Foo data) const
		{
			return (31 * data.Data());
		}
	};

	TEST_CLASS(HashMapTest)
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

		TEST_METHOD(HashTest)
		{
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			auto it = h.begin();
			Assert::AreEqual(10, (*it).second);
			Assert::IsFalse(h.ContainsKey(6));
			Assert::AreEqual(10, h[5]);
			h.Insert(b, wasInserted);
			Assert::AreEqual(2U, h.Size());
			h.Remove(a.first);
			Assert::IsTrue(h.ContainsKey(20));
			Assert::IsFalse(h.ContainsKey(5));
			h[5] = 20;
			Assert::AreEqual(20, (*h.Find(5)).second);
			const HashMap<int, int, CustomHash>& h1 = h;
			h1.At(5);
		}

		TEST_METHOD(InsertTest)
		{
			//PRIMITIVE TYPE
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			auto it = h.begin();
			Assert::IsTrue(wasInserted);
			Assert::AreEqual(a.second, (*it).second);
			Assert::IsFalse(h.ContainsKey(6));
			Assert::AreEqual(a.second, h[5]);
			h.Insert(b, wasInserted);
			Assert::AreEqual(b.second, h[20]);
			it = h.begin();
			Assert::AreEqual(40, it->second);
			Assert::AreEqual(a.second, (++it)->second);
			h.Insert(a, wasInserted);
			Assert::IsFalse(wasInserted);

			//STRING TYPE
			std::pair<std::string, int> c("Hell", 10);
			std::pair<std::string, int> d("foo", 40);
			HashMap<std::string, int> hs;
			hs.Insert(c, wasInserted);
			auto it1 = hs.begin();
			Assert::IsTrue(wasInserted);
			Assert::AreEqual(c.second, (*it1).second);
			Assert::IsFalse(hs.ContainsKey("blah"));
			Assert::AreEqual(c.second, hs["Hell"]);
			hs.Insert(d, wasInserted);
			Assert::AreEqual(d.second, hs["foo"]);
			hs.Insert(c, wasInserted);
			Assert::IsFalse(wasInserted);

			//CHAR* TYPE
			std::pair<char*, int> e("Hell", 10);
			std::pair<char*, int> f("foo", 40);
			HashMap<char*, int> hc;
			hc.Insert(e);
			auto it2 = hc.begin();
			Assert::AreEqual(e.second, (*it2).second);
			Assert::IsFalse(hc.ContainsKey("blah"));
			Assert::AreEqual(e.second, hs["Hell"]);
			hc.Insert(f);
			Assert::AreEqual(f.second, hs["foo"]);
			hc.Insert(e, wasInserted);
			Assert::IsFalse(wasInserted);

			//USER DEFINED TYPE
			Foo foo1(10);
			Foo foo2(20);
			std::pair<Foo, int> f1(foo1, 50);
			std::pair<Foo, int> f2(foo2, 60);
			HashMap<Foo, int, FooHash> hf;
			hf.Insert(f1, wasInserted);
			Assert::IsTrue(wasInserted);
			Assert::AreEqual(f1.second, hf.Find(f1.first)->second);
			Assert::AreEqual(f1.second, hf[f1.first]);
			hf.Insert(f2, wasInserted);
			Assert::AreEqual(f2.second, hf.Find(f2.first)->second);
			hf.Insert(f1, wasInserted);
			Assert::IsFalse(wasInserted);
		}

		TEST_METHOD(FindTest)
		{
			//PRIMITIVE TYPE
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			h.Insert(b, wasInserted);
			Assert::AreEqual(a.second, h.Find(a.first)->second);
			Assert::AreEqual(b.second, h.Find(b.first)->second);
			Assert::IsTrue(h.end() == h.Find(b.second));

			//STRING TYPE
			std::pair<std::string, int> c("Hell", 10);
			std::pair<std::string, int> d("foo", 40);
			HashMap<std::string, int> hs;
			hs.Insert(c, wasInserted);
			hs.Insert(d, wasInserted);
			Assert::AreEqual(c.second, hs.Find(c.first)->second);
			Assert::AreEqual(d.second, hs.Find(d.first)->second);
			Assert::IsTrue(hs.end() == hs.Find("Blah"));

			//CHAR* TYPE
			std::pair<char*, int> e("Hell", 10);
			std::pair<char*, int> f("foo", 40);
			HashMap<char*, int> hc;
			hc.Insert(e, wasInserted);
			hc.Insert(f, wasInserted);
			Assert::AreEqual(e.second, hc.Find(e.first)->second);
			Assert::AreEqual(f.second, hc.Find(f.first)->second);
			Assert::IsTrue(hc.end() == hc.Find("Blah"));

			//USER DEFINED TYPE
			Foo foo1(10);
			Foo foo2(20);
			Foo foo3(30);
			std::pair<Foo, int> f1(foo1, 50);
			std::pair<Foo, int> f2(foo2, 60);
			std::pair<Foo, int> f3(foo3, 70);
			HashMap<Foo, int, FooHash> hf;
			hf.Insert(f1, wasInserted);
			hf.Insert(f2, wasInserted);
			Assert::AreEqual(f1.second, hf.Find(f1.first)->second);
			Assert::AreEqual(f2.second, hf.Find(f2.first)->second);
			Assert::IsTrue(hf.end() == hf.Find(foo3));
		}

		TEST_METHOD(beginTest)
		{
			//PRIMITIVE TYPE
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			h.Insert(b, wasInserted);
			Assert::IsTrue(*(h.begin()) == b);
			h.Remove(b.first);
			Assert::IsTrue(*(h.begin()) == a);
			h.Remove(a.first);
			auto expression = [&h] {h.begin(); };
			Assert::ExpectException<std::exception>(expression);

			//STRING TYPE
			std::pair<std::string, int> c("Hell", 10);
			std::pair<std::string, int> d("foo", 40);
			HashMap<std::string, int> hs;
			hs.Insert(c, wasInserted);
			hs.Insert(d, wasInserted);
			Assert::IsTrue(*(hs.begin()) == d);
			hs.Remove(d.first);
			Assert::IsTrue(*(hs.begin()) == c);
			hs.Remove(c.first);

			//CHAR* TYPE
			std::pair<char*, int> e("Hell", 10);
			std::pair<char*, int> f("foo", 40);
			HashMap<char*, int> hc;
			hc.Insert(e, wasInserted);
			hc.Insert(f, wasInserted);
			Assert::IsTrue(hc.begin()->second == 40);
			hc.Remove(f.first);
			Assert::IsTrue(hc.begin()->second == 10);
			hc.Remove(e.first);


			//USER DEFINED TYPE
			Foo foo1(10);
			Foo foo2(20);
			std::pair<Foo, int> f1(foo1, 50);
			std::pair<Foo, int> f2(foo2, 60);
			HashMap<Foo, int, FooHash> hf;
			hf.Insert(f1, wasInserted);
			hf.Insert(f2, wasInserted);
			Assert::IsTrue(hf.begin()->second == 50);
			hf.Remove(f1.first);
			Assert::IsTrue(hf.begin()->second == 60);
			hf.Remove(f2.first);
		}

		TEST_METHOD(IndexOfOperatorTest)
		{
			//PRIMITIVE TYPE
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			Assert::IsTrue(h[a.first] == a.second);
			h[b.first] = b.second;
			Assert::IsTrue(h.Find(b.first)->second == b.second);
			

			//STRING TYPE
			std::pair<std::string, int> c("Hell", 10);
			std::pair<std::string, int> d("foo", 40);
			HashMap<std::string, int> hs;
			hs.Insert(c, wasInserted);
			Assert::IsTrue(hs[c.first] == c.second);
			hs[d.first] = d.second;
			Assert::IsTrue(hs.Find(d.first)->second == d.second);


			//CHAR* TYPE
			std::pair<char*, int> e("Hell", 10);
			std::pair<char*, int> f("foo", 40);
			HashMap<char*, int> hc;
			hc.Insert(e, wasInserted);
			hc.Insert(f, wasInserted);
			Assert::IsTrue(hc[e.first] == e.second);
			hc[f.first] = f.second;
			Assert::IsTrue(hc.Find(f.first)->second == f.second);


			//USER DEFINED TYPE
			Foo foo1(10);
			Foo foo2(20);
			std::pair<Foo, int> f1(foo1, 50);
			std::pair<Foo, int> f2(foo2, 60);
			HashMap<Foo, int, FooHash> hf;
			hf.Insert(f1, wasInserted);
			Assert::IsTrue(hf[f1.first] == f1.second);
			hf[f2.first] = f2.second;
			Assert::IsTrue(hf.Find(f2.first)->second == f2.second);	
		}

		TEST_METHOD(SizeTest)
		{
			//PRIMITIVE TYPE
			std::pair<const int, int> a(5, 10);
			std::pair<const int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			h.Insert(b, wasInserted);
			Assert::AreEqual(2U, h.Size());
			h.Remove(a.first);
			Assert::AreEqual(1U, h.Size());
			h.Remove(b.first);
			Assert::AreEqual(0U, h.Size());

			//STRING TYPE
			std::pair<const std::string, int> c("Hell", 10);
			std::pair<const std::string, int> d("foo", 40);
			HashMap<std::string, int> hs;
			hs.Insert(c, wasInserted);
			hs.Insert(d, wasInserted);
			Assert::AreEqual(2U, hs.Size());
			hs.Remove(d.first);
			Assert::AreEqual(1U, hs.Size());
			hs.Remove(c.first);
			Assert::AreEqual(0U, hs.Size());

			//CHAR* TYPE
			std::pair<char*, int> e("Hell", 10);
			std::pair<char*, int> f("foo", 40);
			HashMap<char*, int> hc;
			hc.Insert(e, wasInserted);
			hc.Insert(f, wasInserted);
			Assert::AreEqual(2U, hc.Size());
			hc.Remove(f.first);
			Assert::AreEqual(1U, hc.Size());
			hc.Remove(e.first);
			Assert::AreEqual(0U, hc.Size());


			//USER DEFINED TYPE
			Foo foo1(10);
			Foo foo2(20);
			std::pair<Foo, int> f1(foo1, 50);
			std::pair<Foo, int> f2(foo2, 60);
			HashMap<Foo, int, FooHash> hf;
			hf.Insert(f1, wasInserted);
			hf.Insert(f2, wasInserted);
			Assert::AreEqual(2U, hf.Size());
			hf.Remove(f1.first);
			Assert::AreEqual(1U, hf.Size());
			hf.Remove(f2.first);
			Assert::AreEqual(0U, hf.Size());
		}

		TEST_METHOD(RemoveTest)
		{
			//PRIMITIVE TYPE
			std::pair<const int, int> a(5, 10);
			std::pair<const int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			h.Insert(b, wasInserted);
			Assert::AreEqual(2U, h.Size());
			Assert::IsTrue(h.Remove(a.first));
			Assert::AreEqual(1U, h.Size());
			h.Remove(b.first);
			Assert::AreEqual(0U, h.Size());
			Assert::IsFalse(h.Remove(a.first));

			//STRING TYPE
			std::pair<const std::string, int> c("Hell", 10);
			std::pair<const std::string, int> d("foo", 40);
			HashMap<std::string, int> hs;
			hs.Insert(c, wasInserted);
			hs.Insert(d, wasInserted);
			Assert::AreEqual(2U, hs.Size());
			hs.Remove(d.first);
			Assert::AreEqual(1U, hs.Size());
			hs.Remove(c.first);
			Assert::AreEqual(0U, hs.Size());

			//CHAR* TYPE
			std::pair<char*, int> e("Hell", 10);
			std::pair<char*, int> f("foo", 40);
			HashMap<char*, int> hc;
			hc.Insert(e, wasInserted);
			hc.Insert(f, wasInserted);
			Assert::AreEqual(2U, hc.Size());
			hc.Remove(f.first);
			Assert::AreEqual(1U, hc.Size());
			hc.Remove(e.first);
			Assert::AreEqual(0U, hc.Size());


			//USER DEFINED TYPE
			Foo foo1(10);
			Foo foo2(20);
			std::pair<Foo, int> f1(foo1, 50);
			std::pair<Foo, int> f2(foo2, 60);
			HashMap<Foo, int, FooHash> hf;
			hf.Insert(f1, wasInserted);
			hf.Insert(f2, wasInserted);
			Assert::AreEqual(2U, hf.Size());
			hf.Remove(f1.first);
			Assert::AreEqual(1U, hf.Size());
			hf.Remove(f2.first);
			Assert::AreEqual(0U, hf.Size());
		}


		TEST_METHOD(clearTest)
		{
			//PRIMITIVE TYPE
			std::pair<const int, int> a(5, 10);
			std::pair<const int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			h.Insert(b, wasInserted);
			Assert::AreEqual(2U, h.Size());
			h.Clear();
			Assert::AreEqual(0U, h.Size());
			Assert::IsFalse(h.ContainsKey(a.first));
		}

		TEST_METHOD(HashFunctorTest)
		{
			HashFunction<char*> charHash;
			char* a = "Hello";
			char b[6];
			a; b;
			strcpy_s(b, sizeof(b), a);
			uint32_t hash = charHash(a);
			Assert::AreEqual(hash, charHash(b));

			HashFunction<std::string> stringHash;
			std::string s1 = "Hello";
			std::string s2 = s1;
			Assert::AreEqual(stringHash(s1), stringHash(s2));
		}

		TEST_METHOD(ContainsKeyTest)
		{
			//PRIMITIVE TYPE
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			h.Insert(b, wasInserted);
			Assert::IsTrue(h.ContainsKey(a.first));
			Assert::IsTrue(h.ContainsKey(b.first));
			Assert::IsFalse(h.ContainsKey(a.second));

			//STRING TYPE
			std::pair<std::string, int> c("Hell", 10);
			std::pair<std::string, int> d("foo", 40);
			HashMap<std::string, int> hs;
			hs.Insert(c, wasInserted);
			hs.Insert(d, wasInserted);
			int data;
			Assert::IsTrue(hs.ContainsKey(c.first, data));
			Assert::AreEqual(data, c.second);

			//CHAR* TYPE
			std::pair<char*, int> e("Hell", 10);
			std::pair<char*, int> f("foo", 40);
			HashMap<char*, int> hc;
			hc.Insert(e, wasInserted);
			hc.Insert(f, wasInserted);
			Assert::IsTrue(hc.ContainsKey(e.first));
			const HashMap<char*, int> consthc = hc;
			Assert::IsTrue(consthc.ContainsKey(e.first, data));
			Assert::AreEqual(data, e.second);
			Assert::IsFalse(consthc.ContainsKey("blah", data));
			
			//USER DEFINED TYPE
			Foo foo1(10);
			Foo foo2(20);
			Foo foo3(30);
			std::pair<Foo, int> f1(foo1, 50);
			std::pair<Foo, int> f2(foo2, 60);
			std::pair<Foo, int> f3(foo3, 70);
			HashMap<Foo, int, FooHash> hf;
			hf.Insert(f1, wasInserted);
			hf.Insert(f2, wasInserted);
			Assert::IsTrue(hf.ContainsKey(foo1, data));
			Assert::AreEqual(data, f1.second);
			Assert::IsTrue(hf.ContainsKey(foo2, data));
			Assert::IsFalse(hf.ContainsKey(foo3));
		}

		TEST_METHOD(AtTest)
		{
			//PRIMITIVE TYPE
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			Assert::IsTrue(h.At(a.first) == a.second);
			h[b.first] = b.second;
			Assert::IsTrue(h.At(b.first) == b.second);
			auto expression = [&h, &b] {h.At(b.second); };
			Assert::ExpectException<std::exception>(expression);
			const HashMap<int, int, CustomHash> consth = h;
			Assert::IsTrue(consth.At(a.first) == a.second);
			auto expression1 = [&consth, &b] {consth.At(b.second); };
			Assert::ExpectException<std::exception>(expression1);
			

			//STRING TYPE
			std::pair<std::string, int> c("Hell", 10);
			std::pair<std::string, int> d("foo", 40);
			HashMap<std::string, int> hs;
			hs.Insert(c, wasInserted);
			Assert::IsTrue(hs.At(c.first) == c.second);
			hs[d.first] = d.second;
			Assert::IsTrue(hs.At(d.first) == d.second);


			//CHAR* TYPE
			std::pair<char*, int> e("Hell", 10);
			std::pair<char*, int> f("foo", 40);
			HashMap<char*, int> hc;
			hc.Insert(e, wasInserted);
			hc.Insert(f, wasInserted);
			Assert::IsTrue(hc.At(e.first) == e.second);
			hc[f.first] = f.second;
			Assert::IsTrue(hc.At(f.first) == f.second);


			//USER DEFINED TYPE
			Foo foo1(10);
			Foo foo2(20);
			std::pair<Foo, int> f1(foo1, 50);
			std::pair<Foo, int> f2(foo2, 60);
			HashMap<Foo, int, FooHash> hf;
			hf.Insert(f1, wasInserted);
			Assert::IsTrue(hf.At(f1.first) == f1.second);
			hf[f2.first] = f2.second;
			Assert::IsTrue(hf.At(f2.first) == f2.second);
		}

		TEST_METHOD(IteratorIncrementTest)
		{
			//PRIMITIVE TYPE
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			h.Insert(b, wasInserted);
			auto it = h.begin();
			Assert::IsTrue(*it == b);
			it++;
			Assert::IsTrue(*it == a);
			++it;
			Assert::IsTrue(it == h.end());
			auto expression = [&it] {it++; };
			Assert::ExpectException<std::exception>(expression);

			//STRING TYPE
			std::pair<std::string, int> c("Hell", 10);
			std::pair<std::string, int> d("foo", 40);
			HashMap<std::string, int> hs;
			hs.Insert(c, wasInserted);
			hs.Insert(d, wasInserted);
			auto it1 = hs.begin();
			Assert::IsTrue(*it1 == d);
			++it1;
			Assert::IsTrue(*it1 == c);
			it1++;
			Assert::IsTrue(it1 == hs.end());
			auto expression1 = [&it1] {++it1; };
			Assert::ExpectException<std::exception>(expression1);


			//CHAR* TYPE
			std::pair<char*, int> e("Hell", 10);
			std::pair<char*, int> f("foo", 40);
			HashMap<char*, int> hc;
			hc.Insert(e, wasInserted);
			hc.Insert(f, wasInserted);
			auto it2 = hc.begin();
			Assert::IsTrue(it2->second == 40);
			++it2;
			Assert::IsTrue(it2->second == 10);

			//USER DEFINED TYPE
			Foo foo1(10);
			Foo foo2(20);
			std::pair<Foo, int> f1(foo1, 50);
			std::pair<Foo, int> f2(foo2, 60);
			HashMap<Foo, int, FooHash> hf;
			hf.Insert(f1, wasInserted);
			hf.Insert(f2, wasInserted);
			auto it3 = hf.begin();
			Assert::IsTrue(it3->second == 50);
			it3++;
			Assert::IsTrue(it3->second == 60);
		}

		TEST_METHOD(IteratorEqualityTest)
		{
			//PRIMITIVE TYPE
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			std::pair<int, int> c(30, 50);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			h.Insert(b, wasInserted);
			h.Insert(c);
			auto it = h.begin();
			auto it1 = h.Find(b.first);
			Assert::IsTrue(it == it1);
			it++;
			Assert::IsFalse(it == it1);
			++it1;
			Assert::IsTrue(it == it1);
			++it;
			it1 = h.end();
			Assert::IsFalse(it == it1);
			it++;
			Assert::IsTrue(it == it1);
			HashMap<int, int, CustomHash> h1;
			h1.Insert(a);
			it = h1.begin();
			it1 = h.begin();
			Assert::IsFalse(it == it1);
			const HashMap<int, int, CustomHash> hc = h;
			it = h.begin();
			it1 = hc.begin();
			Assert::IsFalse(it == it1);
		}

		TEST_METHOD(IteratorInequalityTest)
		{
			//PRIMITIVE TYPE
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			std::pair<int, int> c(30, 50);
			bool wasInserted;
			HashMap<int, int, CustomHash> h;
			h.Insert(a, wasInserted);
			h.Insert(b, wasInserted);
			h.Insert(c);
			auto it = h.begin();
			auto it1 = h.Find(b.first);
			Assert::IsFalse(it != it1);
			it++;
			Assert::IsTrue(it != it1);
			++it1;
			Assert::IsFalse(it != it1);
			++it;
			it1 = h.end();
			Assert::IsTrue(it != it1);
			it++;
			Assert::IsFalse(it != it1);
			HashMap<int, int, CustomHash> h1;
			h1.Insert(a);
			it = h1.begin();
			it1 = h.begin();
			Assert::IsTrue(it != it1);
			const HashMap<int, int, CustomHash> hc = h;
			it = h.begin();
			it1 = hc.begin();
			Assert::IsTrue(it != it1);
		}

		TEST_METHOD(IteratorDereferenceTest)
		{
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			HashMap<int, int, CustomHash> h;
			h.Insert(a);
			h.Insert(b);
			auto it = h.end();
			auto expression = [&it] {*it; };
			Assert::ExpectException<std::exception>(expression);
			it = h.begin();
			Assert::IsTrue(*it == b);
			Assert::IsTrue(*(++it) == a);
			const HashMap<int, int, CustomHash> hc = h;
			auto it1 = hc.end();
			auto expression1 = [&it1] {*it1; };
			Assert::ExpectException<std::exception>(expression1);
			it1 = hc.begin();
			Assert::IsTrue(*it1 == b);
			Assert::IsTrue(*(++it1) == a);
			const auto it2 = h.begin();
			Assert::IsTrue(*it2 == b);
		}

		TEST_METHOD(IteratorArrowOperatorTest)
		{
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			HashMap<int, int, CustomHash> h;
			h.Insert(a);
			h.Insert(b);
			auto it = h.end();
			auto expression = [&it] {it->first; };
			Assert::ExpectException<std::exception>(expression);
			it = h.begin();
			Assert::IsTrue(it->second == b.second);
			Assert::IsTrue((++it)->second == a.second);
			const HashMap<int, int, CustomHash> hc = h;
			auto it1 = hc.end();
			auto expression1 = [&it1] {it1->first; };
			Assert::ExpectException<std::exception>(expression1);
			it1 = hc.begin();
			Assert::IsTrue(it1->second == b.second);
			Assert::IsTrue((++it1)->second == a.second);
			const auto it2 = h.begin();
			Assert::IsTrue(it2->second == b.second);
		}

		TEST_METHOD(IntializerListTest)
		{
			std::pair<int, int> a(5, 10);
			std::pair<int, int> b(20, 40);
			HashMap<int, int> h{ a , b };
			auto it = h.begin();
			Assert::IsTrue(*it == b);
			Assert::IsTrue(*(++it) == a);


		}


	};
	_CrtMemState HashMapTest::sStartMemState;
}
