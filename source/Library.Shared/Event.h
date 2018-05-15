#pragma once
#include "EventPublisher.h"

namespace FieaGameEngine {

	//!Event class that holds the payload
	template <typename T>
	class Event : public EventPublisher
	{
		//RTTI declarations
		RTTI_DECLARATIONS(Event<T>, EventPublisher)
	public:
		//!parameterized constructor that takes in the message
		/*!
			\param message, a const T reference
		*/
		Event(const T& message);
		//!move and copy constructors
		Event(const Event& rhs) = default;
		Event(Event&& rhs) = default;
		Event& operator=(const Event& rhs) = default;
		Event& operator=(Event&& rhs) = default;
		//!Subscribe function
		/*!
			takes in a subscriber and adds it to the list of subscribers
			\param a reference to the subscriber to be added
		*/
		static void Subscribe(EventSubscriber& subscriber);
		//!Unsubscribe function
		/*!
			takes in a subscriber and removes it from the list of subscribers
			\param a reference to the subscriber to be removed
		*/
		static void Unsubscribe(EventSubscriber& subscriber);
		//!unsubscribe all. Removes all the subscribers
		static void UnsubscribeAll();
		//!Returns the message
		const T& Message() const;
		virtual ~Event() = default;
	private:
		T mMessage;
		static Vector<EventSubscriber*> mListOfSubscribers;
	};

#include "Event.inl"
}

