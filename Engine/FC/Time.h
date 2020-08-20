#pragma once

#include <chrono>

namespace Time {
	using Point = std::chrono::high_resolution_clock::time_point;
	using Duration = std::chrono::duration<long, std::ratio<1, 1000000>>;
	 
	inline Point Now() {
		return Point::clock::now();
	}
	
	inline Duration Since(const Point& point) {
		return std::chrono::duration_cast<Duration>(Point::clock::now() - point);
	}
}
