#pragma once
#include "Vector.h"


template <typename T, typename IncrementFunctor = Incrementor>
Vector<T, IncrementFunctor>::Iterator::Iterator() : mOwner(nullptr)
{

}

template <typename T, typename IncrementFunctor = Incrementor>
Vector<T, IncrementFunctor>::Iterator::Iterator(uint32_t index, const Vector& owner) : mIndex(index), mOwner(&owner)
{

}

template<typename T, typename IncrementFunctor = Incrementor>
bool Vector<T, IncrementFunctor>::Iterator::operator==(const Iterator& rhs) const
{
	return (mOwner == rhs.mOwner && mIndex == rhs.mIndex);
}

template<typename T, typename IncrementFunctor = Incrementor>
bool Vector<T, IncrementFunctor>::Iterator::operator!=(const Iterator& rhs) const
{
	return !operator==(rhs);
}

template<typename T, typename IncrementFunctor = Incrementor>
T& Vector<T, IncrementFunctor>::Iterator::operator*()
{
	if (mOwner == nullptr || mIndex >= mOwner->Size())
	{
		throw std::exception("Iterator points to invalid data");
	}
	return const_cast<T&>(mOwner->operator[](mIndex));
}

template<typename T, typename IncrementFunctor = Incrementor>
const T& Vector<T, IncrementFunctor>::Iterator::operator*() const
{
	if (mOwner == nullptr || mIndex >= mOwner->Size())
	{
		throw std::exception("Iterator points to invalid data");
	}
	return mOwner->operator[](mIndex);
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator& Vector<T, IncrementFunctor>::Iterator::operator++()
{
	if (mOwner == nullptr)
	{
		throw std::exception("Invalid iterator");
	}
	if (mIndex >= mOwner->Size())
	{
		throw std::exception("Iterator out of bounds");
	}
	mIndex++;
	return *this;
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator Vector<T, IncrementFunctor>::Iterator::operator++(int)
{
	Iterator tempIterator = *this;
	operator++();
	return tempIterator;
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator& Vector<T, IncrementFunctor>::Iterator::operator--()
{
	if (mOwner == nullptr)
	{
		throw std::exception("invalid iterator");
	}
	if (mIndex > 0)
	{
		mIndex--;
	}
	return *this;
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator Vector<T, IncrementFunctor>::Iterator::operator--(int)
{
	Iterator tempIterator = *this;
	operator--();
	return tempIterator;
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator Vector<T, IncrementFunctor>::Iterator::operator+(uint32_t increment) const
{
	if (mOwner == nullptr)
	{
		throw std::exception("invalid iterator");
	}
	if (mIndex >= mOwner->Size())
	{
		throw std::exception("Invalid Iterator");
	}
	return Iterator(mIndex + increment, *mOwner);
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator Vector<T, IncrementFunctor>::Iterator::operator-(uint32_t decrement) const
{
	if (mOwner == nullptr)
	{
		throw std::exception("invalid iterator");
	}
	if (mIndex <= 0)
	{
		throw std::exception("Invalid Iterator");
	}
	return Iterator(mIndex - increment, *mOwner);
}

template<typename T, typename IncrementFunctor = Incrementor>
Vector<T, IncrementFunctor>::Vector(uint32_t capacity) : mSize(0), mCapacity(capacity), mData(nullptr)
{
	if (mCapacity > 0)
	{
		Reserve(mCapacity);
	}
}

template<typename T, typename IncrementFunctor = Incrementor>
Vector<T, IncrementFunctor>::Vector(const Vector& rhs) : Vector(rhs.mCapacity)
{
	mIncrementCapacity = rhs.mIncrementCapacity;
	for (T& value : rhs)
	{
		PushBack(value);
	}
}

template<typename T, typename IncrementFunctor = Incrementor>
Vector<T, IncrementFunctor>::Vector(Vector&& rhs) : mData(std::move(rhs.mData)), mCapacity(rhs.mCapacity), mSize(rhs.mSize), mIncrementCapacity(rhs.mIncrementCapacity)
{
	rhs.mData = nullptr;
	rhs.mSize = 0;
	rhs.mCapacity = 0;
}

template<typename T, typename IncrementFunctor = Incrementor>
Vector<T, IncrementFunctor>& Vector<T, IncrementFunctor>::operator=(const Vector& rhs)
{
	if (this != &rhs)
	{
		Clear();
		ShrinkToFit();
		Reserve(rhs.mCapacity);
		mIncrementCapacity = rhs.mIncrementCapacity;
		for (T& value : rhs)
		{
			PushBack(value);
		}
	}
	return *this;
}

template<typename T, typename IncrementFunctor = Incrementor>
Vector<T, IncrementFunctor>& Vector<T, IncrementFunctor>::operator=(Vector&& rhs)
{
	if (this != &rhs)
	{
		Clear();
		ShrinkToFit();
		mData = std::move(rhs.mData);
		mCapacity = rhs.mCapacity;
		mSize = rhs.mSize;
		mIncrementCapacity = rhs.mIncrementCapacity;
		rhs.mSize = 0;
		rhs.mCapacity = 0;
		rhs.mData = nullptr;
	}
	return *this;
}

template<typename T, typename IncrementFunctor = Incrementor>
T& Vector<T, IncrementFunctor>::operator[](const uint32_t& index)
{
	if (index >= mSize)
	{
		throw std::exception("Index is out of bounds");
	}
	return mData[index];
}

template<typename T, typename IncrementFunctor = Incrementor>
const T& Vector<T, IncrementFunctor>::operator[](const uint32_t& index) const
{
	if (index >= mSize)
	{
		throw std::exception("Index is out of bounds");
	}
	return const_cast<T&>(mData[index]);
}

template<typename T, typename IncrementFunctor = Incrementor>
T& Vector<T, IncrementFunctor>::Front()
{
	if (mSize == 0)
	{
		throw std::exception("Empty Vector");
	}
	return mData[0];
}

template<typename T, typename IncrementFunctor = Incrementor>
const T& Vector<T, IncrementFunctor>::Front() const
{
	if (mSize == 0)
	{
		throw std::exception("Empty Vector");
	}
	return const_cast<T&>(mData[0]);
}

template<typename T, typename IncrementFunctor = Incrementor>
T& Vector<T, IncrementFunctor>::Back()
{
	if (mSize == 0)
	{
		throw std::exception("Empty Vector");
	}
	return mData[mSize - 1];
}

template<typename T, typename IncrementFunctor = Incrementor>
const T& Vector<T, IncrementFunctor>::Back() const
{
	if (mSize == 0)
	{
		throw std::exception("Empty Vector");
	}
	return const_cast<T&>(mData[mSize - 1]);
}

template<typename T, typename IncrementFunctor = Incrementor>
void Vector<T, IncrementFunctor>::ShrinkToFit()
{
	mCapacity = mSize;
	mData = static_cast<T*>(realloc(mData, (mSize) * sizeof(T)));
}

template<typename T, typename IncrementFunctor = Incrementor>
bool Vector<T, IncrementFunctor>::Reserve(const uint32_t& capacity)
{
	if (capacity < mSize)
	{
		return false;
	}
	mCapacity = capacity;
	mData = static_cast<T*>(realloc(mData, (mCapacity) * sizeof(T)));
	return (mData != nullptr);
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator Vector<T, IncrementFunctor>::PushBack(const T& value)
{
	if (mSize == mCapacity)
	{
		Reserve(std::_Max_value(mCapacity + 1 , mIncrementCapacity(mSize, mCapacity)));
	}
	new(mData + mSize++) T(value);
	return Iterator(mSize - 1, *this);
}

template<typename T, typename IncrementFunctor = Incrementor>
void Vector<T, IncrementFunctor>::PopBack()
{
	if (mSize > 0)
	{
		mData[--mSize].~T();
	}
}

template<typename T, typename IncrementFunctor = Incrementor>
uint32_t Vector<T, IncrementFunctor>::Capacity() const
{
	return mCapacity;
}

template<typename T, typename IncrementFunctor = Incrementor>
uint32_t Vector<T, IncrementFunctor>::Size() const
{
	return mSize;
}

template<typename T, typename IncrementFunctor = Incrementor>
bool Vector<T, IncrementFunctor>::IsEmpty() const
{
	return (mSize == 0);
}

template<typename T, typename IncrementFunctor = Incrementor>
void Vector<T, IncrementFunctor>::Clear()
{
	for (uint32_t i = 0; i < mSize; i++)
	{
		mData[i].~T();
	}
	mSize = 0;
	mCapacity = 0;
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator Vector<T, IncrementFunctor>::begin() const
{
	return Iterator(0, *this);
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator Vector<T, IncrementFunctor>::end() const
{
	return Iterator(mSize, *this);
}

template<typename T, typename IncrementFunctor = Incrementor>
typename Vector<T, IncrementFunctor>::Iterator Vector<T, IncrementFunctor>::Find(const T& value) const
{
	Iterator it;
	for (it = begin(); it != end(); ++it)
	{
		if (*it == value)
		{
			break;
		}
	}
	return it;
}

template<typename T, typename IncrementFunctor = Incrementor>
bool Vector<T, IncrementFunctor>::Remove(const Iterator& it)
{
	if (it.mOwner != this)
	{
		throw std::exception("invalid iterator");
	}
	if (it == end())
	{
		return false;
	}
	if (it.mIndex == mSize - 1)
	{
		PopBack();
		return true;
	}
	mData[it.mIndex].~T();
	memmove_s(mData + it.mIndex, sizeof(T) * (mSize - it.mIndex - 1),  mData + it.mIndex + 1, sizeof(T) * (mSize - it.mIndex - 1));
	mSize--;
	return true;
}

template<typename T, typename IncrementFunctor = Incrementor>
bool Vector<T, IncrementFunctor>::Remove(const T& value)
{
	return Remove(Find(value));
}

template<typename T, typename IncrementFunctor = Incrementor>
bool Vector<T, IncrementFunctor>::Remove(const Iterator& first,const Iterator& last)
{
	if (first.mOwner != this || last.mOwner != this)
	{
		throw std::exception("invalid iterator");
	}
	if (first == end() || last == end())
	{
		return false;
	}
	if (first.mIndex > last.mIndex)
	{
		return false;
	}
	if (first == begin() && last.mIndex == mSize - 1)
	{
		Clear();
		return true;
	}
	for (uint32_t i = first.mIndex; i <= last.mIndex; i++)
	{
		mData[i].~T();
	}
	memmove_s(mData + first.mIndex, sizeof(T) * (mSize - last.mIndex - 1), mData + last.mIndex + 1, sizeof(T) * (mSize - last.mIndex - 1));
	mSize = mSize - (last.mIndex - first.mIndex) - 1;
	return true;
}

template<typename T, typename IncrementFunctor = Incrementor>
T& Vector<T, IncrementFunctor>::At(uint32_t index)
{
	if (index >= size)
	{
		throw std::exception("Invalid index");
	}
	return mData[index];
}

template<typename T, typename IncrementFunctor = Incrementor>
const T& Vector<T, IncrementFunctor>::At(uint32_t index) const
{
	if (index >= size)
	{
		throw std::exception("Invalid index");
	}
	return const_cast<T&>(mData[index]);
}

template<typename T, typename IncrementFunctor = Incrementor>
Vector<T, IncrementFunctor>::~Vector()
{
	Clear();
	free(mData);
	mData = nullptr;
}

template<typename T, typename IncrementFunctor = Incrementor>
void Vector<T, IncrementFunctor>::Resize(uint32_t size)
{
	if (size < mSize)
	{
		for (--mSize; mSize >= size; mSize--)
		{
			PopBack();
		}
	}
	mCapacity = 0;
	Reserve(size);
	for (; mSize < size; mSize++)
	{
		new(&mData[mSize])T();
	}
	mSize = mCapacity = size;
}
