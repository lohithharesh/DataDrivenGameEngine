#pragma once
#include "Attributed.h"
#include "AbstractFactory.h"

namespace FieaGameEngine {
	class WorldState;
	class Entity;
	class ActionList;

	//!Action Class
	class Action : public Attributed
	{
		//!RTTI declarations
		RTTI_DECLARATIONS(Action, Attributed)
	public:
		//!Returns the name of the instance
		/*!
			\return string, the name of the instance
		*/
		const std::string& Name() const;
		//!Set the name of the instance
		/*!
			\param, name - a string
		*/
		void SetName(const std::string& name);
		//!update function
		virtual void Update(WorldState& worldState) = 0;
		//!Defualt constructor
		Action();
		//!parameterized constructor that takes in a name
		explicit Action(const std::string& name);
		//!Move and copy constructors
		Action(const Action& rhs) = default;
		Action(Action&& rhs) = default;
		Action& operator=(const Action& rhs) = default;
		Action& operator=(Action&& rhs) = default;
		//!Destructor
		virtual ~Action() = default;
		static Vector<Signature> Signatures();
	private:
		std::string mName;
	protected:
		Action(uint64_t id);
		virtual Scope* Clone(const Scope& rhs) override = 0;
	};
}

