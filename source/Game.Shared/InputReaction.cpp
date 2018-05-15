#include "pch.h"
#include "InputReaction.h"
#include "Input.h"
#include "Event.h"
#include "InputAction.h"
#include <cassert>
#include "World.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(InputReaction)
	InputReaction::InputReaction() : Reaction(InputReaction::TypeIdClass())
	{
		Event<InputTypesEnum>::Subscribe(*this);
	}


	InputReaction::~InputReaction()
	{
		Event<int>::Unsubscribe(*this);
	}

	void InputReaction::Update(WorldState & worldState)
	{
		ActionList::Update(worldState);
	}

	void InputReaction::Notify(const EventPublisher & publisher)
	{
		Event<InputTypesEnum>* event = publisher.As<Event<InputTypesEnum>>();
		if (event != nullptr)
		{	
			InputTypesEnum message = event->Message();

			Scope& actionScope = Actions()[0];
			
			InputAction* action = actionScope.As<InputAction>();
			action->SetInputDirection(message);
			Update(GetParent()->As<World>()->GetWorldState());
		}
	}

	Vector<Signature> InputReaction::Signatures()
	{
		return Reaction::Signatures();
	}

	Scope * FieaGameEngine::InputReaction::Clone(const Scope & rhs)
	{
		return new InputReaction(*(rhs.As<InputReaction>()));
	}
}