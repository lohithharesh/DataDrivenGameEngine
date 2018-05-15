#pragma once
#include "Action.h"
#include "AbstractFactory.h"
#include "Input.h"
#include "HashMap.h"

namespace FieaGameEngine
{
	class InputAction : public Action
	{
		RTTI_DECLARATIONS(InputAction, Action)
	public:
		InputAction();
		~InputAction();

		void SetInputDirection(InputTypesEnum inputType);
		const InputTypesEnum& SetInputDirection();

		virtual void Update(WorldState& worldState) override;
		static Vector<Signature> Signatures();
	private:
		InputTypesEnum mInputDirection;

		bool PushDirection(std::pair<int,int> pos, WorldState & worldState);

		

		const HashMap<InputTypesEnum, std::pair<int,int>> InputDirectionHash = 
		{
			{InputTypesEnum::UP, {-1,0}},
			{InputTypesEnum::DOWN, { 1, 0} },
			{InputTypesEnum::LEFT,{ 0,-1 } },
			{InputTypesEnum::RIGHT,{ 0,1 } }
		};

	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	};

	ConcreteFactory(InputAction, Action)
}