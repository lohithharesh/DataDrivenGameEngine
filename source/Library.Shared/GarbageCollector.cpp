#include "pch.h"
#include "GarbageCollector.h"

using namespace FieaGameEngine;

Vector<Scope*> GarbageCollector::garbageList(5);

void GarbageCollector::CleanUp()
{
	for (auto scope : garbageList)
	{
		delete scope;
	}
	garbageList.Clear();
}
