#pragma once
namespace FieaGameEngine
{
	//Additive hash function, that computes the additive hash of a given byte stream.
	inline uint32_t AdditiveHash(const char* data, const size_t size)
	{
		const uint32_t hashPrime = 31;
		uint32_t hash = 0;
		for (size_t i = 0; i < size; i++)
		{
			hash += (hashPrime * data[i]);
		}
		return hash;
	}

	//Hash functor class.
	template<typename T>
	class HashFunction
	{
	public:
		uint32_t operator()(const T& key) const
		{
			const char* keyCastedData = reinterpret_cast<const char*>(&key);
			return AdditiveHash(keyCastedData, sizeof(T));
		}
	};

	//Specialized hash functor class for the string type.
	template<>
	class HashFunction<std::string>
	{
	public:
		uint32_t operator()(const std::string& key) const
		{
			uint32_t hashPrime = 31;
			uint32_t hash = 0;
			for (uint32_t i = 0; i < key.length(); i++)
			{
				hash += (hashPrime * key[i]);
			}
			return hash;
		}
	};

	//Specialized hash functor class for char* type
	template<>
	class HashFunction<char*>
	{
	public:
		uint32_t operator()(const char* key) const
		{
			return AdditiveHash(key, strlen(key));
		}
	};
}