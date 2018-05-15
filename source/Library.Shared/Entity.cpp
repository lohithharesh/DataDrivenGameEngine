#include "pch.h"
#include "Entity.h"
#include "Sector.h"
#include "WorldState.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(Entity)

Entity::Entity(const std::string& name) : Attributed(Entity::TypeIdClass())
{
	SetName(name);
}

Entity::Entity(uint64_t id) : Attributed(id)
{

}
const std::string& Entity::Name() const
{
	return mName;
}

void Entity::SetName(const std::string& name)
{
	mName = name;
}

Sector* Entity::GetSector() const
{
	Scope* parent = GetParent();
	assert(parent->Is(Sector::TypeName()));
	return static_cast<Sector*>(parent);
}

void Entity::SetSector(Sector& sector)
{
	sector.Adopt(*this, "Entities");
}

void Entity::Update(WorldState& worldState)
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

Action* Entity::CreateAction(const std::string& className, const std::string& instanceName)
{
	Action* action = AbstractFactory<Action>::Create(className);
	assert(action != nullptr);
	action->SetName(instanceName);
	Adopt(*action, "Actions");
	return action;
}

Datum& Entity::Actions() const
{
	return *Find("Actions");
}

Vector<Signature> Entity::Signatures()
{
	Vector<Signature> signatures;
	signatures.PushBack({ "Name", DatumTypeEnum::String, 1, offsetof(Entity, mName) });
	signatures.PushBack({ "Actions", DatumTypeEnum::Table, 0, 0 });
	return signatures;
}

Entity::~Entity()
{
}

Scope* Entity::Clone(const Scope& rhs)
{
	return new Entity(*(rhs.As<Entity>()));
}