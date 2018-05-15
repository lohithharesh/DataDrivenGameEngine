#include "pch.h"
#include "Event.h"
#include "FooSubscriber.h"
#include "Foo.h"
#include "GameTime.h"
#include "EventQueue.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EventTest)
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

		TEST_METHOD(MultipleEventsTest)
		{
			Foo f(10);
			Foo f1(20);
			std::shared_ptr<Event<Foo>> e = std::make_shared<Event<Foo>>(f);
			std::shared_ptr<Event<Foo>> e1 = std::make_shared<Event<Foo>>(f1);
			Assert::IsTrue(f == e->Message());
			FooSubscriber fs;
			EventQueue eq;
			GameTime gameTime;
			fs.wasNotified = false;
			fs.mData = 0;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(0)));
			eq.Enqueue(e, gameTime, std::chrono::seconds(1));
			eq.Enqueue(e1, gameTime);
			Assert::IsTrue(e->Delay() == std::chrono::seconds(1));
			Assert::AreEqual(2U, eq.Size());
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(1)));
			eq.Update(gameTime);
			Assert::AreEqual(1U, eq.Size());
			Assert::IsTrue(fs.wasNotified);
			Assert::AreEqual(20, fs.mData);
			fs.wasNotified = false;
			eq.Send(e);
			Assert::IsTrue(eq.IsEmpty());
			Assert::IsTrue(fs.wasNotified);
			Assert::AreEqual(10, fs.mData);
		}

		TEST_METHOD(EventQueueTest)
		{
			Foo f(10);
			std::shared_ptr<Event<Foo>> e = std::make_shared<Event<Foo>>(f);
			Assert::IsTrue(f == e->Message());
			FooSubscriber fs;
			EventQueue eq;
			GameTime gameTime;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(0)));
			Assert::AreEqual(0U, eq.Size());
			eq.Enqueue(e, gameTime);
			Assert::IsTrue(e->TimeEnqueued() == gameTime.CurrentTime());
			Assert::AreEqual(1U, eq.Size());
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(1)));
			eq.Update(gameTime);
			Assert::IsTrue(fs.wasNotified);
			Assert::AreEqual(0U, eq.Size());
			Assert::AreEqual(10, fs.mData);

			fs.wasNotified = false;
			fs.mData = 0;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(0)));
			eq.Enqueue(e, gameTime, std::chrono::seconds(1));
			Assert::IsTrue(e->Delay() == std::chrono::seconds(1));
			Assert::AreEqual(1U, eq.Size());
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(1)));
			eq.Update(gameTime);
			Assert::AreEqual(1U, eq.Size());
			Assert::IsFalse (fs.wasNotified);
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(2)));
			eq.Update(gameTime);
			Assert::AreEqual(0U, eq.Size());
			Assert::IsTrue(fs.wasNotified);
			Assert::AreEqual(10, fs.mData);

			eq.Enqueue(e, gameTime, std::chrono::seconds(1));
			Assert::AreEqual(1U, eq.Size());
			eq.Clear();
			Assert::AreEqual(0U, eq.Size());
		}

		TEST_METHOD(SendTest)
		{
			Foo f(10);
			std::shared_ptr<Event<Foo>> e = std::make_shared<Event<Foo>>(f);
			Assert::IsTrue(f == e->Message());
			FooSubscriber fs;
			EventQueue eq;
			GameTime gameTime;
			fs.wasNotified = false;
			fs.mData = 0;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(0)));
			eq.Enqueue(e, gameTime, std::chrono::seconds(1));
			Assert::IsTrue(e->Delay() == std::chrono::seconds(1));
			Assert::AreEqual(1U, eq.Size());
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(1)));
			eq.Send(e);
			Assert::AreEqual(0U, eq.Size());
			Assert::IsTrue(fs.wasNotified);
			Assert::AreEqual(10, fs.mData);
		}
		
		

		TEST_METHOD(UnsubscribeTest)
		{
			Foo f(10);
			std::shared_ptr<Event<Foo>> e = std::make_shared<Event<Foo>>(f);
			Assert::IsTrue(f == e->Message());
			FooSubscriber fs;
			EventQueue eq;
			GameTime gameTime;
			fs.wasNotified = false;
			fs.mData = 0;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(0)));
			eq.Enqueue(e, gameTime, std::chrono::seconds(1));
			Assert::IsTrue(e->Delay() == std::chrono::seconds(1));
			Assert::AreEqual(1U, eq.Size());
			Event<Foo>::UnsubscribeAll();
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::seconds(1)));
			Assert::AreEqual(1U, eq.Size());
			Assert::IsFalse(fs.wasNotified);
			Assert::AreNotEqual(10, fs.mData);
		}
		
	private:
		static _CrtMemState sStartMemState;
	};
	_CrtMemState EventTest::sStartMemState;
}