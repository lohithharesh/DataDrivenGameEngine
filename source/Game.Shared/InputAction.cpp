#include "pch.h"
#include "InputAction.h"
#include "WorldState.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "AudioManager.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(InputAction)

	InputAction::InputAction() : Action(InputAction::TypeIdClass())
	{
	}


	InputAction::~InputAction()
	{
	}


	void FieaGameEngine::InputAction::Update(WorldState & worldState)
	{
		Vector<GameObject*> players(0);
		auto& board = FieaGameEngine::LevelManager::mBoard;
		for (int i = 0; i < BoardSize; ++i)
		{
			for (int j = 0; j < BoardSize; ++j)
			{
				for (GameObject* gameObject : board[i][j])
				{
					if (GameObject::mRelationships.At(gameObject->GetGameObjectType()).you)
					{
						players.PushBack(gameObject);
					}
				}
			}
		}

		for (auto& you : players)
		{
			int* youPos = you->GetGameObjectPosition();
			std::pair<int, int> dir = InputDirectionHash.At(mInputDirection);
			std::pair<int, int> pos = { youPos[0] + dir.first, youPos[1] + dir.second };

			if (pos.first < 0 || pos.first >= BoardSize || pos.second < 0 || pos.second >= BoardSize)
			{
				continue;
			}

			bool isThereStop = false;

			for (GameObject* gameObject : board[pos.first][pos.second])
			{
				if (GameObject::mRelationships.At(gameObject->GetGameObjectType()).stop)
				{
					isThereStop = true;
					break;
				}
			}

			bool isTherePushable = false;
			bool didPush = false;

			if (!isThereStop)
			{
				for (GameObject* gameObject : board[pos.first][pos.second])
				{
					if (GameObject::mRelationships.At(gameObject->GetGameObjectType()).push)
					{
						isTherePushable = true;
						int poses[2] = { pos.first + InputDirectionHash.At(mInputDirection).first, pos.second + InputDirectionHash.At(mInputDirection).second };
						if (PushDirection({ poses[0], poses[1] }, worldState))
						{
							didPush = true;
							LevelManager::mBoard[gameObject->GetGameObjectPosition()[0]][gameObject->GetGameObjectPosition()[1]].Remove(gameObject);
							gameObject->SetGameObjectPosition(poses);
							LevelManager::mBoard[gameObject->GetGameObjectPosition()[0]][gameObject->GetGameObjectPosition()[1]].PushBack(gameObject);
							break;
						}
					}
				}
			}

			if (didPush)
			{
				LevelManager::mBoard[you->GetGameObjectPosition()[0]][you->GetGameObjectPosition()[1]].Remove(you);
				int poses[2] = { youPos[0] + InputDirectionHash.At(mInputDirection).first, youPos[1] + InputDirectionHash.At(mInputDirection).second };
				you->SetGameObjectPosition(poses);
				LevelManager::mBoard[you->GetGameObjectPosition()[0]][you->GetGameObjectPosition()[1]].PushBack(you);

				AudioManager::Instance()->Play("Move", false);

			}

			if (!isThereStop && !isTherePushable)
			{
				LevelManager::mBoard[you->GetGameObjectPosition()[0]][you->GetGameObjectPosition()[1]].Remove(you);
				int poses[2] = { youPos[0] + InputDirectionHash.At(mInputDirection).first, youPos[1] + InputDirectionHash.At(mInputDirection).second };
				you->SetGameObjectPosition(poses);
				LevelManager::mBoard[you->GetGameObjectPosition()[0]][you->GetGameObjectPosition()[1]].PushBack(you);

			}
		}
	}

	bool FieaGameEngine::InputAction::PushDirection(std::pair<int, int> pos, WorldState & worldState)
	{
		if (pos.first < 0 || pos.first >= BoardSize || pos.second < 0 || pos.second >= BoardSize)
		{
			return false;
		}
		else
		{
			auto& board = FieaGameEngine::LevelManager::mBoard;
						
			for (GameObject* gameObject : board[pos.first][pos.second])
			{
				if (GameObject::mRelationships.At(gameObject->GetGameObjectType()).stop)
				{
					return false;
				}
			}

			for (GameObject* gameObject : board[pos.first][pos.second])
			{
				if (GameObject::mRelationships.At(gameObject->GetGameObjectType()).push)
				{
					bool canPush = PushDirection(std::make_pair(pos.first + InputDirectionHash.At(mInputDirection).first, pos.second + InputDirectionHash.At(mInputDirection).second), worldState);
					if (canPush)
					{
						int poses[2] = { pos.first + InputDirectionHash.At(mInputDirection).first, pos.second + InputDirectionHash.At(mInputDirection).second };
						LevelManager::mBoard[gameObject->GetGameObjectPosition()[0]][gameObject->GetGameObjectPosition()[1]].Remove(gameObject);
						gameObject->SetGameObjectPosition(poses);
						LevelManager::mBoard[gameObject->GetGameObjectPosition()[0]][gameObject->GetGameObjectPosition()[1]].PushBack(gameObject);
					}
					return canPush;
				}
			}

			return true;
		}

	}

	void FieaGameEngine::InputAction::SetInputDirection(InputTypesEnum inputType)
	{
		mInputDirection = inputType;
	}

	const InputTypesEnum & FieaGameEngine::InputAction::SetInputDirection()
	{
		return mInputDirection;
	}

	Vector<Signature> InputAction::Signatures()
	{
		return Action::Signatures();
	}

	Scope * FieaGameEngine::InputAction::Clone(const Scope & rhs)
	{
		return new InputAction(*(rhs.As<InputAction>()));
	}
}
