#pragma once
#include "Entity.h"
#include "AbstractFactory.h"
#include "RuleCheckEntity.h"
#include "HashMap.h"

#include "glm\glm.hpp"

namespace FieaGameEngine
{
	enum class Aspect
	{
		INVALID,
		PUSH,
		STOP,
		KILL,
		WIN,
		YOU,
		MAX
	};

	class GameObject : public Entity
	{
		RTTI_DECLARATIONS(GameObject, Entity)
	private:

		struct Aspects {
			bool bad = false;
			bool push;
			bool stop;
			bool kill;
			bool win;
			bool you;

			bool& GetBool(Aspect asp)
			{
				switch (asp)
				{
				case Aspect::PUSH:
					return push;
				case Aspect::STOP:
					return stop;
				case Aspect::KILL:
					return kill;
				case Aspect::WIN:
					return win;
				case Aspect::YOU:
					return you;
				default:
					return bad;
				}
			}
		};

		int mPosition[2];
		BoardSpaceObject mObjectType;

		

	public:
		GameObject();
		~GameObject();

		static HashMap<BoardSpaceObject, Aspects> mRelationships;

		const BoardSpaceObject& GetGameObjectType();
		void SetGameObjectType(const BoardSpaceObject& boardSpaceObject);

		static void ApplyAspect(BoardSpaceObject bso, Aspect asp, bool newState = true);
		static void ClearAllAspects();
		static Vector<Signature> Signatures();
		int* GetGameObjectPosition();
		void SetGameObjectPosition(int* position);
	};

	ConcreteFactory(GameObject, Entity)
}