#pragma once

#include <chrono>

// The extracted planner only needs a high-resolution monotonic clock. The
// original client supplied this through its Windows PCH; keep the standalone
// build independent of IL2CPP and Windows headers.
struct LARGE_INTEGER {
    long long QuadPart;
};

inline void QueryPerformanceFrequency(LARGE_INTEGER* value)
{
    value->QuadPart = 1000000000LL;
}

inline void QueryPerformanceCounter(LARGE_INTEGER* value)
{
    value->QuadPart = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}
