#pragma once
#include "Reaction.h"
#include "AbstractFactory.h"

namespace FieaGameEngine
{
	class InputReaction : public Reaction
	{
		RTTI_DECLARATIONS(InputReaction, Reaction)
	public:
		InputReaction();
		~InputReaction();
		static Vector<Signature> Signatures();
		virtual void Notify(const EventPublisher& publisher) override;
		virtual void Update(WorldState& worldState) override;

	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	};


	ConcreteFactory(InputReaction, Reaction)
}