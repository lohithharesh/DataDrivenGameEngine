#pragma once
#include "Attributed.h"
#include "AbstractFactory.h"
#include "Action.h"

namespace FieaGameEngine
{
	class Sector;
	class WorldState;
	//!Entity Class
	class Entity : public Attributed
	{
		//RTTI Declarations
		RTTI_DECLARATIONS(Entity, Attributed)
	public:
		//!Name Function
		/*!
			returns the name of the entity
			\return string, the name of the entity
		*/
		const std::string& Name() const;
		//!SetName function
		/*!
			set the name of the entity
			\param name, a const string reference
		*/
		void SetName(const std::string& name);
		//!GetSector function
		/*!
			returns the sector the entity belongs to.
			\return a sector pointer which points to the owner sector
		*/
		Sector* GetSector() const;
		//!SetSector Function
		/*!
			sets the owner of the current entity.
			\param a sector reference to the owner sector
		*/
		void SetSector(Sector& parentSector);
		//!Update function
		virtual void Update(WorldState& worldState);
		//!Parameterized constructor
		explicit Entity(const std::string& name = "");
		//!Create action function
		/*!
			Creates an action based on the given classname and the instance name
			\param string classname, the name of the class of the action to create
			\param string instancename, the name of the newly created action
			\return Action Pointer, a pointer to the newly created action
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);
		//!return the datum of Actions
		Datum& Actions() const;
		//!Copy and move constructors
		Entity(const Entity& rhs) = default;
		Entity(Entity&& rhs) = default;
		Entity& operator=(const Entity& rhs) = default;
		Entity& operator=(Entity&& rhs) = default;
		virtual ~Entity();
		static Vector<Signature> Signatures();
	private:
		std::string mName;
	protected:
		Entity(uint64_t id);
		virtual Scope* Clone(const Scope& rhs) override;
	};

	ConcreteFactory(Entity, Entity)
}
