#pragma once
#include "Action.h"
#include "AbstractFactory.h"

namespace FieaGameEngine {
	class ResetActionElse : public Action
	{
		RTTI_DECLARATIONS(ResetActionElse, Action)
	public:
		ResetActionElse();
		virtual void Update(WorldState& worldState);
		static Vector<Signature> Signatures();
		~ResetActionElse();

	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	};

	ConcreteFactory(ResetActionElse, Action)
}