#pragma once
#include "Action.h"
#include "AbstractFactory.h"
namespace FieaGameEngine {

	//!ActionCreateAction class
	class ActionCreateAction : public Action
	{
		//!RTTI declarations
		RTTI_DECLARATIONS(ActionCreateAction, Action)
	public:
		//!Default constructor
		ActionCreateAction();
		//!parameterized constructor
		ActionCreateAction(const std::string& name);
		//!Update function
		/*!
			creates the action with the classname and the instance name that has been set.
		*/
		virtual void Update(WorldState& worldState) override;
		//!Copy and move constructors
		ActionCreateAction(const ActionCreateAction& rhs) = default;
		ActionCreateAction(ActionCreateAction&& rhs) = default;
		ActionCreateAction& operator=(const ActionCreateAction& rhs) = default;
		ActionCreateAction& operator=(ActionCreateAction&& rhs) = default;
		static Vector<Signature> Signatures();
		//!Destructors
		virtual ~ActionCreateAction() = default;
	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	private:
		std::string mClassName;
		std::string mInstanceName;
	};

	ConcreteFactory(ActionCreateAction, Action)
}

