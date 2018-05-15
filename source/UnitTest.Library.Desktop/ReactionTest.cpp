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
#include "ActionEvent.h"
#include "ReactionAttributed.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ReactionTest)
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
		ConcreteActionEventFactory aef;
		ConcreteReactionAttributedFactory ra;

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
			RegisterType(ActionEvent);
			RegisterType(EventMessageAttributed);
			RegisterType(Reaction);
			RegisterType(ReactionAttributed);
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

		TEST_METHOD(ReactionActionParseTest)
		{
			World tempWorld;
			JsonParseMaster::SharedData* sharedData = new ScopeParseHelper::ScopeSharedData(tempWorld);
			JsonParseMaster master(*sharedData);
			ScopeParseHelper sh;
			master.AddHelper(sh);
			master.ParseFromFile("Script/Reaction.json");
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
			ActionEvent* actionEvent = f->Actions()[0].As<ActionEvent>();
			Assert::IsNotNull(actionEvent);
			ReactionAttributed* reaction = tempWorld.Reactions()[0].As<ReactionAttributed>();
			Assert::IsNotNull(reaction);
			DebugAction* debug = reaction->Actions()[0].As<DebugAction>();
			Assert::IsNotNull(debug);
			Assert::IsTrue(debug->mReactionMessage == "");
			tempWorld.Update();
			tempWorld.Update();
			Assert::IsTrue(debug->mReactionMessage == "Reacting");
			delete sharedData;
		}


		TEST_METHOD(MoveTest)
		{
			World tempWorld;
			JsonParseMaster::SharedData* sharedData = new ScopeParseHelper::ScopeSharedData(tempWorld);
			JsonParseMaster master(*sharedData);
			ScopeParseHelper sh;
			master.AddHelper(sh);
			master.ParseFromFile("Script/Reaction.json");
			World tempWorld2 = std::move(tempWorld);
			Assert::IsTrue(&(tempWorld2.Find("Sectors")->Get<Scope>()) != nullptr);
			Sector* sector = tempWorld2.Find("Sectors")->Get<Scope>().As<Sector>();
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
			ActionEvent* actionEvent = f->Actions()[0].As<ActionEvent>();
			Assert::IsNotNull(actionEvent);
			ReactionAttributed* reaction = tempWorld2.Reactions()[0].As<ReactionAttributed>();
			Assert::IsNotNull(reaction);
			DebugAction* debug = reaction->Actions()[0].As<DebugAction>();
			Assert::IsNotNull(debug);
			Assert::IsTrue(debug->mReactionMessage == "");
			tempWorld2.Update();
			tempWorld2.Update();
			Assert::IsTrue(debug->mReactionMessage == "Reacting");
			delete sharedData;
		}

	private:
		static _CrtMemState sStartMemState;
	};
	_CrtMemState ReactionTest::sStartMemState;
}