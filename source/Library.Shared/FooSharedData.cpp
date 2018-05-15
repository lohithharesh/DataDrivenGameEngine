#include "pch.h"
#include "FooSharedData.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(FooSharedData)

FooSharedData::FooSharedData(ParseTestFoo& f) : foo(&f)
{

}

FooSharedData* FooSharedData::Clone()
{
	FooSharedData* f = new FooSharedData(*foo);
	return f;
}

FooSharedData::~FooSharedData()
{
	
}

ParseTestFoo* FooSharedData::getFooPointer()
{
	return foo;
}

void FooSharedData::Initialize()
{

}