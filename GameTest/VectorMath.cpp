#include "stdafx.h"
#include "VectorMath.h"

Vec2 VectorMath::normalize(const Vec2 v)
{
	float mag = sqrt(v.x * v.x + v.y * v.y);

	if (mag != 0)
	{
		return Vec2(v.x / mag, v.y / mag);
	}
	else {

		std::cerr << "Error: Cannot normalize a zero vector" << std::endl;
		return Vec2();
	}

}

float VectorMath::mag(const Vec2 v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);

}

float VectorMath::dot(const Vec2 a, const Vec2 b)
{

	return (a.x * b.x + a.y * b.y);
}
