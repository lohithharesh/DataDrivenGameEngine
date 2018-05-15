#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	class ResetAction : Action
	{
	public:
		ResetActionIf();
		Vector<Signature> Signatures();
		virtual void Update(WorldState& worldState);
		
		~ResetActionIf();
	};
}

