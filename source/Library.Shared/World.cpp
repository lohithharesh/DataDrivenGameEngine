#include "pch.h"
#include "World.h"
#include "GarbageCollector.h"
#include "AbstractFactory.h"

using namespace FieaGameEngine;
using namespace std;
RTTI_DEFINITIONS(World)

World::World(const std::string& name) : Attributed(World::TypeIdClass())
{
	SetName(name);
}

const std::string& World::Name() const
{
	return mName;
}

void World::SetName(const std::string& name)
{
	mName = name;
}

Datum& World::Sectors()
{
	return *Find("Sectors");
}

Datum& World::Reactions()
{
	return *Find("Reactions");
}

Sector* World::CreateSector(const std::string& name)
{
	Sector* newSector = new Sector();
	newSector->SetName(name);
	newSector->SetWorld(*this);
	return newSector;
}

void World::Update()
{
	mWorldState.mCurrentWorld = this;
	mWorldState.mGameClock.UpdateGameTime(mWorldState.mGameTime);
	Datum* sectors = Find("Sectors");
	if (sectors != nullptr)
	{
		for (uint32_t i = 0; i < sectors->Size(); i++)
		{
			Scope& sectorScope = sectors->Get<Scope>(i);
			assert(sectorScope.Is("Sector"));
			Sector* sector = static_cast<Sector*>(&sectorScope);
			sector->Update(mWorldState);
		}
	}
	mEventQueue.Update(mWorldState.mGameTime);
	mWorldState.mCurrentWorld = nullptr;
	GarbageCollector::CleanUp();
} 

World::~World()
{
	mEventQueue.Clear();
}

Vector<Signature> World::Signatures()
{
	Vector<Signature> signatures;
	signatures.PushBack({ "Name", DatumTypeEnum::String, 1, offsetof(World, mName) });
	signatures.PushBack({ "Sectors", DatumTypeEnum::Table, 0, 0 });
	signatures.PushBack({ "Reactions", DatumTypeEnum::Table , 0, 0 });
	return signatures;
}

Scope* World::Clone(const Scope& rhs)
{
	return new World(*(rhs.As<World>()));
}

WorldState& World::GetWorldState()
{
	return mWorldState;
}

Reaction* World::CreateReaction(const std::string& className, const std::string& instanceName)
{
	Reaction* reaction = AbstractFactory<Reaction>::Create(className);
	assert(reaction != nullptr);
	reaction->SetName(instanceName);
	Adopt(*reaction, "Reactions");
	return reaction;
}

EventQueue& World::GetEventQueue()
{
	return mEventQueue;
}