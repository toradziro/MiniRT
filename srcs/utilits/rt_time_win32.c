#include "rt_time.h"
#include <windows.h>
#include <stdbool.h>

u64 time_ms()
{
    static LARGE_INTEGER frequency = {};
    static LARGE_INTEGER startTime = {};
    static bool initialized = false;

    if (!initialized)
    {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        initialized = true;
    }

     LARGE_INTEGER currentTime;
     QueryPerformanceCounter(&currentTime);

     return ((currentTime.QuadPart - startTime.QuadPart) * 1000) / frequency.QuadPart;
}
