#pragma once
#include <stdio.h>
#include "tuple.h"
#include "misc.h"

// All tests return 1 for success, <0 for failure.
// <0 failure values should be unique within each function
// to help trace problems.

// Chapter One Tests

int test_is_equal_tuple()
{
    struct Tuple tuple_a = new_tuple(4.3, -4.2, 3.1, 1.0);
    struct Tuple tuple_b = new_tuple(4.3, -4.2, 3.1, 1.0);
    struct Tuple tuple_c = new_tuple(1.1, -2.2, 3.1, 1.0);

    if (!is_equal_tuple(tuple_a, tuple_b)) { return -1; }
    if (is_equal_tuple(tuple_a, tuple_c)) { return -2; }

    return 1;
}

int test_new_tuple_is_point()
{
    struct Tuple tuple;
    tuple = new_tuple(4.3, -4.2, 3.1, 1.0);
    if (!is_equal_float(tuple.x, 4.3)) { return -1; }
    if (!is_equal_float(tuple.y, -4.2)) { return -2; }
    if (!is_equal_float(tuple.z, 3.1)) { return -3; }
    if (!is_equal_float(tuple.w, 1.0)) { return -4; }
    if (!tuple_is_point(tuple)) { return -5; }
    if (tuple_is_vector(tuple)) { return -6; }

    return 1;
}

int test_new_tuple_is_vector()
{
    struct Tuple tuple;
    tuple = new_tuple(4.3, -4.2, 3.1, 0.0);
    if (!is_equal_float(tuple.x, 4.3)) { return -1; }
    if (!is_equal_float(tuple.y, -4.2)) { return -2; }
    if (!is_equal_float(tuple.z, 3.1)) { return -3; }
    if (!is_equal_float(tuple.w, 0.0)) { return -4; }
    if (tuple_is_point(tuple)) { return -5; }
    if (!tuple_is_vector(tuple)) { return -6; }

    return 1;
}

int test_new_point_tuple()
{
    struct Tuple point_tuple;
    point_tuple = new_point_tuple(4.3, -4.2, 3.1);

    if (!is_equal_float(point_tuple.x, 4.3)) { return -1; }
    if (!is_equal_float(point_tuple.y, -4.2)) { return -2; }
    if (!is_equal_float(point_tuple.z, 3.1)) { return -3; }
    if (!is_equal_float(point_tuple.w, 1.0)) { return -4; }

    return 1;
}

int test_new_vector_tuple()
{
    struct Tuple point_tuple;
    point_tuple = new_vector_tuple(4.3, -4.2, 3.1);

    if (!is_equal_float(point_tuple.x, 4.3)) { return -1; }
    if (!is_equal_float(point_tuple.y, -4.2)) { return -2; }
    if (!is_equal_float(point_tuple.z, 3.1)) { return -3; }
    if (!is_equal_float(point_tuple.w, 0.0)) { return -4; }

    return 1;
}

int test_add_tuples()
{
    struct Tuple a = new_tuple(3, -2, 5, 1);
    struct Tuple b = new_tuple(-2, 3, 1, 0);
    struct Tuple tuple = add_tuples(a, b);

    if (!is_equal_float(tuple.x, 1)) { return -1; }
    if (!is_equal_float(tuple.y, 1)) { return -2; }
    if (!is_equal_float(tuple.z, 6)) { return -3; }
    if (!is_equal_float(tuple.w, 1)) { return -4; }

    return 1;
}

int test_subtract_points()
{
    struct Tuple a = new_point_tuple(3, 2, 1);
    struct Tuple b = new_point_tuple(5, 6, 7);
    struct Tuple tuple = subtract_tuples(a, b);

    if (!is_equal_float(tuple.x, -2)) { return -1; }
    if (!is_equal_float(tuple.y, -4)) { return -2; }
    if (!is_equal_float(tuple.z, -6)) { return -3; }
    if (tuple_is_point(tuple)) { return -4; }

    return 1;
}

int test_subtract_vector_from_point()
{
    struct Tuple a = new_point_tuple(3, 2, 1);
    struct Tuple b = new_vector_tuple(5, 6, 7);
    struct Tuple tuple = subtract_tuples(a, b);

    if (!is_equal_float(tuple.x, -2)) { return -1; }
    if (!is_equal_float(tuple.y, -4)) { return -2; }
    if (!is_equal_float(tuple.z, -6)) { return -3; }
    if (tuple_is_vector(tuple)) { return -4; }

    return 1;
}

int test_subtract_vectors()
{
    struct Tuple a = new_vector_tuple(3, 2, 1);
    struct Tuple b = new_vector_tuple(5, 6, 7);
    struct Tuple tuple = subtract_tuples(a, b);

    if (!is_equal_float(tuple.x, -2)) { return -1; }
    if (!is_equal_float(tuple.y, -4)) { return -2; }
    if (!is_equal_float(tuple.z, -6)) { return -3; }
    if (tuple_is_point(tuple)) { return -4; }

    return 1;
}

int test_subtract_vector_from_zero_vector()
{
    struct Tuple a = new_vector_tuple(0, 0, 0);
    struct Tuple b = new_vector_tuple(1, -2, 3);
    struct Tuple tuple = subtract_tuples(a, b);

    if (!is_equal_float(tuple.x, -1)) { return -1; }
    if (!is_equal_float(tuple.y, 2)) { return -2; }
    if (!is_equal_float(tuple.z, -3)) { return -3; }

    return 1;
}

int test_negate_tuple()
{
    struct Tuple a = new_tuple(1, -2, 3, -4);
    struct Tuple tuple = negate_tuple(a);

    if (!is_equal_float(tuple.x, -1)) { return -1; }
    if (!is_equal_float(tuple.y, 2)) { return -2; }
    if (!is_equal_float(tuple.z, -3)) { return -3; }
    if (!is_equal_float(tuple.w, 4)) { return -4; }

    return 1;
}

int test_mult_tuple_scalar()
{
    struct Tuple a = new_tuple(1, -2, 3, -4);
    struct Tuple tuple;

    tuple = mult_tuple_scalar(a, 3.5);

    if (!is_equal_float(tuple.x, 3.5)) { return -1; }
    if (!is_equal_float(tuple.y, -7)) { return -2; }
    if (!is_equal_float(tuple.z, 10.5)) { return -3; }
    if (!is_equal_float(tuple.w, -14)) { return -4; }

    tuple = mult_tuple_scalar(a, 0.5);

    if (!is_equal_float(tuple.x, 0.5)) { return -5; }
    if (!is_equal_float(tuple.y, -1)) { return -6; }
    if (!is_equal_float(tuple.z, 1.5)) { return -7; }
    if (!is_equal_float(tuple.w, -2)) { return -8; }

    return 1;
}

int test_div_tuple_scalar()
{
    struct Tuple a = new_tuple(1, -2, 3, -4);
    struct Tuple tuple;

    tuple = div_tuple_scalar(a, 2);

    if (!is_equal_float(tuple.x, 0.5)) { return -1; }
    if (!is_equal_float(tuple.y, -1)) { return -2; }
    if (!is_equal_float(tuple.z, 1.5)) { return -3; }
    if (!is_equal_float(tuple.w, -2)) { return -4; }

    return 1;
}

int test_tuple_magnitude()
{
    struct Tuple a;
    float magnitude;

    a = new_vector_tuple(1, 0, 0);
    magnitude = tuple_magnitude(a);

    if (!is_equal_float(magnitude, 1.0)) { return -1; }

    a = new_vector_tuple(0, 1, 0);
    magnitude = tuple_magnitude(a);

    if (!is_equal_float(magnitude, 1.0)) { return -2; }

    a = new_vector_tuple(0, 0, 1);
    magnitude = tuple_magnitude(a);

    if (!is_equal_float(magnitude, 1.0)) { return -3; }

    a = new_vector_tuple(1, 2, 3);
    magnitude = tuple_magnitude(a);

    if (!is_equal_float(magnitude, sqrtf(14.0))) { return -4; }

    a = new_vector_tuple(-1, -2, -3);
    magnitude = tuple_magnitude(a);

    if (!is_equal_float(magnitude, sqrtf(14.0))) { return -5; }
}

int test_normalize_tuple()
{
    struct Tuple a = new_vector_tuple(4, 0, 0);
    struct Tuple tuple = normalize_tuple(a);

    if (!is_equal_tuple(tuple, new_vector_tuple(1, 0, 0))) { return -1; }

    a = new_vector_tuple(1, 2, 3);
    tuple = normalize_tuple(a);

    if (!is_equal_tuple(tuple, new_vector_tuple(1 / sqrtf(14), 2 / sqrtf(14), 3 / sqrtf(14)))) { return -2; }

    a = new_vector_tuple(1, 2, 3);
    tuple = normalize_tuple(a);

    if (!is_equal_float(tuple_magnitude(tuple), 1.0)) { return -3; }

    return 1;
}

int test_dot_product()
{
    struct Tuple a = new_vector_tuple(1, 2, 3);
    struct Tuple b = new_vector_tuple(2, 3, 4);

    float result = dot_product(a, b);

    if (!is_equal_float(result, 20.0)) { return -1; }

    return 1;
}

int test_cross_product()
{
    struct Tuple a = new_vector_tuple(1, 2, 3);
    struct Tuple b = new_vector_tuple(2, 3, 4);

    struct Tuple tuple = cross_product(a, b);

    if (!is_equal_tuple(tuple, new_vector_tuple(-1, 2, -1))) { return -1; }

    tuple = cross_product(b, a);

    if (!is_equal_tuple(tuple, new_vector_tuple(1, -2, 1))) { return -2; }
}

int chapter_one_tests()
{
    int result = 0;

    result = test_is_equal_tuple();
    if (result < 0) {
        printf("test_is_equal_tuple() failed with code: %i\n", result);
    }
    else {
        printf("test_is_equal_tuple() passed.\n");
    }

    result = test_new_tuple_is_point();
    if (result < 0) {
        printf("test_new_tuple_is_point() failed with code: %i\n", result);
    }
    else {
        printf("test_new_tuple_is_point() passed.\n");
    }

    result = test_new_tuple_is_vector();
    if (result < 0) {
        printf("test_new_tuple_is_vector() failed with code: %i\n", result);
    }
    else {
        printf("test_new_tuple_is_vector() passed.\n");
    }

    result = test_new_point_tuple();
    if (result < 0) {
        printf("test_new_point_tuple() failed with code: %i\n", result);
    }
    else {
        printf("test_new_point_tuple() passed.\n");
    }

    result = test_new_vector_tuple();
    if (result < 0) {
        printf("test_new_vector_tuple() failed with code: %i\n", result);
    }
    else {
        printf("test_new_vector_tuple() passed.\n");
    }

    result = test_add_tuples();
    if (result < 0) {
        printf("test_add_tuples() failed with code: %i\n", result);
    }
    else {
        printf("test_add_tuples() passed.\n");
    }

    result = test_subtract_points();
    if (result < 0) {
        printf("test_subtract_points() failed with code: %i\n", result);
    }
    else {
        printf("test_subtract_points() passed.\n");
    }

    result = test_subtract_vector_from_point();
    if (result < 0) {
        printf("test_subtract_vector_from_point() failed with code: %i\n", result);
    }
    else {
        printf("test_subtract_vector_from_point() passed.\n");
    }

    result = test_subtract_vectors();
    if (result < 0) {
        printf("test_subtract_vectors() failed with code: %i\n", result);
    }
    else {
        printf("test_subtract_vectors() passed.\n");
    }

    result = test_subtract_vector_from_zero_vector();
    if (result < 0) {
        printf("test_subtract_vector_from_zero_vector() failed with code: %i\n", result);
    }
    else {
        printf("test_subtract_vector_from_zero_vector() passed.\n");
    }

    result = test_negate_tuple();
    if (result < 0) {
        printf("test_negate_tuple() failed with code: %i\n", result);
    }
    else {
        printf("test_negate_tuple() passed.\n");
    }

    result = test_mult_tuple_scalar();
    if (result < 0) {
        printf("test_mult_tuple_scalar() failed with code: %i\n", result);
    }
    else {
        printf("test_mult_tuple_scalar() passed.\n");
    }

    result = test_div_tuple_scalar();
    if (result < 0) {
        printf("test_div_tuple_scalar() failed with code: %i\n", result);
    }
    else {
        printf("test_div_tuple_scalar() passed.\n");
    }

    result = test_tuple_magnitude();
    if (result < 0) {
        printf("test_tuple_magnitude() failed with code: %i\n", result);
    }
    else {
        printf("test_tuple_magnitude() passed.\n");
    }

    result = test_normalize_tuple();
    if (result < 0) {
        printf("test_normalize_tuple() failed with code: %i\n", result);
    }
    else {
        printf("test_normalize_tuple() passed.\n");
    }

    result = test_dot_product();
    if (result < 0) {
        printf("test_tuple_dot_product() failed with code: %i\n", result);
    }
    else {
        printf("test_tuple_dot_product() passed.\n");
    }

    result = test_cross_product();
    if (result < 0) {
        printf("test_cross_product() failed with code: %i\n", result);
    }
    else {
        printf("test_cross_product() passed.\n");
    }

    return 1;
}