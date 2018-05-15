#include "pch.h"
#include "ActionListIf.h"
#include "AbstractFactory.h"
#include "WorldState.h"
using namespace FieaGameEngine;

RTTI_DEFINITIONS(ActionListIf);

ActionListIf::ActionListIf(const std::string& name) : ActionList(ActionListIf::TypeIdClass())
{
	SetName(name);
}

ActionListIf::ActionListIf() : ActionListIf("")
{

}

Action* ActionListIf::CreateAction(const std::string& className, const std::string& instanceName, const std::string& key)
{
	Action* action = AbstractFactory<Action>::Create(className);
	action->SetName(instanceName);
	Adopt(*action, key);
	return action;
}

void ActionListIf::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	if (mCondition == 0)
	{
		Scope& action = Find("ActionElse")->Get<Scope>();
		assert(action.Is(Action::TypeName()));
		static_cast<Action*>(&action)->Update(worldState);
		
	}
	else
	{
		Scope& action = Find("ActionIf")->Get<Scope>();
		assert(action.Is(Action::TypeName()));
		static_cast<Action*>(&action)->Update(worldState);
	}
}

int ActionListIf::Condition() const
{
	return mCondition;
}

void ActionListIf::SetCondition(int value)
{
	mCondition = value;
}

Vector<Signature> ActionListIf::Signatures()
{
	Vector<Signature> signatures = ActionList::Signatures();
	signatures.PushBack({ "Condition", DatumTypeEnum::Integer, 1, offsetof(ActionListIf, mCondition) });
	signatures.PushBack({ "ActionIf", DatumTypeEnum::Table, 0, 0 });
	signatures.PushBack({ "ActionElse", DatumTypeEnum::Table, 0, 0 });
	return signatures;
}

Scope* ActionListIf::Clone(const Scope& rhs)
{
	return new ActionListIf(*(rhs.As<ActionListIf>()));
}