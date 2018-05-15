#pragma once
#include "Action.h"
#include "AbstractFactory.h"

namespace FieaGameEngine
{
	class ResetActionIf : public Action
	{
		RTTI_DECLARATIONS(ResetActionIf, Action)
	public:
		ResetActionIf();
		ResetActionIf(const ResetActionIf& rhs) = default;
		ResetActionIf(ResetActionIf&& rhs) = default;
		ResetActionIf& operator=(const ResetActionIf& rhs) = default;
		ResetActionIf& operator=(ResetActionIf&& rhs) = default;
		static Vector<Signature> Signatures();
		virtual void Update(WorldState& worldState);
		
		~ResetActionIf();

	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	};

	ConcreteFactory(ResetActionIf, Action)
}

