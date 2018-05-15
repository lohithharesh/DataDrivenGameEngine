#include "pch.h"
#include "ResetActionIf.h"
#include "WorldState.h"
#include "LevelManager.h"
#include "ActionListIf.h"
using namespace FieaGameEngine;
RTTI_DEFINITIONS(ResetActionIf)

ResetActionIf::ResetActionIf() : Action(ResetActionIf::TypeIdClass())
{

}


Vector<Signature> ResetActionIf::Signatures()
{
	return Action::Signatures();
}

void ResetActionIf::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	LevelManager::LoadCurrentLevelBool = true;
	GetParent()->As<ActionListIf>()->SetCondition(0);
	worldState.mCurrentAction = nullptr;
}

ResetActionIf::~ResetActionIf()
{
}

Scope * FieaGameEngine::ResetActionIf::Clone(const Scope & rhs)
{
	return new ResetActionIf(*(rhs.As<ResetActionIf>()));
}
