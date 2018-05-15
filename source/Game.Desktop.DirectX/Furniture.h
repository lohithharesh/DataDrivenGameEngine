#pragma once
#include "Entity.h"
#include "AbstractFactory.h"
namespace FieaGameEngine
{
	class Furniture : public Entity
	{
		RTTI_DECLARATIONS(Furniture, Entity)
	public:
		Furniture();
		~Furniture() = default;
		Furniture(Furniture& rhs) = default;
		Furniture(Furniture&& rhs) = default;
		Furniture& operator=(Furniture& rhs) = default;
		Furniture& operator=(Furniture&& rhs) = default;
		virtual void Update(WorldState& worldstate) override;
		static Vector<Signature> Signatures();
		float mHeight;
	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	};

	ConcreteFactory(Furniture, Entity)
}

