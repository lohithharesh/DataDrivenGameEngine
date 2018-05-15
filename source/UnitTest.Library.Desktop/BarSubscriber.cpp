#include "pch.h"
#include "BarSubscriber.h"
#include "Event.h"
#include "GameTime.h"
#include "EventQueue.h"

using namespace FieaGameEngine;

BarSubscriber::BarSubscriber(EventQueue& eq, GameTime& gameTime) : wasNotified(false), mData(0), mEq(eq), mGameTime(gameTime)
{
	Event<int>::Subscribe(*this);
}

void BarSubscriber::Notify(const EventPublisher& publisher)
{
	Event<int>* e = publisher.As<Event<int>>();
	if (e != nullptr)
	{
		wasNotified = true;
		mData = e->Message();
		std::shared_ptr<Event<int>> e1 = std::make_shared<Event<int>>(10);
		mEq.Enqueue(e1, mGameTime, std::chrono::milliseconds(0));
		Event<int>::Unsubscribe(*this);
	}
	
}

BarSubscriber::~BarSubscriber()
{
	Event<int>::Unsubscribe(*this);
}