#pragma once
#include "EventSubscriber.h"
#include "Event.h"

namespace FieaGameEngine {
	class FooSubscriber : public EventSubscriber
	{
	public:
		FooSubscriber();
		~FooSubscriber();
		virtual void Notify(const EventPublisher& publisher) override;
		int mData;
		bool wasNotified;
	};
}
