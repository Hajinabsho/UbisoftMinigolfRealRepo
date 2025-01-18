#pragma once
#include "MyVector.h"
#include <cmath>

class VectorMath
{
public:
	static Vec2 normalize(const Vec2 v);
	static float mag(const Vec2 v);
	static float dot(const Vec2 a, const Vec2 b);
};

