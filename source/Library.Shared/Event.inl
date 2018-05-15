#pragma once
#include "Event.h"

template <typename T>
RTTI_DEFINITIONS(Event<T>)

template<typename T>
Vector<EventSubscriber*> Event<T>::mListOfSubscribers(10);

template <typename T>
Event<T>::Event(const T& message) : EventPublisher(mListOfSubscribers), mMessage(message)
{

}

template <typename T>
void Event<T>::Subscribe(EventSubscriber& subscriber)
{
	if (mListOfSubscribers.Find(&subscriber) == mListOfSubscribers.end())
	{
		mListOfSubscribers.PushBack(&subscriber);
	}
}

template <typename T>
void Event<T>::Unsubscribe(EventSubscriber& subscriber)
{
	mListOfSubscribers.Remove(&subscriber);
}

template <typename T>
void Event<T>::UnsubscribeAll()
{
	mListOfSubscribers.Clear();
}

template <typename T>
const T& Event<T>::Message() const
{
	return mMessage;

}