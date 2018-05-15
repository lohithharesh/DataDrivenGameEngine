#pragma once

#include <deque>

#include "RuleCheckEntity.h"
#include "World.h"

namespace FieaGameEngine {
	class LevelManager final {
	public:
		LevelManager() = delete;

		static void InitLevelManager(World& world);

		static RuleCheckEntity::Board& GetBoard();
		static World* GetWorld();
		static void InitializeGame();
		static void StartLevel(int level = mLevel);
		static void LoadNextLevel();
		static void LoadCurrentLevel();
		static void InitRawBoard();
		static void ClearBoard();

		static void TakeBoardSnapShot();
		static void RevertBoard();
		static void ClearSnapshots();

		static RuleCheckEntity::Board mBoard;

		static bool LoadNextLevelBool;
		static bool LoadCurrentLevelBool;
		static bool UndoMoveBool;
		static int mLevel;

	private:

		static HashMap<int, std::string> mLevelNames;
		static World* mWorld;
		
		static std::deque<std::pair<RuleCheckEntity::Board, HashMap<GameObject*, BoardSpaceObject>>> mBoardFrames;
		
	};
}