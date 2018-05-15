#pragma once
#include "HashMap.h"
template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::Iterator() : mOwner(nullptr)
{

}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::Iterator(const HashMap& owner, typename const ChainIterator& chainIterator, const uint32_t bucketIndex) : mOwner(&owner), mChainIterator(chainIterator), mBucketIndex(bucketIndex)
{

}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator& HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::operator++()
{
	if (mOwner == nullptr)
	{
		throw std::exception("Invalid iterator");
	}
	if (mBucketIndex == mOwner->mBucket.Capacity())
	{
		throw std::exception("out of bounds");
	}
	if (++mChainIterator != mOwner->mBucket[mBucketIndex].end())
	{
		return *this;
	}
	while (++mBucketIndex < mOwner->mBucket.Size())
	{
		if (!mOwner->mBucket[mBucketIndex].IsEmpty())
		{
			mChainIterator = mOwner->mBucket[mBucketIndex].begin();
			return *this;
		}
	}
	mChainIterator = mOwner->mBucket[mOwner->mBucket.Capacity() - 1].end();
	return *this;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::operator++(int)
{
	Iterator temp = *this;
	operator++();
	return temp;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
bool  HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::operator==(const Iterator& rhs) const
{
	return (mOwner == rhs.mOwner && mBucketIndex == rhs.mBucketIndex && mChainIterator == rhs.mChainIterator);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
bool  HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::operator!=(const Iterator& rhs) const
{
	return !operator==(rhs);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::PairType& HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::operator*()
{
	if (mOwner == nullptr || mBucketIndex >= mOwner->mBucket.Size())
	{
		throw std::exception("Invalid iterator");
	}
	return *mChainIterator;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename const HashMap<TKey, TData, HashFunctor, EqualityFunction>::PairType& HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::operator*() const
{
	if (mOwner == nullptr || mBucketIndex >= mOwner->mBucket.Size())
	{
		throw std::exception("Invalid iterator");
	}
	return const_cast<PairType&>(*mChainIterator);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::PairType* HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::operator->()
{
	if (mOwner == nullptr || mBucketIndex >= mOwner->mBucket.Size())
	{
		throw std::exception("Invalid iterator");
	}
	return &(*mChainIterator);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename const HashMap<TKey, TData, HashFunctor, EqualityFunction>::PairType* HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator::operator->() const
{
	if (mOwner == nullptr || mBucketIndex >= mOwner->mBucket.Size())
	{
		throw std::exception("Invalid iterator");
	}
	return &(*mChainIterator);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
HashMap<TKey, TData, HashFunctor, EqualityFunction>::HashMap(uint32_t bucketSize) : mBucket(BucketType(bucketSize))
{
	mBucket.Resize(bucketSize);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
HashMap<TKey, TData, HashFunctor, EqualityFunction>::HashMap(std::initializer_list<PairType> list) : HashMap(static_cast<uint32_t>(list.size()))
{
	for (auto& entry : list)
	{
		Insert(entry);
	}
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
HashMap<TKey, TData, HashFunctor, EqualityFunction>::HashMap(HashMap&& rhs)
{
	operator=(std::move(rhs));
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
HashMap<TKey, TData, HashFunctor, EqualityFunction>& HashMap<TKey, TData, HashFunctor, EqualityFunction>::operator=(HashMap&& rhs)
{
	if (this != &rhs)
	{
		mBucket = std::move(rhs.mBucket);
		mHashFunction = std::move(rhs.mHashFunction);
		mEquals = std::move(rhs.mEquals);
		mSize = std::move(rhs.mSize);
		rhs.mSize = 0;
	}
	return *this;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator HashMap<TKey, TData, HashFunctor, EqualityFunction>::Find(const TKey& key, uint32_t& bucketIndex) const
{
	
	bucketIndex = mHashFunction(key) % mBucket.Capacity();
	auto& chain = mBucket[bucketIndex];
	for (ChainIterator it = chain.begin(); it != chain.end(); it++)
	{
		if (mEquals(key, (*it).first))
		{
			return Iterator(*this, it, bucketIndex);
		}
	}
	return end();
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator HashMap<TKey, TData, HashFunctor, EqualityFunction>::Find(const TKey& key) const
{

	uint32_t bucketIndex;
	return Find(key, bucketIndex);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator HashMap<TKey, TData, HashFunctor, EqualityFunction>::Insert(const PairType& entry, bool& wasInserted)
{
	uint32_t bucketIndex;
	Iterator it = Find(entry.first, bucketIndex);
	if (it != end())
	{
		wasInserted = false;
		return it;
	}
	mSize++;
	wasInserted = true;
	return Iterator(*this, mBucket[bucketIndex].PushBack(entry), bucketIndex);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator HashMap<TKey, TData, HashFunctor, EqualityFunction>::Insert(const PairType& entry)
{
	bool wasInserted;
	return Insert(entry, wasInserted);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator HashMap<TKey, TData, HashFunctor, EqualityFunction>::begin() const
{
	uint32_t index = 0;
	while (index < mBucket.Capacity() && mBucket[index].IsEmpty())
	{
		index++;
	}
	if (index == mBucket.Capacity())
	{
		throw std::exception("Map is empty");
	}
	return Iterator(*this, mBucket[index].begin(), index);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
typename HashMap<TKey, TData, HashFunctor, EqualityFunction>::Iterator HashMap<TKey, TData, HashFunctor, EqualityFunction>::end() const
{
	return Iterator(*this, mBucket[mBucket.Capacity() - 1].end(), mBucket.Capacity());
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
TData& HashMap<TKey, TData, HashFunctor, EqualityFunction>::operator[](const TKey& key)
{
	return Insert(std::make_pair(key, TData()))->second;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
uint32_t HashMap<TKey, TData, HashFunctor, EqualityFunction>::Size() const
{
	return mSize;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
bool HashMap<TKey, TData, HashFunctor, EqualityFunction>::Remove(const TKey& key)
{
	auto it = Find(key);
	if (it == end())
	{
		return false;
	}
	mBucket[it.mBucketIndex].Remove(it.mChainIterator);
	mSize--;
	return true;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
void HashMap<TKey, TData, HashFunctor, EqualityFunction>::Clear()
{
	for (uint32_t i = 0; i < mBucket.Size(); i++)
	{
		mBucket[i].Clear();
	}
	mSize = 0;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
bool HashMap<TKey, TData, HashFunctor, EqualityFunction>::ContainsKey(const TKey& key,TData& data) const
{
	auto it = Find(key);
	if (it != end())
	{
		data = (*it).second;
		return true;
	}
	return false;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
bool HashMap<TKey, TData, HashFunctor, EqualityFunction>::ContainsKey(const TKey& key) const
{
	TData data;
	return ContainsKey(key, data);
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
const TData& HashMap<TKey, TData, HashFunctor, EqualityFunction>::At(const TKey& key) const
{
	auto it = Find(key);
	if (it == end())
	{
		throw std::exception("Key doesn't exist");
	}
	return (*it).second;
}

template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
TData& HashMap<TKey, TData, HashFunctor, EqualityFunction>::At(const TKey& key)
{
	auto it = Find(key);
	if (it == end())
	{
		throw std::exception("Key doesn't exist");
	}
	return (*it).second;
}