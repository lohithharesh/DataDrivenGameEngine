#include "pch.h"
#include "Reaction.h"

using namespace FieaGameEngine;
RTTI_DEFINITIONS(Reaction)

Reaction::Reaction(uint64_t typeId) : ActionList(typeId)
{

}

Vector<Signature> Reaction::Signatures()
{
	Vector<Signature> signatures = ActionList::Signatures();
	return signatures;
}
