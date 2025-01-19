#pragma once
class MemoryTracker
{
private:
    static int allocCount;
public:
    static void Allocate() { allocCount++; }
    static void Deallocate() { allocCount--; }
    static int GetCount() { return allocCount; }
};

// In your classes:
class MyClass {
public:
    MyClass() { MemoryTracker::Allocate(); }
    ~MyClass() { MemoryTracker::Deallocate(); }

};

