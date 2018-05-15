#pragma once
#include "AbstractFactory.h"

template <typename T>
typename AbstractFactory<T>::HashMapType AbstractFactory<T>::mFactoryMap(20);

template<typename T>
AbstractFactory<T>* AbstractFactory<T>::Find(std::string className)
{
	auto it = mFactoryMap.Find(className);
	if (it != mFactoryMap.end())
	{
		return it->second;
	}
	return nullptr;
}

template<typename T>
void AbstractFactory<T>::Add(AbstractFactory& rhs)
{
	mFactoryMap.Insert(std::make_pair(rhs.ClassName(), &rhs));
}

template<typename T>
void AbstractFactory<T>::Remove(AbstractFactory& rhs)
{
	mFactoryMap.Remove(rhs.ClassName());
}

template<typename T>
template<typename... Args>
T* AbstractFactory<T>::Create(std::string className, Args... args)
{
	AbstractFactory* foundFactory = Find(className);
	if (foundFactory != nullptr)
	{
		return foundFactory->Create(std::forward<Args>(args)...);
	}
	return nullptr;
}
