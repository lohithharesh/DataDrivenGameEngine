#include "pch.h"
#include "ReactionAttributed.h"
#include "World.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(ReactionAttributed)

ReactionAttributed::ReactionAttributed() : Reaction(ReactionAttributed::TypeIdClass())
{
	Event<EventMessageAttributed>::Subscribe(*this);
}


Vector<Signature> ReactionAttributed::Signatures()
{
	Vector<Signature> signatures = Reaction::Signatures();
	signatures.PushBack({ "SubType", DatumTypeEnum::String, 1, offsetof(ReactionAttributed, mSubType) });
	return signatures;
}

void ReactionAttributed::Notify(const EventPublisher& publisher)
{
	Event<EventMessageAttributed>* event = publisher.As<Event<EventMessageAttributed>>();
	if (event != nullptr)
	{
		EventMessageAttributed message = event->Message();
		if (message.GetSubType() == mSubType)
		{
			Vector<ScopePairType*> auxAttributes = message.AuxillaryPairs();
			for (auto aux : auxAttributes)
			{
				AppendAuxillaryAttribute(aux->first) = aux->second; 
			}
			Update(message.GetWorld()->GetWorldState());
		}
	}
}

void ReactionAttributed::Update(WorldState& worldState)
{
	ActionList::Update(worldState);
}

Scope* ReactionAttributed::Clone(const Scope& rhs)
{
	return new ReactionAttributed(*(rhs.As<ReactionAttributed>()));
}

ReactionAttributed::~ReactionAttributed()
{
	Event<EventMessageAttributed>::Unsubscribe(*this);
}