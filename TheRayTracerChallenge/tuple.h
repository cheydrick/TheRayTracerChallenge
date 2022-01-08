#pragma once
#include "stdio.h"
#include "misc.h"

struct Tuple {
    float x;
    float y;
    float z;
    float w;
};

void debug_print_tuple(struct Tuple *tuple)
{
    printf("x: %f y: %f z: %f w: %f\n", tuple->x, tuple->y, tuple->z, tuple->w);
}

// Functions for creating new tuples, points, and vectors
int new_tuple(struct Tuple *tuple, float x, float y, float z, float w)
{
    tuple->x = x;
    tuple->y = y;
    tuple->z = z;
    tuple->w = w;

    return 1;
}

int new_point_tuple(struct Tuple *tuple, float x, float y, float z)
{
    new_tuple(tuple, x, y, z, 1.0);

    return 1;
}

int tuple_is_point(struct Tuple *point)
{
    if (is_equal_float(point->w, 1.0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int new_vector_tuple(struct Tuple *tuple, float x, float y, float z)
{
    new_tuple(tuple, x, y, z, 0.0);

    return 1;
}

int tuple_is_vector(struct Tuple *vector)
{
    if (is_equal_float(vector->w, 0.0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Operations on tuples
int is_equal_tuple(struct Tuple *a, struct Tuple *b)
{
    if (!is_equal_float(a->x, b->x)) { return 0; }
    if (!is_equal_float(a->y, b->y)) { return 0; }
    if (!is_equal_float(a->z, b->z)) { return 0; }
    if (!is_equal_float(a->w, b->w)) { return 0; }

    return 1;
}

int add_tuples(struct Tuple *sum, struct Tuple *a, struct Tuple *b)
{
    new_tuple(sum, a->x + b->x, a->y + b->y, a->z + b->z, a->w + b->w);

    return 1;
}

int subtract_tuples(struct Tuple *difference, struct Tuple *a, struct Tuple *b)
{
    new_tuple(difference, a->x - b->x, a->y - b->y, a->z - b->z, a->w - b->w);

    return 1;
}

int negate_tuple(struct Tuple *neg, struct Tuple *a)
{
    new_tuple(neg, 0.0 - a->x, 0.0 - a->y, 0.0 - a->z, 0.0 - a->w);

    return 1;
}

int mult_tuple_scalar(struct Tuple *product, struct Tuple *a, float scalar)
{
    new_tuple(product, a->x * scalar, a->y * scalar, a->z * scalar, a->w * scalar);

    return 1;
}

int div_tuple_scalar(struct Tuple *quotient, struct Tuple *a, float scalar)
{
    new_tuple(quotient, a->x / scalar, a->y / scalar, a->z / scalar, a->w / scalar);

    return 1;
}

float tuple_magnitude(struct Tuple *a)
{
    float magnitude;

    magnitude = sqrtf((a->x * a->x) + (a->y * a->y) + (a->z * a->z) + (a->w * a->w));

    return magnitude;
}

int normalize_tuple(struct Tuple *norm, struct Tuple *a)
{
    float magnitude = tuple_magnitude(a);

    new_tuple(norm, (a->x / magnitude), (a->y / magnitude), (a->z / magnitude), (a->w / magnitude));

    return 1;
}

float dot_product(struct Tuple *a, struct Tuple *b)
{
    float dot_product = (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);

    return dot_product;
}

int cross_product(struct Tuple *product, struct Tuple *a, struct Tuple *b)
{
    float x = (a->y * b->z) - (a->z * b->y);
    float y = (a->z * b->x) - (a->x * b->z);
    float z = (a->x * b->y) - (a->y * b->x);

    new_vector_tuple(product, x, y, z);

    return 1;
}