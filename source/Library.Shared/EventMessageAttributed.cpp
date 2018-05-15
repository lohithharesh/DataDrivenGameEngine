#include "pch.h"
#include "EventMessageAttributed.h"
#include "World.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(EventMessageAttributed)

EventMessageAttributed::EventMessageAttributed() : Attributed(EventMessageAttributed::TypeIdClass())
{

}

void EventMessageAttributed::SetWorld(World& world)
{
	mWorld = &world;
}

World* EventMessageAttributed::GetWorld()
{
	return mWorld;
}

void EventMessageAttributed::SetSubType(const std::string& subType)
{
	mSubType = subType;
}

const std::string& EventMessageAttributed::GetSubType()
{
	return mSubType;
}




Vector<Signature> EventMessageAttributed::Signatures()
{
	Vector<Signature> signatures;
	signatures.PushBack({ "SubType", DatumTypeEnum::String, 1, offsetof(EventMessageAttributed, mSubType) });
	signatures.PushBack({ "World", DatumTypeEnum::RTTI, 1, offsetof(EventMessageAttributed, mWorld) });
	return signatures;
}

Scope* EventMessageAttributed::Clone(const Scope& rhs)
{
	return new EventMessageAttributed(*(rhs.As<EventMessageAttributed>()));
}