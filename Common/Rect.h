#pragma once

#include <GLM.h>

struct Rect {
	Rect(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f)
		: x(x), y(y), w(w), h(h) {}
		
	Rect(Vec2 position, float w, float h)
		: x(position.x), y(position.y), w(w), h(h) {}

	Rect(float x, float y, Vec2 size)
		: x(x), y(y), w(size.x), h(size.y) {}
		
	Rect(Vec2 position, Vec2 size)
	: x(position.x), y(position.y), w(size.x), h(size.y) {}

	inline bool Contains(const Vec2& point) {
		return point.x > x && point.x < x + w && point.y > y && point.y < y + h;
	}

	float x, y;
	float w, h;
};
