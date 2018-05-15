#include "pch.h"
#include "ActionDestroyAction.h"
#include "WorldState.h"
#include "GarbageCollector.h"
using namespace FieaGameEngine;
RTTI_DEFINITIONS(ActionDestroyAction)

ActionDestroyAction::ActionDestroyAction() : ActionDestroyAction("")
{
}

ActionDestroyAction::ActionDestroyAction(const std::string& name) : Action(ActionDestroyAction::TypeIdClass())
{
	SetName(name);
}


void ActionDestroyAction::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	bool deletedAction = false;
	Scope* parent = GetParent();
	while (!deletedAction && parent != nullptr)
	{
		Datum* actions = parent->Find("Actions");
		if (actions != nullptr)
		{

			for (uint32_t i = 0; i < actions->Size(); i++)
			{
				Action* action = (*actions)[i].As<Action>();
				if (action->Name() == mActionName)
				{
					deletedAction = true;
					GarbageCollector::garbageList.PushBack(action);
					break;
				}
			}
		}
		parent = parent->GetParent();;
	}
	worldState.mCurrentAction = nullptr;
}

Vector<Signature> ActionDestroyAction::Signatures()
{
	Vector<Signature> signatures = Action::Signatures();
	signatures.PushBack({ "ActionName", DatumTypeEnum::String, 1, offsetof(ActionDestroyAction, mActionName) });
	return signatures;
}

Scope* ActionDestroyAction::Clone(const Scope& rhs)
{
	return new ActionDestroyAction(*(rhs.As<ActionDestroyAction>()));
}