#pragma once
#include "ActionList.h"

namespace FieaGameEngine {
	//!actionlist if class
	class ActionListIf : public ActionList
	{
		//RTTI declarations
		RTTI_DECLARATIONS(ActionListIf, ActionList)
	public:
		//!Default Constructor
		ActionListIf();
		//!Parameterized constructor
		ActionListIf(const std::string& name);
		//!Create Action Function
		/*!
			Creates an action based on the given classname and the instance name
			\param string classname, the name of the class of the action to create
			\param string instancename, the name of the newly created action
			\param string key, the datum the action needs to be put into (if or else)
			\return Action Pointer, a pointer to the newly created action
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName, const std::string& key);
		//!Move and copy constructors
		ActionListIf(const ActionListIf& rhs) = default;
		ActionListIf(ActionListIf&& rhs) = default;
		ActionListIf& operator=(const ActionListIf& rhs) = default;
		ActionListIf& operator=(ActionListIf&& rhs) = default;
		//!Update function
		/*!
			Check the condtion and call the corresponding action
		*/
		virtual void Update(WorldState& worldState) override;
		//!Condition Function
		/*!
			returns the condition value
		*/
		int Condition() const;
		//!SetCondition Set the condition value
		void SetCondition(int value);
		//!Destructor
		static Vector<Signature> Signatures();
		virtual ~ActionListIf() = default;
	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	private:
		int mCondition;
	};

	ConcreteFactory(ActionListIf, Action)
}

