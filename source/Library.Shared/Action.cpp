#include "pch.h"
#include "Action.h"
#include "ActionList.h"
#include "Entity.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(Action);

Action::Action() : Action("")
{
	
}

Action::Action(const std::string& name) : Attributed(Action::TypeIdClass())
{
	SetName(name);
}

Action::Action(uint64_t id) : Attributed(id)
{

}


const std::string& Action::Name() const
{
	return mName;
}

void Action::SetName(const std::string& name)
{
	mName = name;
}

Vector<Signature> Action::Signatures()
{
	Vector<Signature> signatures;
	signatures.PushBack({ "Name", DatumTypeEnum::String, 1, offsetof(Action, mName) });
	return signatures;
}
