#pragma once
#include "stdio.h"
#include "misc.h"

struct Tuple {
    float x;
    float y;
    float z;
    float w;
};

void debug_print_tuple(struct Tuple tuple)
{
    printf("x: %f y: %f z: %f w: %f\n", tuple.x, tuple.y, tuple.z, tuple.w);
}

// Functions for creating new tuples, points, and vectors
struct Tuple new_tuple(float x, float y, float z, float w)
{
    struct Tuple tuple;
    tuple.x = x;
    tuple.y = y;
    tuple.z = z;
    tuple.w = w;

    return tuple;
}

struct Tuple new_point_tuple(float x, float y, float z)
{
    struct Tuple point;
    point = new_tuple(x, y, z, 1.0);

    return point;
}

int tuple_is_point(struct Tuple point)
{
    if (is_equal_float(point.w, 1.0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

struct Tuple new_vector_tuple(float x, float y, float z)
{
    struct Tuple vector;
    vector = new_tuple(x, y, z, 0.0);

    return vector;
}

int tuple_is_vector(struct Tuple vector)
{
    if (is_equal_float(vector.w, 0.0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Operations on tuples
int is_equal_tuple(struct Tuple a, struct Tuple b)
{
    if (!is_equal_float(a.x, b.x)) { return 0; }
    if (!is_equal_float(a.y, b.y)) { return 0; }
    if (!is_equal_float(a.z, b.z)) { return 0; }
    if (!is_equal_float(a.w, b.w)) { return 0; }

    return 1;
}

struct Tuple add_tuples(struct Tuple a, struct Tuple b)
{
    struct Tuple tuple;
    tuple = new_tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);

    return tuple;
}

struct Tuple subtract_tuples(struct Tuple a, struct Tuple b)
{
    struct Tuple tuple;
    tuple = new_tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);

    return tuple;
}

struct Tuple negate_tuple(struct Tuple a)
{
    struct Tuple tuple;
    tuple = new_tuple(0.0 - a.x, 0.0 - a.y, 0.0 - a.z, 0.0 - a.w);

    return tuple;
}

struct Tuple mult_tuple_scalar(struct Tuple a, float scalar)
{
    struct Tuple tuple;
    tuple = new_tuple(a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar);

    return tuple;
}

struct Tuple div_tuple_scalar(struct Tuple a, float scalar)
{
    struct Tuple tuple;
    tuple = new_tuple(a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar);

    return tuple;
}

float tuple_magnitude(struct Tuple a)
{
    float magnitude;

    magnitude = sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z) + (a.w * a.w));

    return magnitude;
}

struct Tuple normalize_tuple(struct Tuple a)
{
    float magnitude = tuple_magnitude(a);

    struct Tuple tuple = new_tuple((a.x / magnitude), (a.y / magnitude), (a.z / magnitude), (a.w / magnitude));

    return tuple;
}

float dot_product(struct Tuple a, struct Tuple b)
{
    float dot_product = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);

    return dot_product;
}

struct Tuple cross_product(struct Tuple a, struct Tuple b)
{
    float x = (a.y * b.z) - (a.z * b.y);
    float y = (a.z * b.x) - (a.x * b.z);
    float z = (a.x * b.y) - (a.y * b.x);

    struct Tuple tuple = new_vector_tuple(x, y, z);

    return tuple;
}