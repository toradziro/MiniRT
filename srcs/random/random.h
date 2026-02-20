#pragma once
#include "../includes/my_types.h"

typedef struct
{
    u32 state;
} t_rng;

_Thread_local t_rng thread_local_rng = {0};
;

u32 xorshift32(t_rng* rng)
{
    rng->state ^= rng->state << 13;
    rng->state ^= rng->state >> 17;
    rng->state ^= rng->state << 5;
    return rng->state;
}

float rng_float(t_rng* rng) { return (float)(xorshift32(rng)) / (float)0xFFFFFFFF; }
