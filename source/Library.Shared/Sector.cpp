#include "pch.h"
#include "Sector.h"
#include "AbstractFactory.h"
#include "World.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(Sector)

Sector::Sector(const std::string& name) : Attributed(Sector::TypeIdClass())
{
	SetName(name);
}

const std::string& Sector::Name() const
{
	return mName;
}

void Sector::SetName(const std::string& name)
{
	mName = name;
}

Datum& Sector::Entities() const
{
	return *Find("Entities");
}

Entity* Sector::CreateEntity(const std::string& className,const std::string& instanceName)
{
	 Entity* entity = AbstractFactory<Entity>::Create(className); 
	 assert(entity != nullptr);
	 entity->SetName(instanceName);
	 entity->SetSector(*this);
	 return entity;
}

void Sector::SetWorld(World& ownerWorld)
{
	ownerWorld.Adopt(*this, "Sectors");
}

World* Sector::GetWorld() const
{
	Scope* parent = GetParent();
	assert(parent->Is(World::TypeName()));
	return static_cast<World*>(parent);
}

void Sector::Update(WorldState& worldState)
{
	worldState.mCurrentSector = this;
	Datum* entities = Find("Entities");
	for (uint32_t i = 0; i < entities->Size(); i++)
	{
		Scope& entityScope = entities->Get<Scope>(i);
		assert(entityScope.Is("Entity"));
		Entity* entity = static_cast<Entity*>(&entityScope);
		entity->Update(worldState);
	}
	worldState.mCurrentSector = nullptr;
}


Vector<Signature> Sector::Signatures()
{
	Vector<Signature> signatures;
	signatures.PushBack({ "Name", DatumTypeEnum::String, 1, offsetof(Sector, mName) });
	signatures.PushBack({ "Entities", DatumTypeEnum::Table, 0, 0 });
	return signatures;
}

Scope* Sector::Clone(const Scope& rhs)
{
	return new Sector(*(rhs.As<Sector>()));
}