#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"

namespace FieaGameEngine {
	//!Reaction class
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)
	public:
		Reaction() = delete;
		//!Move and Copy Constructors
		Reaction(const Reaction& rhs) = default;
		Reaction(Reaction&& rhs) = default;
		Reaction& operator=(const Reaction& rhs) = default;
		Reaction& operator=(Reaction&& rhs) = default;
		//!notfiy function
		/*!
			virtual function that is implemented by the subscribers. Delivers a reference of the event to the subscribers.
			\param publisher, a const reference to the publisher
		*/
		virtual void Notify(const EventPublisher& publisher) override = 0;
		//!Update Function
		virtual void Update(WorldState& worldState) override = 0;
		//!Clone Function
		virtual Scope* Clone(const Scope& rhs) override = 0;
		//!Signatures Function
		static Vector<Signature> Signatures();
		virtual ~Reaction() = default;
	protected:
		Reaction(uint64_t id);
	};
}

