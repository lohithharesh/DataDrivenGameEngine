#pragma once
#include "Action.h"

namespace FieaGameEngine {
	//!ActionDestroyAction class
	class ActionDestroyAction : public Action
	{
		//RTTI DEClarations
		RTTI_DECLARATIONS(ActionDestroyAction, Action)
	public:
		//!Defualt constructor
		ActionDestroyAction();
		//!Parameterized constructor that takes in a name
		ActionDestroyAction(const std::string& name);
		//!Update function
		/*!
			Deletes the action whose name is stored in the actionname field
		*/
		virtual void Update(WorldState& worldState) override;
		//!move and copy constructors
		ActionDestroyAction(const ActionDestroyAction& rhs) = default;
		ActionDestroyAction(ActionDestroyAction&& rhs) = default;
		ActionDestroyAction& operator=(const ActionDestroyAction& rhs) = default;
		ActionDestroyAction& operator=(ActionDestroyAction&& rhs) = default;
		static Vector<Signature> Signatures();
		//!Destructor
		virtual ~ActionDestroyAction() = default;
	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	private:
		std::string mActionName;
	};

	ConcreteFactory(ActionDestroyAction, Action)
}

