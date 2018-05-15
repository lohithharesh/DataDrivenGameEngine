#pragma once

#include <exception>
#include <chrono>

namespace FieaGameEngine
{
    class GameTime;

    class GameClock
    {
    public:
        GameClock();
		GameClock(const GameClock& rhs) = default;
		GameClock& operator=(const GameClock& rhs) = default;
		GameClock(GameClock&& rhs) = default;
		GameClock& operator=(GameClock&& rhs) = default;

		const std::chrono::high_resolution_clock::time_point& StartTime() const;
		const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		const std::chrono::high_resolution_clock::time_point& LastTime() const;

        void Reset();
        void UpdateGameTime(GameTime& gameTime);

    private:
        std::chrono::high_resolution_clock::time_point mStartTime;
		std::chrono::high_resolution_clock::time_point mCurrentTime;
		std::chrono::high_resolution_clock::time_point mLastTime;
    };
}
