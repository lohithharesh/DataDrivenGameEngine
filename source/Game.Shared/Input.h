#pragma once
#include "Entity.h"
#include "AbstractFactory.h"
#include <Keyboard.h>

namespace FieaGameEngine
{
	enum class InputTypesEnum
	{
		INVALID,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		RESET,
		MAX_NUMBER_OF_TYPES
	};

	class Input : public Entity
	{
		RTTI_DECLARATIONS(Input, Entity)
	public:
		Input();
		Input(const Input& rhs) = delete;
		Input(Input&& rhs) = delete;
		Input& operator=(const Input& rhs) = delete;
		Input& operator=(Input&& rhs) = delete;
		virtual void Update(WorldState& worldState) override;
		static Vector<Signature> Signatures();
		~Input();
	private:
		bool mUpPressed = false;
		bool mDownPressed = false;
		bool mLeftPressed = false;
		bool mRightPressed = false;
		bool mResetPressed = false;
		bool mUndoPressed = false;

		int mMoveLeftKey;
		int mMoveRightKey;
		int mMoveUpKey;
		int mMoveDownKey;
		int mResetKey;
		int mUndoKey;
		std::unique_ptr<DirectX::Keyboard> mKeyboard; 
	};

	ConcreteFactory(Input, Entity)
}

