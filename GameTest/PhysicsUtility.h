#pragma once
#include "MyVector.h"
/// <summary>
/// I need a way to Convert from Physics coordiate to pixel Coordinate. This class will be mainly
/// in charge of it.
/// </summary>
class PhysicsUtility
{

public:
    // Just gonna try making a pixel per meter to 100 as a test as it seems to be standard choice
    static constexpr float PIXELS_PER_METER = 100.0f; 

    // Convert physics space (meters) to pixel space
    static float ToPixels(float meters) {
        return meters * PIXELS_PER_METER;
    }

    static Vec2 ToPixels(const Vec2& metersVec) {
        return Vec2(ToPixels(metersVec.x), ToPixels(metersVec.y));
    }

    // Convert pixel space to physics space (meters)
    static float ToMeters(float pixels) {
        return pixels / PIXELS_PER_METER;
    }

    static Vec2 ToMeters(const Vec2& pixelsVec) {
        return Vec2(ToMeters(pixelsVec.x), ToMeters(pixelsVec.y));
    }
};

