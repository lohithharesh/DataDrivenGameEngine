#include "pch.h"
#include "GameObject.h"
#include "LevelManager.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameObject)
	HashMap<BoardSpaceObject, GameObject::Aspects> GameObject::mRelationships  = 
	{
		{ BoardSpaceObject::INVALID, { false, false, false, false, false, false } },
		{ BoardSpaceObject::IS_WORD, {false, true, false, false, false, false}},
		{ BoardSpaceObject::BABA_WORD, { false, true, false, false, false, false } },
		{ BoardSpaceObject::ROCK_WORD, {false, true, false, false, false, false}},
		{ BoardSpaceObject::FLAG_WORD, { false, true, false, false, false, false }},
		{ BoardSpaceObject::SKULL_WORD, { false, true, false, false, false, false }},
		{ BoardSpaceObject::WALL_WORD, { false, true, false, false, false, false }},
		{ BoardSpaceObject::YOU_WORD, { false, true, false, false, false, false }},
		{ BoardSpaceObject::DIE_WORD, { false, true, false, false, false, false }},
		{ BoardSpaceObject::WIN_WORD, { false, true, false, false, false, false }},
		{ BoardSpaceObject::STOP_WORD, { false, true, false, false, false, false }},
		{ BoardSpaceObject::PUSH_WORD, { false, true, false, false, false, false }},
		{ BoardSpaceObject::BABA, { false, false, false, false, false, true } },
		{ BoardSpaceObject::ROCK, { false, true, false, false, false, false } },
		{ BoardSpaceObject::FLAG, { false, false, false, false, false, false } },
		{ BoardSpaceObject::SKULL, { false, false, false, false, false, false } },
		{ BoardSpaceObject::WALL, { false, false, true, false, false, false } },
		{ BoardSpaceObject::BUSH, { false, false, false, false, false, false } }
	};

	GameObject::GameObject() : Entity(GameObject::TypeIdClass())
	{
	}


	GameObject::~GameObject()
	{
	}

	const BoardSpaceObject& GameObject::GetGameObjectType()
	{
		return mObjectType;
	}

	void FieaGameEngine::GameObject::SetGameObjectType(const BoardSpaceObject & boardSpaceObject)
	{
		mObjectType = boardSpaceObject;
	}

	int* FieaGameEngine::GameObject::GetGameObjectPosition()
	{
		return mPosition;
	}

	void FieaGameEngine::GameObject::SetGameObjectPosition(int* position)
	{
		
		mPosition[0] = position[0];
		mPosition[1] = position[1];
		
	}

	void FieaGameEngine::GameObject::ApplyAspect(BoardSpaceObject bso, Aspect asp, bool newState)
	{
		mRelationships.At(bso).GetBool(asp) = newState;
	}

	void FieaGameEngine::GameObject::ClearAllAspects()
	{
		for (auto it = mRelationships.begin(); it != mRelationships.end(); ++it)
		{
			if (!RuleCheckEntity::IsWord(it->first))
			{
				it->second.push = false;
				it->second.stop = false;
				it->second.kill = false;
				it->second.win = false;
				it->second.you = false;
			}
		}
	}

	Vector<Signature> GameObject::Signatures()
	{
		Vector<Signature> signatures = Entity::Signatures();
		signatures.PushBack({ "Position", DatumTypeEnum::Integer, 2, offsetof(GameObject, mPosition) });
		signatures.PushBack({ "ObjectType", DatumTypeEnum::Integer, 1, offsetof(GameObject, mObjectType) });
		return signatures;
	}
}