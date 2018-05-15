#include "pch.h"
#include "ResetActionElse.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(ResetActionElse)

ResetActionElse::ResetActionElse() : Action(ResetActionElse::TypeIdClass())
{
}


ResetActionElse::~ResetActionElse()
{
}

Vector<Signature> ResetActionElse::Signatures()
{
	return Action::Signatures();
}

Scope * FieaGameEngine::ResetActionElse::Clone(const Scope & rhs)
{
	return new ResetActionElse(*(rhs.As<ResetActionElse>()));
}

void ResetActionElse::Update(WorldState& worldState)
{
	UNREFERENCED_PARAMETER(worldState);
}