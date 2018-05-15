#pragma once
#include "RTTI.h"
namespace FieaGameEngine
{
	class Foo : public FieaGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Foo, RTTI)
	private:
		int data;
		int* dataPointer;
	public:
		Foo() { data = 10; };
		Foo(int dataValue);
		Foo(const Foo& rhs);
		Foo& operator=(const Foo& rhs);
		const bool operator==(const Foo& rhs) const;
		const bool operator!=(const Foo& rhs) const;
		const int Data() const;
		const int* DataPointer() const;
		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;
		~Foo();
	};
}


namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<FieaGameEngine::Foo>(const FieaGameEngine::Foo& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}
}