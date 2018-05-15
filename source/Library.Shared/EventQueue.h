#pragma once
#include "EventPublisher.h"
#include "GameTime.h"
#include <queue>
namespace FieaGameEngine {

	//!EventQueue class
	class EventQueue
	{
	public:
		//!Default constructor
		EventQueue() = default;
		//!Copy and move constructors
		EventQueue(const EventQueue& rhs) = default;
		EventQueue(EventQueue&& rhs) = default;
		EventQueue& operator=(const EventQueue& rhs) = default;
		EventQueue& operator=(EventQueue&& rhs) = default;
		//!Enqueue
		/*!
			Enqueue function that is used to add an event to the evetn queue.
			\param event, a pointer to the event publisher
			\param gametime, a reference to the gametime object
			\delayTime, Delay for the event before it expires
		*/
		void Enqueue(std::shared_ptr<EventPublisher> event, const GameTime& gameTime, const std::chrono::milliseconds& delayTime = std::chrono::milliseconds());
		//!Send function
		/*!
			Send the event irrespective of the delay.
			\param event, the event to send.
		*/
		void Send(std::shared_ptr<EventPublisher> event);
		//!Update
		/*!
			update function that takes in teh gametime.
		*/
		void Update(const GameTime& gameTime);
		//!Clear function that clears the queue
		void Clear();
		//!IsEmpty returns true if the queue is empty
		bool IsEmpty() const;
		//!Size function. Returns the current size of the queue. 
		uint32_t Size() const;
		//!Destructor
		~EventQueue() = default;
	private:
		std::deque<std::shared_ptr<EventPublisher>> mEventQueue;
	};
}

