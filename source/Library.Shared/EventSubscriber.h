#pragma once
#include "EventPublisher.h"

namespace FieaGameEngine {
	//!Event Subscriber interface which has to be implemented by the subscribers
	class EventSubscriber
	{
	public:
		EventSubscriber() = default;
		//!notfiy function
		/*!
			virtual function that is implemented by the subscribers. Delivers a reference of the event to the subscribers.
			\param publisher, a const reference to the publisher
		*/
		virtual void Notify(const EventPublisher& publisher) = 0;
		~EventSubscriber() = default;
	};
}

