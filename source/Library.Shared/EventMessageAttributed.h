#pragma once
#include "Attributed.h"

namespace FieaGameEngine {
	class World;
	//!Event Message Attributed Class
	class EventMessageAttributed : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed)
	public:
		//!Defualt constructor
		EventMessageAttributed();
		//!Move and copy constructors
		EventMessageAttributed(const EventMessageAttributed& rhs) = default;
		EventMessageAttributed(EventMessageAttributed&& rhs) = default;
		EventMessageAttributed& operator=(const EventMessageAttributed& rhs) = default;
		EventMessageAttributed& operator=(EventMessageAttributed&& rhs) = default;
		//!Signatures Function
		static Vector<Signature> Signatures();
		//!Destructor
		virtual ~EventMessageAttributed() = default;
		//!clone function for copy constructor to work
		virtual Scope* Clone(const Scope& rhs) override;
		//!Set World Function
		/*!
			\param a world reference
		*/
		void SetWorld(World& world);
		//!getter for the world member
		World* GetWorld();
		//!Setter for the subtype member
		void SetSubType(const std::string& subType);
		//!getter for the subtype member
		const std::string& GetSubType();
	private:
		std::string mSubType;
		World* mWorld;
	};
}

