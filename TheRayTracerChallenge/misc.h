#pragma once
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.00001

int is_equal_float(float a, float b)
{
    if (fabsf(a - b) < EPSILON)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
