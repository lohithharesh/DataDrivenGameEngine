#include "pch.h"
#include "FooSubscriber.h"
#include "Foo.h"
using namespace FieaGameEngine;

FooSubscriber::FooSubscriber() : wasNotified(false), mData(0)
{
	Event<Foo>::Subscribe(*this);
}

void FooSubscriber::Notify(const EventPublisher& publisher)
{
	publisher;
	Event<Foo>* e = publisher.As<Event<Foo>>();
	if (e != nullptr)
	{
		wasNotified = true;
		mData = e->Message().Data();
	}
}

FooSubscriber::~FooSubscriber()
{
	Event<Foo>::Unsubscribe(*this);
}