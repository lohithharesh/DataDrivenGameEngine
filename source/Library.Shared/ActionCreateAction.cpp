#include "pch.h"
#include "ActionCreateAction.h"
#include "Entity.h"
#include "ActionList.h"
#include "WorldState.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(ActionCreateAction)

ActionCreateAction::ActionCreateAction() : ActionCreateAction("")
{
}

ActionCreateAction::ActionCreateAction(const std::string& name) : Action(ActionCreateAction::TypeIdClass())
{
	SetName(name);
}

void ActionCreateAction::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	Scope* parent = GetParent();
	assert(parent->Is(ActionList::TypeName()) || parent->Is(Entity::TypeName()));
	ActionList* action = parent->As<ActionList>();
	if (action != nullptr)
	{
		action->CreateAction(mClassName, mInstanceName);
	}
	else
	{
		Entity* entity = parent->As<Entity>();
		entity->CreateAction(mClassName, mInstanceName);
	}
	worldState.mCurrentAction = nullptr;
}

Vector<Signature> ActionCreateAction::Signatures()
{
	Vector<Signature> signatures = Action::Signatures();
	signatures.PushBack({ "ClassName", DatumTypeEnum::String, 1, offsetof(ActionCreateAction, mClassName) });
	signatures.PushBack({ "InstanceName", DatumTypeEnum::String, 1, offsetof(ActionCreateAction, mInstanceName) });
	return signatures;
}

Scope* ActionCreateAction::Clone(const Scope& rhs)
{
	return new ActionCreateAction(*(rhs.As<ActionCreateAction>()));
}