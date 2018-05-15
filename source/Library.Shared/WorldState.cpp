#include "pch.h"
#include "WorldState.h"

using namespace std;

using namespace FieaGameEngine;

namespace FieaGameEngine
{
	void WorldState::SetGameTime(GameTime gameTime)
	{
		mGameTime = gameTime;
	}

	const Vector<pair<uint32_t, uint32_t>>& WorldState::SpacesWithIs() const
	{
		return mSpacesWithIs;
	}

	RuleCheckEntity::Board& WorldState::RawBoard()
	{
		return mRawBoard;
	}
}