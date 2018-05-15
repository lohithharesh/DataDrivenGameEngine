#include "pch.h"
#include "ActionEvent.h"
#include "World.h"



using namespace FieaGameEngine;

RTTI_DEFINITIONS(ActionEvent)
ActionEvent::ActionEvent() : Action(ActionEvent::TypeIdClass())
{

}


Scope* ActionEvent::Clone(const Scope& rhs)
{
	return new ActionEvent(*(rhs.As<ActionEvent>()));
}

Vector<Signature> ActionEvent::Signatures()
{
	Vector<Signature> signatures = Action::Signatures();
	signatures.PushBack({ "SubType", DatumTypeEnum::String, 1, offsetof(ActionEvent, mSubType) });
	signatures.PushBack({ "Delay", DatumTypeEnum::Integer, 1, offsetof(ActionEvent, mDelay) });
	return signatures;
}

void ActionEvent::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	EventMessageAttributed message;
	message.SetSubType(mSubType);
	message.SetWorld(*worldState.mCurrentWorld);
	Vector<ScopePairType*> auxAttributes = AuxillaryPairs();
	for (auto aux : auxAttributes)
	{
		message.AppendAuxillaryAttribute(aux->first) = aux->second;
	}
	std::shared_ptr<Event<EventMessageAttributed>> event = std::make_shared<Event<EventMessageAttributed>>(message);
	worldState.mCurrentWorld->GetEventQueue().Enqueue(event, worldState.mGameTime, std::chrono::milliseconds(mDelay));
	worldState.mCurrentAction = nullptr;
}