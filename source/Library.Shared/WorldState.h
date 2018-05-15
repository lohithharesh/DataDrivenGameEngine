#pragma once
#include "GameTime.h"
#include "Vector.h"
#include "RuleCheckEntity.h"
#include <array>
namespace FieaGameEngine
{
	const int BoardSize = 20;
	class World;
	class Sector;
	class Entity;
	class Action;
	class WorldState final
	{
	public:
		//!Default constructor
		WorldState() = default;
		~WorldState() = default;
		WorldState(const WorldState& rhs) = default;
		WorldState(WorldState&& rhs) = default;
		WorldState& operator=(const WorldState& rhs) = default;
		WorldState& operator=(WorldState&& rhs) = default;
		//!Set the gameTime
		void SetGameTime(GameTime gameTime);
		World* mCurrentWorld;
		Sector* mCurrentSector;
		Entity* mCurrentEntity;
		Action* mCurrentAction;
		GameTime mGameTime;
		GameClock mGameClock;

		//Baba Is You stuff starts here
	public:
		/// <summary>
		/// This method returns a const reference to the list of spaces with
		/// "Is" currently on them.
		/// </summary>
		/// <returns>The list of spaces on the board with "Is" on them.
		/// </returns>
		const Vector<std::pair<uint32_t, uint32_t>>& SpacesWithIs() const;

		/// <summary>
		/// Accessor for the raw board.
		/// </summary>
		/// <returns>A reference to the board.</returns>
		RuleCheckEntity::Board& RawBoard();
		
		Vector<GameObject*> mIsObjects;
		Vector<GameObject*> mPlayerObjects;
	private:
		/// <summary>
		/// This is the actual board.
		/// </summary>
		RuleCheckEntity::Board mRawBoard;

		/// <summary>
		/// This is a list of spaces on the board with "Is" on them right now.
		/// </summary>
		Vector<std::pair<uint32_t, uint32_t>> mSpacesWithIs;

		
	};
}

