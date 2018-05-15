#include "pch.h"
#include "Furniture.h"
#include "WorldState.h"
using namespace FieaGameEngine;

RTTI_DEFINITIONS(Furniture)

Furniture::Furniture() : Entity(Furniture::TypeIdClass())
{

}



void Furniture::Update(WorldState& worldState)
{
	worldState.mCurrentEntity = this;
	Datum* actions = Find("Actions");
	for (uint32_t i = 0; i < actions->Size(); i++)
	{
		Scope& actionScope = actions->Get<Scope>(i);
		assert(actionScope.Is("Action"));
		Action* action = static_cast<Action*>(&actionScope);
		action->Update(worldState);
	}
	worldState.mCurrentEntity = nullptr;
}

Vector<Signature> Furniture::Signatures()
{
	Vector<Signature> signatures = Entity::Signatures();
	signatures.PushBack({ "Height", DatumTypeEnum::Float, 1, offsetof(Furniture, mHeight) });
	return signatures;
}

Scope* Furniture::Clone(const Scope& rhs)
{
	return new Furniture(*(rhs.As<Furniture>()));
}