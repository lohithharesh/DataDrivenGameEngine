#include "pch.h"
#include <cassert>
#include <utility>
#include "LevelManager.h"
#include "GameObject.h"
#include "JsonParseMaster.h"
#include "ScopeParseHelper.h"
#include "HashMap.h"

using namespace FieaGameEngine;

HashMap<int, std::string> LevelManager::mLevelNames = {
	{ 0, "JsonFiles/Level1.json" },
	{ 1, "JsonFiles/Level2.json" },
	{ 2, "JsonFiles/Level3.json" },
	{ 3, "JsonFiles/Level4.json" },
	{ 4, "JsonFiles/Level5.json" },
	{ 5, "JsonFiles/Level6.json" },
	{ 6, "JsonFiles/Level7.json" }
};

int LevelManager::mLevel = 0;
World* LevelManager::mWorld = nullptr;
bool LevelManager::LoadNextLevelBool = false;
bool LevelManager::LoadCurrentLevelBool = false;
bool LevelManager::UndoMoveBool = false;

RuleCheckEntity::Board LevelManager::mBoard;
std::deque<std::pair<RuleCheckEntity::Board, HashMap<GameObject*, BoardSpaceObject>>> LevelManager::mBoardFrames;

void LevelManager::InitLevelManager(World& world) {
	mWorld = &world;
}

RuleCheckEntity::Board& LevelManager::GetBoard() {
	return mBoard;
}

World* LevelManager::GetWorld() {
	return mWorld;
}

void LevelManager::ClearBoard() {
	for (auto& y : mBoard) {
		for (auto& vec : y) {
			vec.Clear();
		}
	}
}

void LevelManager::StartLevel(int level) {
	mLevel = level;

	if (mLevel == 1)
	{

	}

	Datum& sectorDatum = mWorld->Sectors();
	if (sectorDatum.Size() > 1)
	{
		delete &(sectorDatum[1]);
	}
	ClearBoard();
	mBoardFrames.clear();
	Sector* sector = mWorld->CreateSector("Level");
	ScopeParseHelper::ScopeSharedData data(*sector);
	JsonParseMaster master(data);

	ScopeParseHelper helper;

	master.AddHelper(helper);

	master.ParseFromFile(mLevelNames[mLevel]);

	InitRawBoard();
}

void LevelManager::LoadNextLevel() {
	if (LoadNextLevelBool)
	{
		StartLevel((mLevel + 1) % 7);
		LoadNextLevelBool = false;
	}
}

void LevelManager::LoadCurrentLevel()
{
	if (LoadCurrentLevelBool)
	{
		StartLevel(mLevel);
		LoadCurrentLevelBool = false;
	}
}

void LevelManager::InitRawBoard() {
	Sector* sector = mWorld->Sectors().Get<Scope>(1).As<Sector>();

	if (sector == nullptr) {
		throw std::exception("Fucked world");
	}

	auto& entities = sector->Entities();

	for (uint32_t i = 0; i < entities.Size(); ++i) {
		assert(entities[i].Is(GameObject::TypeIdClass()));
		GameObject* gameObj = static_cast<GameObject*>(&entities[i]);
		int x = gameObj->GetGameObjectPosition()[0];
		int y = gameObj->GetGameObjectPosition()[1];
		mBoard[x][y].PushBack(gameObj);
	}
}

void LevelManager::InitializeGame()
{
	ScopeParseHelper::ScopeSharedData data(*mWorld);
	JsonParseMaster master(data);

	ScopeParseHelper helper;

	master.AddHelper(helper);

	master.ParseFromFile("JsonFiles/Input.json");
}

void LevelManager::TakeBoardSnapShot() {
	if (mBoardFrames.size() > 10) {
		mBoardFrames.pop_front();
	}

	RuleCheckEntity::Board board = mBoard;

	HashMap<GameObject*, BoardSpaceObject> oldState;
	for (uint32_t i = 0u; i < RuleCheckEntity::BOARD_SIZE; ++i)
	{
		for (uint32_t j = 0u; j < RuleCheckEntity::BOARD_SIZE; ++j)
		{
			for (GameObject* entity : board[i][j])
			{
				oldState[entity] = entity->GetGameObjectType();
			}
		}
	}
	
	mBoardFrames.push_back(std::make_pair(board, oldState));
}

void LevelManager::RevertBoard() {
	if (UndoMoveBool) {
		if (mBoardFrames.size() > 0) {
			RuleCheckEntity::Board board = mBoardFrames.back().first;

			LevelManager::ClearBoard();

			mBoard = board;

			for (uint32_t i = 0u; i < RuleCheckEntity::BOARD_SIZE; ++i)
			{
				for (uint32_t j = 0u; j < RuleCheckEntity::BOARD_SIZE; ++j)
				{
					for (GameObject* entity : board[i][j])
					{
						entity->GetGameObjectPosition()[0] = i;
						entity->GetGameObjectPosition()[1] = j;
						
						entity->SetGameObjectType(mBoardFrames.back().second.At(entity));
					}
				}
			}

			mBoardFrames.pop_back();
		}
	
		UndoMoveBool = false;
	}
}

void LevelManager::ClearSnapshots() {
	mBoardFrames.clear();
}