#pragma once
#include "Action.h"

namespace FieaGameEngine {
	//!ActionList class
	class ActionList : public Action
	{
		//RTTI declarations
		RTTI_DECLARATIONS(ActionList, Action)
	public:
		//!Parameterized Constructor that takes in a name
		ActionList(const std::string& name);
		//!Default constructor
		ActionList();
		//!Update Function
		/*!
			Loops through the list of actions and calls update on each of them
		*/
		virtual void Update(WorldState& worldState) override;
		//!Create action function
		/*!
			Creates an action based on the given classname and the instance name
			\param string classname, the name of the class of the action to create
			\param string instancename, the name of the newly created action
			\return Action Pointer, a pointer to the newly created action
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);
		//!Move and copy constructors
		ActionList(const ActionList& rhs) = default;
		ActionList(ActionList&& rhs) = default;
		ActionList& operator=(const ActionList& rhs) = default;
		ActionList& operator=(ActionList&& rhs) = default;
		//!Destructor
		virtual ~ActionList() = default;
		Datum& Actions() const;
		static Vector<Signature> Signatures();
	protected:
		virtual Scope* Clone(const Scope& rhs) override;
		ActionList(uint64_t id);
	};

	ConcreteFactory(ActionList, Action)
}

