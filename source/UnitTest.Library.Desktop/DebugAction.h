#pragma once
#include "Action.h"
#include "AbstractFactory.h"

namespace FieaGameEngine {
	class DebugAction : public Action
	{
		RTTI_DECLARATIONS(DebugAction, Action)
	public:
		DebugAction();
		DebugAction(DebugAction& rhs) = default;
		DebugAction(DebugAction&& rhs) = default;
		DebugAction& operator=(DebugAction& rhs) = default;
		DebugAction& operator=(DebugAction&& rhs) = default;
		~DebugAction();
		virtual void Update(WorldState& worldState) override;
		std::string mDebugMessage;
		static Vector<Signature> Signatures();
		std::string mReactionMessage;
	protected:
		virtual Scope* Clone(const Scope& rhs);
	};

	ConcreteFactory(DebugAction, Action)
}

