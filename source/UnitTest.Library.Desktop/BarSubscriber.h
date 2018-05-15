#pragma once
#include "EventSubscriber.h"
#include "Event.h"
#include "World.h"

namespace FieaGameEngine {
	class BarSubscriber : public EventSubscriber
	{
	public:
		BarSubscriber(EventQueue& eq, GameTime& gameTime);
		~BarSubscriber();
		virtual void Notify(const EventPublisher& publisher) override;
		int mData;
		bool wasNotified;
		World* mWorld;
		EventQueue& mEq;
		GameTime mGameTime;
	};
}
