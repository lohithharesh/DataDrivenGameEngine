#include "pch.h"
#include "World.h"
#include "ScopeParseHelper.h"
#include "Furniture.h"
#include "ActionList.h"
#include "DebugAction.h"
#include "ActionListIf.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionExpression.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(WorldTest)
	{
	public:
		ConcreteFurnitureFactory ff;
		ConcreteEntityFactory ee;
		ConcreteDebugActionFactory da;
		ConcreteActionListFactory al;
		ConcreteActionListIfFactory ai;
		ConcreteActionCreateActionFactory aca;
		ConcreteActionDestroyActionFactory ada;
		ConcreteActionExpressionFactory ae;
		TEST_METHOD_INITIALIZE(Initialize)
		{
			RegisterType(World);
			RegisterType(Entity);
			RegisterType(Sector);
			RegisterType(Furniture);
			RegisterType(Action);
			RegisterType(ActionList);
			RegisterType(ActionListIf);
			RegisterType(ActionCreateAction);
			RegisterType(ActionDestroyAction);
			RegisterType(DebugAction);
			RegisterType(ActionExpression);
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

		TEST_METHOD(ParseTest)
		{
			World tempWorld;
			JsonParseMaster::SharedData* sharedData = new ScopeParseHelper::ScopeSharedData(tempWorld);
			JsonParseMaster master(*sharedData);
			ScopeParseHelper sh;
			master.AddHelper(sh);
			master.ParseFromFile("Script/World.json");
			Assert::IsTrue(&(tempWorld.Find("Sectors")->Get<Scope>()) != nullptr);
			Sector* sector = tempWorld.Find("Sectors")->Get<Scope>().As<Sector>();
			Assert::IsTrue(sector->Name() == "BedRoom");
			Entity* entity = sector->Find("Entities")->Get<Scope>().As<Entity>();
			Assert::IsTrue(entity->Name() == "Chair");
			Assert::IsTrue(entity->Find("Height")->Get<float>() == 20.0f);
			Furniture* f = entity->As<Furniture>();
			Assert::IsNotNull(f);
			Assert::IsTrue(f->mHeight == 20.0f);
			entity = sector->Find("Entities")->Get<Scope>(1).As<Entity>();
			Assert::IsTrue(entity->Name() == "Table");
			Assert::IsTrue(entity->Find("Height")->Get<float>() == 30.0f);
			f = entity->As<Furniture>();
			Assert::IsTrue(f->mHeight == 30.0f);
			Sector* hall = tempWorld.Find("Sectors")->Get<Scope>(1).As<Sector>();
			Assert::IsTrue(hall->Name() == "Hallway");
			Assert::IsTrue(hall->Entities()[0].As<Furniture>()->Name() == "Cupboard");
			Assert::IsTrue(hall->Entities()[0].Find("Height")->Get<float>() == 40.0f);
			Assert::IsTrue(hall->Entities()[0].Find("Safebox")->Get<Scope>().Find("Money")->Get<int>() == 50);
			delete sharedData;
		}

		TEST_METHOD(HierarchyTest)
		{
			World w;
			Sector * s = w.CreateSector("TestSector");
			Assert::IsTrue(s->GetParent()->As<World>() == &w);
			Assert::IsTrue(s->GetWorld() == &w);
			Entity* entity = s->CreateEntity("Entity", "TestEntity");
			Assert::IsTrue(&(s->Find("Entities")->Get<Scope>()) == entity);
			Assert::IsTrue(entity->GetSector() == s);
			Assert::IsTrue(ff.ClassName() == "Furniture");
			Entity* entity1 = s->CreateEntity("Furniture", "blah");
			Assert::IsNotNull(entity1);
			Assert::IsTrue(entity1->GetSector() == s);
			Furniture* ffff = entity1->As<Furniture>();
			Assert::IsTrue(ffff->IsPrescribed("Name"));
			ffff->SetName("haha");
			Assert::IsTrue(ffff->Find("Name")->Get < std::string>() == "haha");
		}

		TEST_METHOD(ActionHierarchyTest)
		{
			World w;
			Sector * s = w.CreateSector("TestSector");
			Assert::IsTrue(s->GetParent()->As<World>() == &w);
			Assert::IsTrue(s->GetWorld() == &w);
			Entity* entity = s->CreateEntity("Entity", "TestEntity");
			Assert::IsTrue(&(s->Find("Entities")->Get<Scope>()) == entity);
			Assert::IsTrue(entity->GetSector() == s);
			Assert::IsTrue(ff.ClassName() == "Furniture");
			Entity* entity1 = s->CreateEntity("Furniture", "blah");
			Furniture* mehs = entity1->As<Furniture>();
			mehs->mHeight = 100.0f;
			Assert::IsNotNull(entity1);
			Assert::IsTrue(entity1->GetSector() == s);
			Action* action = entity->CreateAction("DebugAction", "debug");
			Assert::IsTrue(&(entity->Find("Actions")->Get<Scope>()) == action);
			ActionList* actionList = entity1->CreateAction("ActionList", "list")->As<ActionList>();
			Action* temp = actionList->CreateAction("ActionCreateAction", "blahblah");
			temp->Find("ClassName")->Set("DebugAction");
			temp->Find("InstanceName")->Set("DebugTest1");
			Action* createAction = entity->CreateAction("ActionCreateAction", "creator");
			Action* destroyAction = entity->CreateAction("ActionDestroyAction", "Destroyer");
			createAction->Find("ClassName")->Set("DebugAction");
			createAction->Find("InstanceName")->Set("DebugTest");
			destroyAction->Find("ActionName")->Set("debug");
			w.Update();
			Assert::AreEqual(3U, entity->Find("Actions")->Size()); 
			Assert::IsTrue(entity->Find("Actions")->Get<Scope>(2).As<DebugAction>()->Name() == "DebugTest");
			ActionExpression* actionExpression = entity1->CreateAction("ActionExpression", "Exp")->As<ActionExpression>();
			ScopeParseHelper sh;
			actionExpression->mDatumToSet = "Height";
			actionExpression->mExpression = sh.StringToRPN("( Height + 4.0 * ( 2.0 - 1.0 ) ) % 4.0");
			w.Update();
			Assert::IsTrue(mehs->mHeight == 0.0f);
		}

		TEST_METHOD(MoveConstructorsTest)
		{
			World w;
			w.SetName("World");
			Sector* s = w.CreateSector("TestSector");
			Entity* entity = s->CreateEntity("Entity", "TestEntity");
			World w2 = w;
			World w1(std::move(w));
			Assert::IsTrue(&(w1.Find("Sectors")->Get<Scope>()) != nullptr);
			Assert::IsTrue(w1.Name() == "World");
			entity;

			Sector* s1 = w1.CreateSector("temp"); 
			entity = s1->CreateEntity("Furniture", "NewEntity");
			Sector copySector = *s1;
			Assert::IsTrue(&(copySector.Find("Entities")->Get<Scope>()) != nullptr);
			Entity* test = copySector.Find("Entities")->Get<Scope>().As<Entity>(); test;
			Assert::IsTrue(copySector.Name() == "temp");
			Sector s2 = std::move(*s1); s2;
			Assert::IsTrue(&(s2.Find("Entities")->Get<Scope>()) != nullptr);
			Assert::IsTrue(s2.Name() == "temp");			

			Entity entity1 = std::move(*entity);
			Assert::IsTrue(entity1.Name() == "NewEntity");

			Entity entity2 = *s2.CreateEntity("Entity", "Blah");
			Entity entity3 = entity2;
			Assert::IsTrue(entity3.Name() == "Blah");
			delete s1;
			delete entity;
		}

		TEST_METHOD(UpdateTest)
		{
			World w;
			Sector * s = w.CreateSector("TestSector");
			Entity* entity = s->CreateEntity("Entity", "TestEntity");
			Datum* h = entity->Find("Actions");
			Action* action = entity->CreateAction("ActionList", "meh");
			entity; h;
			action;
			w.Update();
		}


		TEST_METHOD(ActionParseTest)
		{
			World tempWorld;
			JsonParseMaster::SharedData* sharedData = new ScopeParseHelper::ScopeSharedData(tempWorld);
			JsonParseMaster master(*sharedData);
			ScopeParseHelper sh;
			master.AddHelper(sh);
			master.ParseFromFile("Script/World.json");
			Assert::IsTrue(&(tempWorld.Find("Sectors")->Get<Scope>()) != nullptr);
			Sector* sector = tempWorld.Find("Sectors")->Get<Scope>().As<Sector>();
			Assert::IsTrue(sector->Name() == "BedRoom");
			Entity* entity = sector->Find("Entities")->Get<Scope>().As<Entity>();
			Assert::IsTrue(entity->Name() == "Chair");
			Assert::IsTrue(entity->Find("Height")->Get<float>() == 20.0f);
			Furniture* f = entity->As<Furniture>();
			Assert::IsNotNull(f);
			Assert::IsTrue(f->mHeight == 20.0f);
			entity = sector->Find("Entities")->Get<Scope>(1).As<Entity>();
			Assert::IsTrue(entity->Name() == "Table");
			Assert::IsTrue(entity->Find("Height")->Get<float>() == 30.0f);
			f = entity->As<Furniture>();
			Assert::IsTrue(f->mHeight == 30.0f);
			Sector* hall = tempWorld.Find("Sectors")->Get<Scope>(1).As<Sector>();
			Assert::IsTrue(hall->Name() == "Hallway");
			Assert::IsTrue(hall->Entities()[0].As<Furniture>()->Name() == "Cupboard");
			Assert::IsTrue(hall->Entities()[0].Find("Height")->Get<float>() == 40.0f);
			Assert::IsTrue(hall->Entities()[0].Find("Safebox")->Get<Scope>().Find("Money")->Get<int>() == 50);
			Assert::IsTrue(((((hall->Entities()[0])["Safebox"])[0])["Money"]).Get<int>() == 50);
			Datum* actions = hall->Entities()[0].As<Furniture>()->Find("Actions");
			Assert::IsNotNull(actions);
			Assert::AreEqual(3U, actions->Size());
			Scope* scope = &actions->Get<Scope>();
			scope;
			ActionListIf* actionList = actions->Get<Scope>().As<ActionListIf>();
			Assert::IsTrue(actionList->Condition() == 1);
			ActionList* debugActionList = actions->Get<Scope>(2).As<ActionList>();
			Assert::IsTrue(debugActionList->Name() == "Debugger");
			Assert::IsTrue(debugActionList->Find("Actions")->Get<Scope>().As<DebugAction>()->mDebugMessage == "Debug1");
			tempWorld.Update();
			actions = hall->Entities()[0].As<Furniture>()->Find("Actions");
			Assert::AreEqual(4U, actions->Size());
			Assert::IsTrue(actions->Get<Scope>(3).As<DebugAction>()->Name() == "Debug3");
			delete sharedData;
		}

		TEST_METHOD(ExpressionTest)
		{
			ScopeParseHelper sh;
			std::string tokens = sh.StringToRPN("3 + 4 * ( 2 - 1 )");
			tokens;
		}

	private:
		static _CrtMemState sStartMemState;
	};
	_CrtMemState WorldTest::sStartMemState;
}