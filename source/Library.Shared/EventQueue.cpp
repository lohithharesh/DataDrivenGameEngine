#include "pch.h"
#include "EventQueue.h"
#include "Event.h"
#include <cassert>

using namespace FieaGameEngine;

void EventQueue::Enqueue(std::shared_ptr<EventPublisher> event, const GameTime& gameTime, const std::chrono::milliseconds& delayTime)
{
	assert(event != nullptr);
	event->setTime(gameTime.CurrentTime(), delayTime);
	mEventQueue.push_back(event);
}
void EventQueue::Send(std::shared_ptr<EventPublisher> event)
{
	auto it = std::find(mEventQueue.begin(), mEventQueue.end(), event);
	if (it != mEventQueue.end())
	{
		(*it)->Deliver();
		mEventQueue.erase(it);
	}
}

void EventQueue::Update(const GameTime& gameTime)
{
	auto it = std::partition(mEventQueue.begin(), mEventQueue.end(), [gameTime](std::shared_ptr<EventPublisher>& event) {return !event->IsExpired(gameTime.CurrentTime()); });
	for (auto start = it ; start != mEventQueue.end(); ++start)
	{
		(*start)->Deliver();
	}
	mEventQueue.erase(it, mEventQueue.end());
}

void EventQueue::Clear()
{
	mEventQueue.clear();
}

bool EventQueue::IsEmpty() const
{
	return mEventQueue.empty();
}

uint32_t EventQueue::Size() const
{
	return static_cast<uint32_t>(mEventQueue.size());
}