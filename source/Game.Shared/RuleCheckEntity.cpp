#include "pch.h"
#include "RuleCheckEntity.h"
#include "WorldState.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "AudioManager.h"
#include <array>

using namespace std;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(RuleCheckEntity);

	const array<pair<BoardSpaceObject, BoardSpaceObject>, 5>
		RuleCheckEntity::MaterialWordToMaterialMap =
	{
		make_pair(BoardSpaceObject::BABA_WORD, BoardSpaceObject::BABA),
		make_pair(BoardSpaceObject::ROCK_WORD, BoardSpaceObject::ROCK),
		make_pair(BoardSpaceObject::FLAG_WORD, BoardSpaceObject::FLAG),
		make_pair(BoardSpaceObject::WALL_WORD, BoardSpaceObject::WALL),
		make_pair(BoardSpaceObject::SKULL_WORD, BoardSpaceObject::SKULL)
	};

	void RuleCheckEntity::Update(WorldState& worldState)
	{
		UNREFERENCED_PARAMETER(worldState);

		Board& board = FieaGameEngine::LevelManager::mBoard;
		GameObject::ClearAllAspects();

		for (uint32_t i = 0u; i < BOARD_SIZE; ++i)
		{
			for (uint32_t j = 0u; j < BOARD_SIZE; ++j)
			{
				for (GameObject* entity : board[i][j])
				{
					if (entity->GetGameObjectType() == BoardSpaceObject::IS_WORD)
					{
						// look for horizontal sentence
						LookForAndApplyRule(i, j, board, true);
						//look for vertical sentence
						LookForAndApplyRule(j, i, board, false);
					}
				}
			}
		}

		for (uint32_t i = 0u; i < BOARD_SIZE; ++i)
		{
			for (uint32_t j = 0u; j < BOARD_SIZE; ++j)
			{
				bool containsYou = false;
				GameObject* you;
				bool containsWin = false;
				bool containsKill = false;
				for (GameObject* entity : board[i][j])
				{					
					if (GameObject::mRelationships.At(entity->GetGameObjectType()).you)
					{
						you = entity;
						containsYou = true;
					}
					if (GameObject::mRelationships.At(entity->GetGameObjectType()).win)
					{
						containsWin = true;
					}
					if (GameObject::mRelationships.At(entity->GetGameObjectType()).kill)
					{
						containsKill = true;
					}
				}

				if (containsYou && containsWin)
				{
					LevelManager::LoadNextLevelBool = true;
					LevelManager::ClearSnapshots();

					AudioManager::Instance()->Play("Win", false);
				}
				if (containsYou && containsKill)
				{
					board[i][j].Remove(you);

					AudioManager::Instance()->Play("Die", false);

				}
			}
		}
	}

	void RuleCheckEntity::AssignWord(BoardSpaceObject& bso, uint32_t i, uint32_t j, Board& board, bool material) const
	{
		for (GameObject* obj : board[i][j])
		{
			if ((material && IsMaterialWord(obj->GetGameObjectType())) ||
				(!material && IsWord(obj->GetGameObjectType())))
			{
				bso = obj->GetGameObjectType();
				break;
			}
		}
	}

	void RuleCheckEntity::LookForAndApplyRule(uint32_t vary, uint32_t constant, Board& board, bool varyI) const
	{
		if (vary > 0u && vary < BOARD_SIZE - 1u)
		{
			BoardSpaceObject firstWord = BoardSpaceObject::INVALID;
			BoardSpaceObject secondWord = BoardSpaceObject::INVALID;
			if (varyI)
			{
				AssignWord(firstWord, vary - 1u, constant, board, true);
				AssignWord(secondWord, vary + 1u, constant, board, false);
			}
			else
			{
				AssignWord(firstWord, constant, vary - 1u, board, true);
				AssignWord(secondWord, constant, vary + 1u, board, false);
			}

			if (firstWord != BoardSpaceObject::INVALID &&
				secondWord != BoardSpaceObject::INVALID)
			{

				if (IsMaterialWord(secondWord))
				{
					ReplaceMaterialWithMaterial(board, GetMaterialFromMaterialWord(firstWord), GetMaterialFromMaterialWord(secondWord));
				}
				else if (IsAspectWord(secondWord))
				{
					ApplyAspectToMaterial(board, GetMaterialFromMaterialWord(firstWord), secondWord);
				}
			}
		}
	}

	bool RuleCheckEntity::IsWord(BoardSpaceObject bso)
	{
		return (bso > BoardSpaceObject::INVALID) &&
			(bso < BoardSpaceObject::BABA);
	}

	bool RuleCheckEntity::IsMaterialWord(BoardSpaceObject bso)
	{
		return (bso > BoardSpaceObject::IS_WORD) &&
			(bso < BoardSpaceObject::PUSH_WORD);
	}

	bool RuleCheckEntity::IsAspectWord(BoardSpaceObject bso)
	{
		return IsWord(bso) && !IsMaterialWord(bso) &&
			(bso != BoardSpaceObject::IS_WORD);
	}

	void RuleCheckEntity::ReplaceMaterialWithMaterial(Board& board, BoardSpaceObject original, BoardSpaceObject replaceWith)
	{
		for (uint32_t i = 0u; i < BOARD_SIZE; ++i)
		{
			for (uint32_t j = 0u; j < BOARD_SIZE; ++j)
			{
				for (GameObject* entity : board[i][j])
				{
					if (entity->GetGameObjectType() == original)
					{
						entity->SetGameObjectType(replaceWith);
					}
				}
			}
		}
	}

	void RuleCheckEntity::ApplyAspectToMaterial(Board& board, BoardSpaceObject material, BoardSpaceObject aspect)
	{
		UNREFERENCED_PARAMETER(board);
		Aspect asp = static_cast<Aspect>(static_cast<int>(aspect) - 6);
		GameObject::ApplyAspect(material, asp, true);
	}

	BoardSpaceObject RuleCheckEntity::GetMaterialFromMaterialWord(BoardSpaceObject word)
	{
		BoardSpaceObject returnValue = BoardSpaceObject::INVALID;

		for (pair<BoardSpaceObject, BoardSpaceObject> materialPair :
			MaterialWordToMaterialMap)
		{
			if (materialPair.first == word)
			{
				returnValue = materialPair.second;
				break;
			}
		}

		return returnValue;
	}

	Vector<Signature> RuleCheckEntity::Signatures()
	{
		return Entity::Signatures();
	}
}