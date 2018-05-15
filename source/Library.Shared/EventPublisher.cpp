#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"


using namespace FieaGameEngine;
RTTI_DEFINITIONS(EventPublisher);

EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscribers) : mSubscribers(subscribers)
{

}

void EventPublisher::setTime(const std::chrono::high_resolution_clock::time_point& currentTime, const std::chrono::milliseconds& delay)
{
	mEnqueuedTime = currentTime;
	mDelayTime = delay;
}

const std::chrono::high_resolution_clock::time_point& EventPublisher::TimeEnqueued()
{
	return mEnqueuedTime;
}


const std::chrono::milliseconds& EventPublisher::Delay()
{
	return mDelayTime;
}
bool EventPublisher::IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime)
{
	if ((mEnqueuedTime + mDelayTime) <= currentTime)
	{
		return true;
	}
	return false;
}
void EventPublisher::Deliver() const 
{
	for (auto subscriber : mSubscribers)
	{
		subscriber->Notify(*this);
	}
}


