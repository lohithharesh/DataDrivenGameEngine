#pragma once
namespace FieaGameEngine
{
	//Equality functor class.
	template<typename TKey>
	class Equality
	{
	public:
		bool operator()(const TKey& lhs, const TKey& rhs) const
		{
			return (lhs == rhs);
		}
	};

	//Specialized equality functor class.
	template<>
	class Equality<char*>
	{
	public:
		bool operator()(const char* lhs, const char* rhs) const
		{
			if (!strcmp(lhs, rhs))
			{
				return true;
			}
			return false;
		}
	};
}