#include "pch.h"
#include "Foo.h"

namespace FieaGameEngine {

	RTTI_DEFINITIONS(Foo)

	Foo::Foo(int dataValue) : data(dataValue), dataPointer(new int(dataValue))
	{

	}

	Foo::Foo(const Foo& rhs) : data(rhs.data), dataPointer(new int(rhs.data))
	{

	}

	Foo& Foo::operator=(const Foo& rhs)
	{
		if (this != &rhs)
		{
			delete dataPointer;
			data = rhs.data;
			dataPointer = new int(data);
		}
		return *this;
	}

	const bool Foo::operator==(const Foo& rhs) const
	{
		if (dataPointer == rhs.dataPointer)
		{
			return data == rhs.data;
		}
		if (dataPointer == nullptr || rhs.dataPointer == nullptr)
		{
			return false;
		}
		return data == rhs.data && *dataPointer == *(rhs.dataPointer);
	}

	const bool Foo::operator!=(const Foo& rhs) const
	{
		return !operator==(rhs);
	}

	const int Foo::Data() const
	{
		return data;
	}

	const int* Foo::DataPointer() const
	{
		return dataPointer;
	}

	Foo::~Foo()
	{
		delete dataPointer;
	}

	bool Foo::Equals(const RTTI* rhs) const 
	{
		Foo* f = rhs->As<Foo>();
		return (data == f->data && *(f->dataPointer) == *dataPointer);
	}

	std::string Foo::ToString() const
	{
		return std::to_string(data);
	}
}
