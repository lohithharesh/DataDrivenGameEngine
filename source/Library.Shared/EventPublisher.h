#pragma once
#include "RTTI.h"
#include "Vector.h"
#include <chrono>
#include <memory>
namespace FieaGameEngine {

	class EventSubscriber;
	//!Event publisher class
	/*!
		Base class for the event class
	*/
	class EventPublisher : public RTTI 
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)
	public:
		//!Set Time
		/*!
			Takes in the current time and an optional delay time and sets it for the current event
			\param, current time a timepoint
			\param delay, a duration
		*/
		void setTime(const std::chrono::high_resolution_clock::time_point& currentTime,const std::chrono::milliseconds& delay = std::chrono::milliseconds()); 
		//!TimeEnqueued
		/*!
			returns the time it was enqueued
			\return the timepoint when  it was enqueued
		*/
		const std::chrono::high_resolution_clock::time_point& TimeEnqueued();
		//!TimeEnqueued
		/*!
			returns the delay time
			\return the duration for delays
		*/
		const std::chrono::milliseconds& Delay();
		//!IsExpired
		/*!
			returns a bool that tells if the event has expired or not.
			\param, current time, a timepoint
			\return, bool true if the event has expired
		*/
		bool IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime);
		//!Deliver method which delivers the payload to each of its subscribers
		void Deliver() const;
		//!Copy and move constructors
		EventPublisher(const EventPublisher& rhs) = default;
		EventPublisher(EventPublisher&& rhs) = default;
		EventPublisher& operator=(const EventPublisher& rhs) = default;
		EventPublisher& operator=(EventPublisher&& rhs) = default;
		virtual ~EventPublisher() = default;
	protected:
		EventPublisher(Vector<EventSubscriber*>& subscribers);
		std::chrono::high_resolution_clock::time_point mEnqueuedTime;
		std::chrono::milliseconds mDelayTime;
	private:
		Vector<EventSubscriber*>& mSubscribers;
	};
}

