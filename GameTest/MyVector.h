#pragma once
#include <iostream>

/// <summary>
/// Custom Simple Vec2 Class
/// </summary>
struct Vec2 
{
	float  x, y;
	

	void set(float x_, float y_) {
		x = x_; y = y_;
	}

	/// For convenience
	inline  Vec2() {
		set(0.0f, 0.0f);
	}

	/// A copy constructor
	inline Vec2(const Vec2& v) {
		set(v.x, v.y);
	}
	inline Vec2(float x_, float y_) {
		x = x_; y = y_;
	}


	inline Vec2& operator = (const Vec2& v) {
		set(v.x, v.y);
		return *this;
	}
	

	inline Vec2 operator*(float s)const 
	{
		return Vec2(x * s, y * s);
	}

	inline Vec2 operator+(Vec2& v) const 
	{
		return Vec2(x + v.x, y + v.y);
	}

	inline Vec2 operator+(const Vec2& v) const
	{
		return Vec2(x + v.x, y + v.y);
	}
	inline Vec2 operator-(Vec2& v) const
	{
		return Vec2(x - v.x, y - v.y);
	}
	inline Vec2 operator-(const Vec2& v) const
	{
		return Vec2(x - v.x, y - v.y);
	}
	inline Vec2 operator/(float s) const 
	{
		return Vec2(x / s, y / s);
	}
	

	inline void print() 
	{
		std::cout << "X: " << x << "Y: " << y << '\n';
	}



};


class MyVector
{
	float x, y;


};

