#pragma once
#include "Sector.h"
#include "Reaction.h"
#include "WorldState.h"
#include "EventQueue.h"

namespace FieaGameEngine
{
	class World final : public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed)
	public:
		//!Default constructor
		explicit World(const std::string& name = "");
		//!Name Function
		/*!
			returns the name of the world
			\return string, the name of the world
		*/
		const std::string& Name() const;
		//!SetName function
		/*!
			set the name of the World
			\param name, a const string reference
		*/
		void SetName(const std::string& name);
		//!Sectors function
		/*!
			returns the datum that contains the sector pointers.
			\return a datum.
		*/
		Datum& Sectors();
		//!CreateSector
		/*!
			create a sector and return a pointer to it.
			\param name, the name of the sector
			\return a sector pointer to the newly created sector
		*/
		Sector* CreateSector(const std::string& name);
		//!Update function
		void Update();
		//!Move and copy constructors
		World(const World& rhs) = default;
		World(World&& rhs) = default;
		World& operator=(const World& rhs) = default;
		World& operator=(World&& rhs) = default;
		static Vector<Signature> Signatures();
		WorldState& GetWorldState();
		Reaction* CreateReaction(const std::string& classname, const std::string& instanceName);
		Datum& Reactions();
		EventQueue& GetEventQueue();
		~World();
	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	private:
		std::string mName;
		WorldState mWorldState;
		EventQueue mEventQueue;
	};
}

