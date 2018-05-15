#include "pch.h"
#include "ActionList.h"
#include "WorldState.h"
#include "AbstractFactory.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(ActionList);
ActionList::ActionList() : ActionList("")
{

}

ActionList::ActionList(const std::string& name) : Action(ActionList::TypeIdClass())
{
	SetName(name);
}

ActionList::ActionList(uint64_t id) : Action(id)
{

}

void ActionList::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	Datum* actions = Find("Actions");
	for (uint32_t i = 0; i < actions->Size(); i++)
	{
		Scope& actionScope = actions->Get<Scope>(i);
		assert(actionScope.Is("Action"));
		Action* action = static_cast<Action*>(&actionScope);
		action->Update(worldState);
	}
	worldState.mCurrentAction = nullptr;
}

Action* ActionList::CreateAction(const std::string& className, const std::string& instanceName)
{
	Action* action = AbstractFactory<Action>::Create(className);
	assert(action != nullptr);
	action->SetName(instanceName);
	Adopt(*action, "Actions");
	return action;
}

Vector<Signature> ActionList::Signatures()
{
	Vector<Signature> signatures = Action::Signatures();
	signatures.PushBack({ "Actions", DatumTypeEnum::Table, 0, 0 });
	return signatures;
}

Scope* ActionList::Clone(const Scope& rhs)
{
	return new ActionList(*(rhs.As<ActionList>()));
}

Datum& ActionList::Actions() const
{
	return *Find("Actions");
}