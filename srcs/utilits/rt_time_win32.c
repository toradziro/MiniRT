#include "rt_time.h"
#include <windows.h>

u64 time_ms()
{
    LARGE_INTEGER perfomanceFrequency = {};
    QueryPerformanceFrequency(&perfomanceFrequency);
    LARGE_INTEGER perfomanceCounterEnd = {};
    QueryPerformanceCounter(&perfomanceCounterEnd);
    float timeSeconds = (float)(perfomanceCounterEnd.QuadPart) / (float)perfomanceFrequency.QuadPart;
    float timeMs      = timeSeconds * 1000;
    return timeMs;
}
