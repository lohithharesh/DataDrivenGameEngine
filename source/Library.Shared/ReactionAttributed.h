#pragma once
#include "Reaction.h"
#include "EventMessageAttributed.h"
#include "Event.h"

namespace FieaGameEngine {
	//!Reaction Attributed Class
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction)
	public:
		//!Default Constructor
		ReactionAttributed();
		//!notify function
		/*!
			checks if the subtype matches and calls the update function accordingly
		*/
		virtual void Notify(const EventPublisher& publisher) override;
		//!update function
		/*!
			Calls action list update function which takes care of calling update on each
			of the child actions
		*/
		virtual void Update(WorldState& worldState) override;
		//!signatures Function
		static Vector<Signature> Signatures();
		//!Clone function for copying
		virtual Scope* Clone(const Scope& rhs) override;
		~ReactionAttributed();
	private:
		std::string mSubType;
	};


	ConcreteFactory(ReactionAttributed, Reaction)
}

