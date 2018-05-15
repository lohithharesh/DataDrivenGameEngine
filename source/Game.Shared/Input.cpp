#include "pch.h"
#include "Input.h"
#include "WorldState.h"
#include <conio.h>
#include "World.h"
#include "Event.h"
#include "ActionListIf.h"
#include "LevelManager.h"
#include "AudioManager.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(Input)

Input::Input() : Entity(Input::TypeIdClass())
{
	mKeyboard = std::make_unique<DirectX::Keyboard>();
}

void Input::Update(WorldState& worldState)
{
	bool didGetInput = false;
	std::shared_ptr<Event<InputTypesEnum>> event;

	auto kb = mKeyboard->GetState();	

	if (kb.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(mMoveUpKey)) && !mUpPressed)
	{
		mUpPressed = true;
		mDownPressed = false;
		mRightPressed = false;
		mLeftPressed = false;
		mResetPressed = false;
		mUndoPressed = false;
		didGetInput = true;
		event = std::make_shared<Event<InputTypesEnum>>(InputTypesEnum::UP);

		LevelManager::TakeBoardSnapShot();
	}
	else if (kb.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(mMoveDownKey)) && !mDownPressed)
	{
		mUpPressed = false;
		mDownPressed = true;
		mRightPressed = false;
		mLeftPressed = false;
		mResetPressed = false;
		mUndoPressed = false;
		didGetInput = true;
		event = std::make_shared<Event<InputTypesEnum>>(InputTypesEnum::DOWN);

		LevelManager::TakeBoardSnapShot();
	}
	else if (kb.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(mMoveLeftKey)) && !mLeftPressed)
	{
		mUpPressed = false;
		mDownPressed = false;
		mRightPressed = false;
		mLeftPressed = true;
		mResetPressed = false;
		mUndoPressed = false;
		didGetInput = true;
		event = std::make_shared<Event<InputTypesEnum>>(InputTypesEnum::LEFT);

		LevelManager::TakeBoardSnapShot();
	}
	else if (kb.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(mMoveRightKey)) && !mRightPressed)
	{
		mUpPressed = false;
		mDownPressed = false;
		mRightPressed = true;
		mLeftPressed = false;
		mResetPressed = false;
		mUndoPressed = false;
		didGetInput = true;
		event = std::make_shared<Event<InputTypesEnum>>(InputTypesEnum::RIGHT);

		LevelManager::TakeBoardSnapShot();
	}
	else if (kb.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(mResetKey)) && !mResetPressed)
	{
		mUpPressed = false;
		mDownPressed = false;
		mRightPressed = false;
		mLeftPressed = false;
		mUndoPressed = false;
		mResetPressed = true;
		didGetInput = false;
		assert(&Actions()[0] != nullptr);
		ActionListIf* action = Actions()[0].As<ActionListIf>();
		action->SetCondition(1);

		AudioManager::Instance()->Play("Reset", false);
	}
	else if (kb.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(mUndoKey)) && !mUndoPressed)
	{
		mUpPressed = false;
		mDownPressed = false;
		mRightPressed = false;
		mLeftPressed = false;
		mResetPressed = false;
		mUndoPressed = true;
		didGetInput = false;
			
		LevelManager::UndoMoveBool = true;

		AudioManager::Instance()->Play("Undo", false);
	}
	else if(!kb.R && !kb.W && !kb.S && !kb.A && !kb.D && !kb.Z)
	{
		mUpPressed = false;
		mDownPressed = false;
		mRightPressed = false;
		mLeftPressed = false;
		mResetPressed = false;
		mUndoPressed = false;
	}
	
	if (didGetInput)
	{
		worldState.mCurrentWorld->GetEventQueue().Enqueue(event, worldState.mGameTime);
		worldState.mCurrentWorld->GetEventQueue().Update(worldState.mGameTime);
	}

	Datum* actions = Find("Actions");
	for (uint32_t i = 0; i < actions->Size(); i++)
	{
		Scope& actionScope = actions->Get<Scope>(i);
		assert(actionScope.Is("Action"));
		Action* action = static_cast<Action*>(&actionScope);
		action->Update(worldState);
	}
}

Input::~Input()
{
}

Vector<Signature> Input::Signatures()
{
	Vector<Signature> signatures = Entity::Signatures();
	signatures.PushBack({ "MoveUpKey", DatumTypeEnum::Integer, 1, offsetof(Input, mMoveUpKey) });
	signatures.PushBack({ "MoveDownKey", DatumTypeEnum::Integer, 1, offsetof(Input, mMoveDownKey) });
	signatures.PushBack({ "MoveLeftKey", DatumTypeEnum::Integer, 1, offsetof(Input, mMoveLeftKey) });
	signatures.PushBack({ "MoveRightKey", DatumTypeEnum::Integer, 1, offsetof(Input, mMoveRightKey) });
	signatures.PushBack({ "ResetKey", DatumTypeEnum::Integer, 1, offsetof(Input, mResetKey) });
	signatures.PushBack({ "UndoKey", DatumTypeEnum::Integer, 1, offsetof(Input, mUndoKey) });
	return signatures;
}
