#pragma once
#include "Action.h"
#include "Event.h"
#include "EventMessageAttributed.h"

namespace FieaGameEngine {
	//!ActionEvent class
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action)
	public:
		//!Default constructor
		ActionEvent();
		//!Move and copy constructors
		ActionEvent(const ActionEvent& rhs) = default;
		ActionEvent(ActionEvent&& rhs) = default;
		ActionEvent& operator=(const ActionEvent& rhs) = default;
		ActionEvent& operator=(ActionEvent&& rhs) = default;
		//!Update function 
		/*!
			creates an event with event message attributed as the message. 
			copies any auxillary attributes to the event and forawrds it.
		*/
		void Update(WorldState& worldState);
		//!Clone function for the copying
		virtual Scope* Clone(const Scope& rhs) override;
		//!Signatures function
		static Vector<Signature> Signatures();
		~ActionEvent() = default;
	private:
		std::string mSubType;
		int mDelay;

	};

	ConcreteFactory(ActionEvent, Action)
}

