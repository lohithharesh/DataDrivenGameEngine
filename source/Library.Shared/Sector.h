#pragma once
#include "Attributed.h"
#include "Entity.h"

namespace FieaGameEngine
{
	class World;
	class WorldState;
	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)
	public:
		//!Parameterized constructor
		explicit Sector(const std::string& name = "");
		//!Name Function
		/*!
			returns the name of the sector
			\return string, the name of the sector
		*/
		const std::string& Name() const;
		//!SetName function
		/*!
			set the name of the Sector
			\param name, a const string reference
		*/
		void SetName(const std::string& name);
		//!Entities function
		/*!
			returns the datum that contains the entity pointers.
			\return a datum.
		*/
		Datum& Entities() const;
		//!Create entity function
		/*!
			A wrapper to the factory call to create entity. 
			\param classname, the entity class that needs to be instanced
			\param instancename, the name of the entity
			\return a Entity pointer to the newly created entity
		*/
		Entity* CreateEntity(const std::string& className,const std::string& instanceName);
		//!SetWorld Function
		/*!
			sets the owner of the current sector.
			\param a world reference to the owner world
		*/
		void SetWorld(World& ownerWorld);
		//!GetWorld function
		/*!
			returns the world the sector belongs to.
			\return a world pointer which points to the owner world
		*/
		World* GetWorld() const;
		//!Update function
		void Update(WorldState& worldState);
		//!Move and copy constructors
		Sector(const Sector& rhs) = default;
		Sector(Sector&& rhs) = default;
		Sector& operator=(const Sector& rhs) = default;
		Sector& operator=(Sector&& rhs) = default;
		static Vector<Signature> Signatures();
	    virtual ~Sector() = default;
	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	private:
		std::string mName;

	};
}

