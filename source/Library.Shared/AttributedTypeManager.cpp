#include "pch.h"
#include "AttributedTypeManager.h"

using namespace FieaGameEngine;

HashMap<uint64_t, Vector<Signature>> AttributedTypeManager::mPrescribedAttributes(15);

void AttributedTypeManager::AddAttributes(uint64_t id, const Vector<Signature>& signatures)
{
	mPrescribedAttributes.Insert(std::make_pair(id, signatures));
}

const Vector<Signature>& AttributedTypeManager::GetSignatures(uint64_t id)
{
	return mPrescribedAttributes.Find(id)->second;
}
