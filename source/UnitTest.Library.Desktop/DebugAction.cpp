#include "pch.h"
#include "DebugAction.h"
#include "WorldState.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(DebugAction)

DebugAction::DebugAction() : Action(DebugAction::TypeIdClass())
{

}

void DebugAction::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	std::wstring stemp = std::wstring(mDebugMessage.begin(), mDebugMessage.end());
	LPCWSTR sw = stemp.c_str();
	OutputDebugString(sw);
	Datum* rs = Search("ReactionString");
	if (rs != nullptr)
	{
		mReactionMessage = rs->Get<std::string>();
	}
	worldState.mCurrentAction = nullptr;
}

DebugAction::~DebugAction()
{
}

Vector<Signature> DebugAction::Signatures()
{
	Vector<Signature> signatures = Action::Signatures();
	signatures.PushBack({ "DebugMessage", DatumTypeEnum::String, 1, offsetof(DebugAction, mDebugMessage) });
	return signatures;
}

Scope* DebugAction::Clone(const Scope& rhs)
{
	return new DebugAction(*(rhs.As<DebugAction>()));
}