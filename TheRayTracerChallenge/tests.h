#pragma once
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "tuple.h"
#include "color.h"
#include "canvas.h"
#include "matrix.h"
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

// Chapter 1 "Putting It Together" exercise
struct Projectile { struct Tuple position_point; struct Tuple velocity_vector; };
struct Environment { struct Tuple gravity_vector; struct Tuple wind_vector; };

struct Projectile tick(struct Environment env, struct Projectile proj)
{
    struct Projectile updated_proj;

    updated_proj.position_point = add_tuples(proj.position_point, proj.velocity_vector);
    updated_proj.velocity_vector = add_tuples(add_tuples(proj.velocity_vector, env.gravity_vector), env.wind_vector);

    return updated_proj;
}

int test_projectile()
{
    struct Projectile p = { new_point_tuple(0, 1, 0), normalize_tuple(new_vector_tuple(1, 1, 0)) };
    struct Environment e = { new_vector_tuple(0, -0.1, 0), new_vector_tuple(-0.01, 0, 0) };

    while (p.position_point.y > 0)
    {
        printf("Projectile Y position: %f\n", p.position_point.y);
        p = tick(e, p);
    }

    return 1;
}

// Chapter 2 Tests

int test_new_color()
{
    struct Color color = new_color(-0.5, 0.4, 1.7);

    if (!is_equal_float(color.r, -0.5)) { return -1; }
    if (!is_equal_float(color.g, 0.4)) { return -2; }
    if (!is_equal_float(color.b, 1.7)) { return -3; }

    return 1;
}

int test_add_colors()
{
    struct Color a = new_color(0.9, 0.6, 0.75);
    struct Color b = new_color(0.7, 0.1, 0.25);
    struct Color color = add_colors(a, b);

    if (!is_equal_float(color.r, 1.6)) { return -1; }
    if (!is_equal_float(color.g, 0.7)) { return -2; }
    if (!is_equal_float(color.b, 1.0)) { return -3; }

    return 1;
}

int test_subtract_colors()
{
    struct Color a = new_color(0.9, 0.6, 0.75);
    struct Color b = new_color(0.7, 0.1, 0.25);
    struct Color color = subtract_colors(a, b);

    if (!is_equal_float(color.r, 0.2)) { return -1; }
    if (!is_equal_float(color.g, 0.5)) { return -2; }
    if (!is_equal_float(color.b, 0.5)) { return -3; }

    return 1;
}

int test_mult_color_scalar()
{
    struct Color a = new_color(0.2, 0.3, 0.4);
    struct Color color = mult_color_scalar(a, 2);

    if (!is_equal_float(color.r, 0.4)) { return -1; }
    if (!is_equal_float(color.g, 0.6)) { return -2; }
    if (!is_equal_float(color.b, 0.8)) { return -3; }

    return 1;
}

int test_mult_colors()
{
    struct Color a = new_color(1, 0.2, 0.4);
    struct Color b = new_color(0.9, 1.0, 0.1);
    struct Color color = mult_colors(a, b);

    if (!is_equal_float(color.r, 0.9)) { return -1; }
    if (!is_equal_float(color.g, 0.2)) { return -2; }
    if (!is_equal_float(color.b, 0.04)) { return -3; }

    return 1;
}

int test_new_canvas()
{
    struct Canvas canvas = new_canvas(10, 20);

    if (canvas.canvas == NULL) { return -1; }
    if (canvas.width != 10) { return -2; }
    if (canvas.height != 20) { return -3; }

    unsigned int canvas_array_length = canvas.width * canvas.height;

    struct Color tmp_color;

    for (int i = 0; i < canvas_array_length; i++)
    {
        tmp_color = canvas.canvas[i];
        if (!is_equal_float(tmp_color.r, 0.0)) { return -4; }
        if (!is_equal_float(tmp_color.g, 0.0)) { return -5; }
        if (!is_equal_float(tmp_color.b, 0.0)) { return -6; }
    }

    free_canvas(&canvas);

    if (canvas.canvas != NULL) { return -7; }

    return 1;

}

int test_set_pixel()
{
    struct Canvas canvas = new_canvas(10, 20);
    if (canvas.canvas == NULL) { return -1; }

    struct Color red = new_color(1, 0, 0);

    set_pixel(&canvas, 2, 3, red);
    struct Color color = get_pixel(canvas, 2, 3);

    if (!is_equal_color(red, color)) { return -2; }

    free_canvas(&canvas);
    return 1;
}

int test_ppm_header()
{
    struct Canvas canvas = new_canvas(5, 3);
    if (canvas.canvas == NULL) { return -1; }

    // Write canvas to .ppm file
    int res = write_ppm(canvas, "test_ppm_header.ppm");
    if (res != 1) { return -2; }

    // Construct expected .ppm header string
    const char *expected_ppm_header = "P3\n5 3\n255\n";

    // Read the .ppm file that was just written
    int ppm_data_from_file_length = 0;
    char* ppm_data_from_file = read_ppm("test_ppm_header.ppm", &ppm_data_from_file_length);

    // Copy just the header of the read .ppm file
    // First allocate a char array to fit the expected header (plus one extra length for terminating zero)
    int ppm_header_length = strlen(expected_ppm_header);
    char *ppm_header_from_file = (char*)malloc(ppm_header_length + 1);
    memset(ppm_header_from_file, 0, ppm_header_length + 1);
    // Copy just the header from the .ppm data read from the file
    strncpy_s(ppm_header_from_file, ppm_header_length + 1, ppm_data_from_file, ppm_header_length);
    // Compare the expected .ppm header to the one that was read from the created file
    int compare = strncmp(expected_ppm_header, ppm_header_from_file, ppm_header_length);
    if (compare != 0) { free(ppm_header_from_file); free(ppm_data_from_file); return -3; }

    free(ppm_header_from_file);
    free(ppm_data_from_file);
}

int test_ppm_data()
{
    struct Canvas canvas = new_canvas(5, 3);
    if (canvas.canvas == NULL) { return -1; }

    struct Color c1 = new_color(1.5, 0, 0);
    struct Color c2 = new_color(0, 0.5, 0);
    struct Color c3 = new_color(-0.5, 0, 1);

    set_pixel(&canvas, 0, 0, c1);
    set_pixel(&canvas, 2, 1, c2);
    set_pixel(&canvas, 4, 2, c3);

    // Construct the expected ppm data
    const char* expected_ppm_data_section = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    int expected_ppm_data_section_length = strlen(expected_ppm_data_section);

    // Write canvas to .ppm file
    int res = write_ppm(canvas, "test_ppm_data.ppm");
    if (res != 1) { return -2; }

    // Read the .ppm file that was just written
    int ppm_from_file_length = 0;
    char* ppm_from_file = read_ppm("test_ppm_data.ppm", &ppm_from_file_length);

    // Copy just the .ppm data section
    char* ppm_data_section_from_file = (char*)malloc(expected_ppm_data_section_length + 1); // + 1 for the terminating zero
    if (ppm_data_section_from_file == NULL) { return -3; }
    memset(ppm_data_section_from_file, 0, expected_ppm_data_section_length + 1);
    strncpy_s(ppm_data_section_from_file, expected_ppm_data_section_length + 1, ppm_from_file + strlen("P3\n5 3\n255\n"), expected_ppm_data_section_length);

    // Compare the expected data to the data in the file
    int compare = strncmp(expected_ppm_data_section, ppm_data_section_from_file, expected_ppm_data_section_length);
    if (compare != 0) { return -4; }

    free(ppm_data_section_from_file);
    free(ppm_from_file);
    return 1;
}

int test_ppm_data_long()
{
    struct Canvas canvas = new_canvas(10, 2);
    if (canvas.canvas == NULL) { return -1; }

    struct Color c1 = new_color(1, 0.8, 0.6);

    set_all_pixels(&canvas, c1);

    // Construct the expected ppm data
    const char* expected_ppm_data_section = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    int expected_ppm_data_section_length = strlen(expected_ppm_data_section);

    // Write the canvas to .ppm file
    int res = write_ppm(canvas, "test_ppm_data_long.ppm");
    if (res != 1) { return -2; }

    // Read the .ppm file that was just written
    int ppm_from_file_length = 0;
    char* ppm_from_file = read_ppm("test_ppm_data_long.ppm", &ppm_from_file_length);

    // Copy just the .ppm data section
    char* ppm_data_section_from_file = (char*)malloc(expected_ppm_data_section_length + 1); // + 1 for the terminating zero
    if (ppm_data_section_from_file == NULL) { return -3; }
    memset(ppm_data_section_from_file, 0, expected_ppm_data_section_length + 1);
    strncpy_s(ppm_data_section_from_file, expected_ppm_data_section_length + 1, ppm_from_file + strlen("P3\n10 2\n255\n"), expected_ppm_data_section_length);

    // Compare the expected data to the data in the file
    int compare = strncmp(expected_ppm_data_section, ppm_data_section_from_file, expected_ppm_data_section_length);
    if (compare != 0) { return -4; }

    free(ppm_data_section_from_file);
    free(ppm_from_file);
    return 1;
}

// Chapter 3 Tests
int test_4x4_matrix()
{
    Matrix m = new_matrix(4, 4);
    set_matrix_element(&m, 0, 0, 1); set_matrix_element(&m, 0, 1, 2); set_matrix_element(&m, 0, 2, 3); set_matrix_element(&m, 0, 3, 4);
    set_matrix_element(&m, 1, 0, 5.5); set_matrix_element(&m, 1, 1, 6.5); set_matrix_element(&m, 1, 2, 7.5); set_matrix_element(&m, 1, 3, 8.5);
    set_matrix_element(&m, 2, 0, 9); set_matrix_element(&m, 2, 1, 10); set_matrix_element(&m, 2, 2, 11); set_matrix_element(&m, 2, 3, 12);
    set_matrix_element(&m, 3, 0, 13.5); set_matrix_element(&m, 3, 1, 14.5); set_matrix_element(&m, 3, 2, 15.5); set_matrix_element(&m, 3, 3, 16.5);

    float elem = 0; int error = 0;
    if (!is_equal_float(1, get_matrix_element(&m, 0, 0, &error))) { return -1; }
    if (!is_equal_float(4, get_matrix_element(&m, 0, 3, &error))) { return -2; }
    if (!is_equal_float(5.5, get_matrix_element(&m, 1, 0, &error))) { return -3; }
    if (!is_equal_float(7.5, get_matrix_element(&m, 1, 2, &error))) { return -4; }
    if (!is_equal_float(11, get_matrix_element(&m, 2, 2, &error))) { return -5; }
    if (!is_equal_float(13.5, get_matrix_element(&m, 3, 0, &error))) { return -6; }
    if (!is_equal_float(15.5, get_matrix_element(&m, 3, 2, &error))) { return -7; }

    free_matrix(&m);
    return 1;
}

int test_2x2_matrix()
{
    Matrix m = new_matrix(2, 2);
    set_matrix_element(&m, 0, 0, -3); set_matrix_element(&m, 0, 1, 5); 
    set_matrix_element(&m, 1, 0, 1); set_matrix_element(&m, 1, 1, -2);

    float elem = 0; int error = 0;
    if (!is_equal_float(-3, get_matrix_element(&m, 0, 0, &error))) { return -1; }
    if (!is_equal_float(5, get_matrix_element(&m, 0, 1, &error))) { return -2; }
    if (!is_equal_float(1, get_matrix_element(&m, 1, 0, &error))) { return -3; }
    if (!is_equal_float(-2, get_matrix_element(&m, 1, 1, &error))) { return -4; }

    free_matrix(&m);
    return 1;
}

int test_3x3_matrix()
{
    Matrix m = new_matrix(3, 3);
    set_matrix_element(&m, 0, 0, -3); set_matrix_element(&m, 0, 1, 5); set_matrix_element(&m, 0, 2, 0);
    set_matrix_element(&m, 1, 0, 1); set_matrix_element(&m, 1, 1, -2); set_matrix_element(&m, 1, 2, -7);
    set_matrix_element(&m, 2, 0, 0); set_matrix_element(&m, 2, 1, 1); set_matrix_element(&m, 2, 2, 1);

    float elem = 0; int error = 0;
    if (!is_equal_float(-3, get_matrix_element(&m, 0, 0, &error))) { return -1; }
    if (!is_equal_float(-2, get_matrix_element(&m, 1, 1, &error))) { return -2; }
    if (!is_equal_float(1, get_matrix_element(&m, 2, 2, &error))) { return -3; }

    free_matrix(&m);
    return 1;
}

int test_new_matrix_4x4()
{
    float values[16] = { 1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5 };
    Matrix m = new_matrix_4x4(values);

    float elem = 0; int error = 0;
    if (!is_equal_float(1, get_matrix_element(&m, 0, 0, &error))) { return -1; }
    if (!is_equal_float(4, get_matrix_element(&m, 0, 3, &error))) { return -2; }
    if (!is_equal_float(5.5, get_matrix_element(&m, 1, 0, &error))) { return -3; }
    if (!is_equal_float(7.5, get_matrix_element(&m, 1, 2, &error))) { return -4; }
    if (!is_equal_float(11, get_matrix_element(&m, 2, 2, &error))) { return -5; }
    if (!is_equal_float(13.5, get_matrix_element(&m, 3, 0, &error))) { return -6; }
    if (!is_equal_float(15.5, get_matrix_element(&m, 3, 2, &error))) { return -7; }

    free_matrix(&m);
    return 1;
}

int test_new_matrix_2x2()
{
    float values[16] = { -3, 5, 1, -2 };
    Matrix m = new_matrix_2x2(values);

    float elem = 0; int error = 0;
    if (!is_equal_float(-3, get_matrix_element(&m, 0, 0, &error))) { return -1; }
    if (!is_equal_float(5, get_matrix_element(&m, 0, 1, &error))) { return -2; }
    if (!is_equal_float(1, get_matrix_element(&m, 1, 0, &error))) { return -3; }
    if (!is_equal_float(-2, get_matrix_element(&m, 1, 1, &error))) { return -4; }

    free_matrix(&m);
    return 1;
}

int test_new_matrix_3x3()
{
    float values[16] = { -3, 5, 0, 1, -2, -7, 0, 1, 1 };
    Matrix m = new_matrix_3x3(values);

    float elem = 0; int error = 0;
    if (!is_equal_float(-3, get_matrix_element(&m, 0, 0, &error))) { return -1; }
    if (!is_equal_float(-2, get_matrix_element(&m, 1, 1, &error))) { return -2; }
    if (!is_equal_float(1, get_matrix_element(&m, 2, 2, &error))) { return -3; }

    free_matrix(&m);
    return 1;
}

int test_is_equal_matrix()
{
    float a_values[16] = { 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2 };
    float b_values[16] = { 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2 };

    Matrix A = new_matrix_4x4(a_values);
    Matrix B = new_matrix_4x4(b_values);

    if (is_equal_matrix(4, 4, &A, &B) != 1) { return -1; }

    free_matrix(&A);
    free_matrix(&B);

    float c_values[16] = { 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2 };
    float d_values[16] = { 2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1 };

    Matrix C = new_matrix_4x4(c_values);
    Matrix D = new_matrix_4x4(d_values);

    if (is_equal_matrix(4, 4, &C, &D) != 0) { return -2; }

    free_matrix(&C);
    free_matrix(&D);

    return 1;
}

int test_mult_4x4_matrices()
{
    float a_values[16] = { 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2 };
    float b_values[16] = { -2,1,2,3,3,2,1,-1,4,3,6,5,1,2,7,8 };
    float p_values[16] = { 20,22,50,48,44,54,114,108,40,58,110,102,16,26,46,42 };

    Matrix A = new_matrix_4x4(a_values);
    Matrix B = new_matrix_4x4(b_values);
    Matrix P = new_matrix_4x4(p_values);

    int error = 0;
    Matrix T = mult_4x4_matrices(&A, &B, &error);

    if (error != 1) { return -1; }
    if (is_equal_matrix(4, 4, &P, &T) != 1) { return -2; }

    free_matrix(&A);
    free_matrix(&B);
    free_matrix(&P);
    return 1;
}

int test_mult_4x4_matrix_tuple()
{
    float a_values[16] = { 1,2,3,4,2,4,4,2,8,6,4,1,0,0,0,1 };

    Matrix A = new_matrix_4x4(a_values);
    Tuple B = new_tuple(1, 2, 3, 1);

    int error = 0;
    Tuple P = mult_4x4_matrix_tuple(&A, &B, &error);

    free_matrix(&A);

    if (P.x != 18) { return -1; }
    if (P.y != 24) { return -2; }
    if (P.z != 33) { return -3; }
    if (P.w != 1) { return -4; }
    
    return 1;
}

int test_new_matrix_4x4_identity()
{
    float a_values[16] = { 0,1,2,4,1,2,4,8,2,4,8,16,4,8,16,32 };
    Matrix A = new_matrix_4x4(a_values);
    Matrix I = new_matrix_4x4_identity();

    int error = 0;
    Matrix P = mult_4x4_matrices(&A, &I, &error);

    int comp = is_equal_matrix(4, 4, &A, &P);

    free_matrix(&A);
    free_matrix(&I);
    free_matrix(&P);

    if (comp != 1) { return -1; }
    return 1;
}

int test_transpose_4x4_matrix()
{
    float a_values[16] = { 0,9,3,0,9,8,0,8,1,8,5,3,0,0,5,8 };
    float b_values[16] = { 0,9,1,0,9,8,8,0,3,0,5,5,0,8,3,8 };
    Matrix A = new_matrix_4x4(a_values);
    Matrix B = new_matrix_4x4(b_values);
    
    int error = 0;
    Matrix T = transpose_4x4_matrix(&A, &error);
    int comp = is_equal_matrix(4, 4, &B, &T);

    free_matrix(&A);
    free_matrix(&B);
    free_matrix(&T);

    if (comp != 1) { return -1; }
    return 1;
}

int test_det_2x2_matrix()
{
    float a_values[4] = { 1,5,-3,2 };

    Matrix A = new_matrix_2x2(a_values);

    int error = 0;
    float det = det_2x2_matrix(&A, &error);
    int comp = is_equal_float(det, 17);
    
    free_matrix(&A);

    if (comp != 1) { return -1; }
    return 1;
}

int test_submatrix_3x3()
{
    float a_values[9] = { 1,5,0,-3,2,7,0,6,-3 };
    struct Matrix A = new_matrix_3x3(a_values);
    float b_values[4] = { -3,2,0,6 };
    struct Matrix B = new_matrix_2x2(b_values);
    
    int error = 0;
    struct Matrix S = submatrix_3x3(&A, 0, 2, &error);

    int comp = is_equal_matrix(2, 2, &B, &S);
    
    free_matrix(&A);
    free_matrix(&B);
    free_matrix(&S);
    
    if (comp != 1) { return -1; }
    return 1;
}

int test_submatrix_4x4()
{
    float a_values[16] = {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
    struct Matrix A = new_matrix_4x4(a_values);
    float b_values[9] = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
    struct Matrix B = new_matrix_3x3(b_values);

    int error = 0;
    struct Matrix S = submatrix_4x4(&A, 2, 1, &error);

    int comp = is_equal_matrix(3, 3, &B, &S);

    free_matrix(&A);
    free_matrix(&B);
    free_matrix(&S);

    if (comp != 1) { return -1; }
    return 1;
}

int test_minor_3x3_matrix()
{
    float a_values[9] = { 3,5,0,2,-1,-7,6,-1,5 };
    struct Matrix A = new_matrix_3x3(a_values);

    int error = 0;
    float minor = minor_3x3_matrix(&A, 1, 0, &error);

    free_matrix(&A);

    if (!is_equal_float(minor, 25)) { return -1; }

    return 1;
}

int test_cofactor_3x3_matrix()
{
    float a_values[9] = { 3,5,0,2,-1,-7,6,-1,5 };
    struct Matrix A = new_matrix_3x3(a_values);

    int error = 0;
    
    float m1 = minor_3x3_matrix(&A, 0, 0, &error);
    if (error != 1) { free_matrix(&A); return -1; }
    if (!is_equal_float(m1, -12)) { free_matrix(&A); return -2; }

    float c1 = cofactor_3x3_matrix(&A, 0, 0, &error);
    if (error != 1) { free_matrix(&A); return -3; }
    if (!is_equal_float(c1, -12)) { free_matrix(&A); return -4; }

    float m2 = minor_3x3_matrix(&A, 1, 0, &error);
    if (error != 1) { free_matrix(&A); return -5; }
    if (!is_equal_float(m2, 25)) { free_matrix(&A); return -6; }

    float c2 = cofactor_3x3_matrix(&A, 1, 0, &error);
    if (error != 1) { free_matrix(&A); return -7; }
    if (!is_equal_float(c2, -25)) { free_matrix(&A); return -8; }

    free_matrix(&A);
    return 1;
}

int test_det_3x3_matrix()
{
    float a_values[9] = {1,2,6,-5,8,-4,2,6,4};
    struct Matrix A = new_matrix_3x3(a_values);

    int error = 0;
    float c1 = cofactor_3x3_matrix(&A, 0, 0, &error);
    float c2 = cofactor_3x3_matrix(&A, 0, 1, &error);
    float c3 = cofactor_3x3_matrix(&A, 0, 2, &error);

    float det = det_3x3_matrix(&A, &error);

    free_matrix(&A);

    if (!is_equal_float(c1, 56)) { return -1; }
    if (!is_equal_float(c2, 12)) { return -2; }
    if (!is_equal_float(c3, -46)) { return -3; }
    if (!is_equal_float(det, -196)) { return -4; }

    return 1;
}

int test_det_4x4_matrix()
{
    float a_values[16] = { -2,-8,3,5,-3,1,7,3,1,2,-9,6,-6,7,7,-9 };
    struct Matrix A = new_matrix_4x4(a_values);

    int error = 0;
    float c1 = cofactor_4x4_matrix(&A, 0, 0, &error);
    float c2 = cofactor_4x4_matrix(&A, 0, 1, &error);
    float c3 = cofactor_4x4_matrix(&A, 0, 2, &error);
    float c4 = cofactor_4x4_matrix(&A, 0, 3, &error);

    float det = det_4x4_matrix(&A, &error);

    if (!is_equal_float(c1, 690)) { return -1; }
    if (!is_equal_float(c2, 447)) { return -2; }
    if (!is_equal_float(c3, 210)) { return -3; }
    if (!is_equal_float(c4, 51)) { return -4; }
    if (!is_equal_float(det, -4071)) { return -5; }

    free_matrix(&A);
    return 1;
}

int test_is_invertable_4x4_matrix()
{
    float a_values[16] = { 6,4,4,4,5,5,7,6,4,-9,3,-7,9,1,7,-6 };
    float b_values[16] = { -4,2,-2,-3,9,6,2,6,0,-5,1,-5,0,0,0,0 };

    struct Matrix A = new_matrix_4x4(a_values);
    struct Matrix B = new_matrix_4x4(b_values);

    unsigned int is_invertable_A = 0;
    unsigned int is_invertable_B = 0;

    int error = 0;
    is_invertable_A = is_invertable_4x4_matrix(&A, &error);
    is_invertable_B = is_invertable_4x4_matrix(&B, &error);

    free_matrix(&A);
    free_matrix(&B);

    if (is_invertable_A != 1) { return -1; }
    if (is_invertable_B != 0) { return -2; }

    return 1;
}

int test_inverse_4x4_matrix()
{
    float a_values[16] = { -5,2,6,-8,1,-5,1,8,7,7,-6,-7,1,-3,7,4 };
    struct Matrix A = new_matrix_4x4(a_values);

    float expected_inverse_values[16] = { 0.21805, 0.45113, 0.24060, -0.04511, -0.80827, -1.45677, -0.44361, 0.52068, -0.07895, -0.22368, -0.05263, 0.19737, -0.52256, -0.81391, -0.30075, 0.30639 };
    struct Matrix expected_inverse_A = new_matrix_4x4(expected_inverse_values);

    int error = 0;
    float det = det_4x4_matrix(&A, &error);
    float c1 = cofactor_4x4_matrix(&A, 2, 3, &error);

    struct Matrix inverse_A = inverse_4x4_matrix(&A, &error);
    float inverse_A_3_2 = get_matrix_element(&inverse_A, 3, 2, &error);
    float c2 = cofactor_4x4_matrix(&A, 3, 2, &error);
    float inverse_A_2_3 = get_matrix_element(&inverse_A, 2, 3, &error);

    free_matrix(&A);
    
    if (!is_equal_float(det, 532)) { free_matrix(&inverse_A); free_matrix(&expected_inverse_A); return -1; }
    if (!is_equal_float(c1, -160)) { free_matrix(&inverse_A); free_matrix(&expected_inverse_A); return -2; }
    if (!is_equal_float(inverse_A_3_2, (-160.0/532.0))) { free_matrix(&inverse_A); free_matrix(&expected_inverse_A); return -3; }
    if (!is_equal_float(c2, 105)) { free_matrix(&inverse_A); free_matrix(&expected_inverse_A); return -4; }
    if (!is_equal_float(inverse_A_2_3, (105.0/532.0))) { free_matrix(&inverse_A); free_matrix(&expected_inverse_A); return -5; }
    if (!is_equal_matrix(4, 4, &expected_inverse_A, &inverse_A)) { free_matrix(&inverse_A); free_matrix(&expected_inverse_A); return -6; }

    free_matrix(&inverse_A);
    free_matrix(&expected_inverse_A);

    return 1;
}

int test_inverse_4x4_matrix_extra()
{
    float a_values[16] = { 8,-5,9,2,7,5,6,1,-6,0,9,6,-3,0,-9,-4 };
    float b_values[16] = { 9,3,0,9,-5,-2,-6,-3,-4,9,6,4,-7,6,6,2 };
    float expected_inverse_a_values[16] = { -0.15385, -0.15385, -0.28205, -0.53846, -0.07692, 0.12308, 0.02564, 0.03077, 0.35897, 0.35897, 0.43590, 0.92308, -0.69231, -0.69231, -0.76923, -1.92308 };
    float expected_inverse_b_values[16] = { -0.04074, -0.07778, 0.14444, -0.22222, -0.07778, 0.03333, 0.36667, -0.33333, -0.02901, -0.14630, -0.10926, 0.12963, 0.17778, 0.06667, -0.26667, 0.33333 };

    int error = 0;
    struct Matrix A = new_matrix_4x4(a_values);
    struct Matrix B = new_matrix_4x4(b_values);
    struct Matrix expected_inverse_A = new_matrix_4x4(expected_inverse_a_values);
    struct Matrix expected_inverse_B = new_matrix_4x4(expected_inverse_b_values);
    struct Matrix inverse_A = inverse_4x4_matrix(&A, &error);
    struct Matrix inverse_B = inverse_4x4_matrix(&B, &error);

    free_matrix(&A);
    free_matrix(&B);

    if (!is_equal_matrix(4, 4, &expected_inverse_A, &inverse_A)) { free_matrix(&expected_inverse_A); free_matrix(&inverse_A); free_matrix(&expected_inverse_B); free_matrix(&inverse_B); return -1; }
    if (!is_equal_matrix(4, 4, &expected_inverse_B, &inverse_B)) { free_matrix(&expected_inverse_A); free_matrix(&inverse_A); free_matrix(&expected_inverse_B); free_matrix(&inverse_B); return -2; }

    free_matrix(&expected_inverse_A);
    free_matrix(&inverse_A); 
    free_matrix(&expected_inverse_B); 
    free_matrix(&inverse_B);

    return 1;
}

int test_inverse_4x4_matrix_multiplication()
{
    float a_values[16] = {3,-9,7,3,3,-8,2,-9,-4,4,4,1,-6,5,-1,1};
    float b_values[16] = {8,2,2,2,3,-1,7,0,7,0,5,4,6,-2,0,5};

    struct Matrix A = new_matrix_4x4(a_values);
    struct Matrix B = new_matrix_4x4(b_values);

    int error = 0;
    struct Matrix C = mult_4x4_matrices(&A, &B, &error);

    struct Matrix inverse_B = inverse_4x4_matrix(&B, &error);
    struct Matrix C_inverse_B = mult_4x4_matrices(&C, &inverse_B, &error);

    int comp = is_equal_matrix(4, 4, &A, &C_inverse_B);

    free_matrix(&A);
    free_matrix(&B);
    free_matrix(&C);
    free_matrix(&inverse_B);
    free_matrix(&C_inverse_B);

    if (comp != 1) { return -1; }
    else return 1;
}

// Chapter 3 Tests
int test_translation_matrix()
{
    struct Matrix T = new_translation_matrix(5, -3, 2);
    struct Tuple point = new_point_tuple(-3, 4, 5);
    struct Tuple expected_transformed_point = new_point_tuple(2, 1, 7);

    int error = 0;
    struct Tuple transformed_point = mult_4x4_matrix_tuple(&T, &point, &error);
    int comp = is_equal_tuple(expected_transformed_point, transformed_point);

    free_matrix(&T);

    if (comp != 1) { return -1; }
    else return 1;
}

int test_translation_inversion()
{
    struct Matrix T = new_translation_matrix(5, -3, 2);
    int error = 0;
    struct Matrix inverse_T = inverse_4x4_matrix(&T, &error);
    struct Tuple point = new_point_tuple(-3, 4, 5);
    struct Tuple expected_inverse_point = new_point_tuple(-8, 7, 3);

    struct Tuple inverse_point = mult_4x4_matrix_tuple(&inverse_T, &point, &error);

    int comp = is_equal_tuple(expected_inverse_point, inverse_point);

    free_matrix(&T);
    free_matrix(&inverse_T);

    if (comp != 1) { return -1; }
    else return 1;
}

int test_translation_vector()
{
    struct Matrix T = new_translation_matrix(5, -3, 2);
    struct Tuple vector = new_vector_tuple(-3, 4, 5);

    int error = 0;
    struct Tuple translated_vector = mult_4x4_matrix_tuple(&T, &vector, &error);

    int comp = is_equal_tuple(vector, translated_vector);

    free_matrix(&T);

    if (comp != 1) { return -1; }
    else return 1;
}

int test_scaling_matrix()
{
    struct Matrix S = new_scaling_matrix(2, 3, 4);
    struct Tuple point = new_point_tuple(-4, 6, 8);
    struct Tuple expected_scaled_point = new_point_tuple(-8, 18, 32);

    int error = 0;
    struct Tuple scaled_point = mult_4x4_matrix_tuple(&S, &point, &error);

    int comp = is_equal_tuple(expected_scaled_point, scaled_point);

    free_matrix(&S);

    if (comp != 1) { return -1; }
    else return 1;
}

int test_scaling_vector()
{
    struct Matrix S = new_scaling_matrix(2, 3, 4);
    struct Tuple vector = new_vector_tuple(-4, 6, 8);
    struct Tuple expected_scaled_vector = new_vector_tuple(-8, 18, 32);

    int error = 0;
    struct Tuple scaled_vector = mult_4x4_matrix_tuple(&S, &vector, &error);

    int comp = is_equal_tuple(expected_scaled_vector, scaled_vector);

    free_matrix(&S);

    if (comp != 1) { return -1; }
    else return 1;
}

int test_scaling_inversion()
{
    struct Matrix S = new_scaling_matrix(2, 3, 4);
    int error = 0;
    struct Matrix inverse_S = inverse_4x4_matrix(&S, &error);
    struct Tuple vector = new_vector_tuple(-4, 6, 8);
    struct Tuple expected_inverted_scaled_vector = new_vector_tuple(-2, 2, 2);

    struct Tuple scaled_vector = mult_4x4_matrix_tuple(&inverse_S, &vector, &error);

    int comp = is_equal_tuple(expected_inverted_scaled_vector, scaled_vector);

    free_matrix(&S);
    free_matrix(&inverse_S);

    if (comp != 1) { return -1; }
    else return 1;
}

int test_scaling_reflection()
{
    struct Matrix S = new_scaling_matrix(-1, 1, 1);
    struct Tuple point = new_point_tuple(2, 3, 4);
    struct Tuple expected_scaled_point = new_point_tuple(-2, 3, 4);

    int error = 0;
    struct Tuple scaled_point = mult_4x4_matrix_tuple(&S, &point, &error);

    int comp = is_equal_tuple(expected_scaled_point, scaled_point);

    free_matrix(&S);

    if (comp != 1) { return -1; }
    else return 1;
}

int test_rotation_x_matrix()
{
    struct Tuple point = new_point_tuple(0, 1, 0);
    struct Tuple expected_half_quarter_point = new_point_tuple(0, sqrt(2) / 2, sqrt(2) / 2);
    struct Tuple expected_full_quarter_point = new_point_tuple(0, 0, 1);

    struct Matrix half_quarter_x_rotation_matrix = new_rotation_x_matrix(M_PI / 4.0);
    struct Matrix full_quarter_x_rotation_matrix = new_rotation_x_matrix(M_PI / 2.0);

    int error = 0;
    struct Tuple half_quarter_point = mult_4x4_matrix_tuple(&half_quarter_x_rotation_matrix, &point, &error);
    struct Tuple full_quarter_point = mult_4x4_matrix_tuple(&full_quarter_x_rotation_matrix, &point, &error);

    int comp1 = is_equal_tuple(expected_half_quarter_point, half_quarter_point);
    int comp2 = is_equal_tuple(expected_full_quarter_point, full_quarter_point);

    free_matrix(&half_quarter_x_rotation_matrix);
    free_matrix(&full_quarter_x_rotation_matrix);

    if (comp1 != 1) { return -1; }
    else if (comp2 != 1) { return -2; }
    else return 1;
}

int chapter_one_tests()
{
    int result = 0;
    int num_failed = 0;

    result = test_is_equal_tuple();
    if (result < 0) {
        printf("test_is_equal_tuple() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_is_equal_tuple() passed.\n");
    }

    result = test_new_tuple_is_point();
    if (result < 0) {
        printf("test_new_tuple_is_point() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_new_tuple_is_point() passed.\n");
    }

    result = test_new_tuple_is_vector();
    if (result < 0) {
        printf("test_new_tuple_is_vector() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_new_tuple_is_vector() passed.\n");
    }

    result = test_new_point_tuple();
    if (result < 0) {
        printf("test_new_point_tuple() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_new_point_tuple() passed.\n");
    }

    result = test_new_vector_tuple();
    if (result < 0) {
        printf("test_new_vector_tuple() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_new_vector_tuple() passed.\n");
    }

    result = test_add_tuples();
    if (result < 0) {
        printf("test_add_tuples() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_add_tuples() passed.\n");
    }

    result = test_subtract_points();
    if (result < 0) {
        printf("test_subtract_points() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_subtract_points() passed.\n");
    }

    result = test_subtract_vector_from_point();
    if (result < 0) {
        printf("test_subtract_vector_from_point() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_subtract_vector_from_point() passed.\n");
    }

    result = test_subtract_vectors();
    if (result < 0) {
        printf("test_subtract_vectors() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_subtract_vectors() passed.\n");
    }

    result = test_subtract_vector_from_zero_vector();
    if (result < 0) {
        printf("test_subtract_vector_from_zero_vector() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_subtract_vector_from_zero_vector() passed.\n");
    }

    result = test_negate_tuple();
    if (result < 0) {
        printf("test_negate_tuple() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_negate_tuple() passed.\n");
    }

    result = test_mult_tuple_scalar();
    if (result < 0) {
        printf("test_mult_tuple_scalar() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_mult_tuple_scalar() passed.\n");
    }

    result = test_div_tuple_scalar();
    if (result < 0) {
        printf("test_div_tuple_scalar() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_div_tuple_scalar() passed.\n");
    }

    result = test_tuple_magnitude();
    if (result < 0) {
        printf("test_tuple_magnitude() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_tuple_magnitude() passed.\n");
    }

    result = test_normalize_tuple();
    if (result < 0) {
        printf("test_normalize_tuple() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_normalize_tuple() passed.\n");
    }

    result = test_dot_product();
    if (result < 0) {
        printf("test_tuple_dot_product() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_tuple_dot_product() passed.\n");
    }

    result = test_cross_product();
    if (result < 0) {
        printf("test_cross_product() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_cross_product() passed.\n");
    }

    // result = test_projectile();
    // Result of test_projectile() is irrelevant; it's just an exercise

    return num_failed;
}

int chapter_two_tests()
{
    int result = 0;
    int num_failed = 0;

    result = test_new_color();
    if (result < 0) {
        printf("test_new_color() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_new_color() passed.\n");
    }

    result = test_add_colors();
    if (result < 0) {
        printf("test_add_colors() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_add_colors() passed.\n");
    }

    result = test_subtract_colors();
    if (result < 0) {
        printf("test_subtract_colors() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_subtract_colors() passed.\n");
    }

    result = test_mult_color_scalar();
    if (result < 0) {
        printf("test_mult_color_scalar() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_mult_color_scalar() passed.\n");
    }

    result = test_mult_colors();
    if (result < 0) {
        printf("test_mult_colors() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_mult_colors() passed.\n");
    }

    result = test_new_canvas();
    if (result < 0) {
        printf("test_new_canvas() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_new_canvas() passed.\n");
    }

    result = test_set_pixel();
    if (result < 0) {
        printf("test_set_pixel() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_set_pixel() passed.\n");
    }

    result = test_ppm_header();
    if (result < 0) {
        printf("test_ppm_header() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_ppm_header() passed.\n");
    }

    result = test_ppm_data();
    if (result < 0) {
        printf("test_ppm_data() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_ppm_data() passed.\n");
    }

    result = test_ppm_data_long();
    if (result < 0) {
        printf("test_ppm_data_long() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_ppm_data_long() passed.\n");
    }

    return num_failed;
}

int chapter_three_tests()
{
    int result = 0;
    int num_failed = 0;

    result = test_4x4_matrix();
    if (result < 0) {
        printf("test_4x4_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_4x4_matrix() passed.\n");
    }

    result = test_new_matrix_4x4();
    if (result < 0) {
        printf("test_new_matrix_4x4() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_new_matrix_4x4() passed.\n");
    }

    result = test_2x2_matrix();
    if (result < 0) {
        printf("test_2x2_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_2x2_matrix() passed.\n");
    }

    result = test_new_matrix_2x2();
    if (result < 0) {
        printf("test_new_matrix_2x2() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_new_matrix_2x2() passed.\n");
    }

    result = test_3x3_matrix();
    if (result < 0) {
        printf("test_3x3_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_3x3_matrix() passed.\n");
    }

    result = test_is_equal_matrix();
    if (result < 0) {
        printf("test_is_equal_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_is_equal_matrix() passed.\n");
    }

    result = test_mult_4x4_matrices();
    if (result < 0) {
        printf("test_mult_4x4_matrices() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_mult_4x4_matrices() passed.\n");
    }

    result = test_mult_4x4_matrix_tuple();
    if (result < 0) {
        printf("test_mult_4x4_matrix_tuple() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_mult_4x4_matrix_tuple() passed.\n");
    }

    result = test_new_matrix_4x4_identity();
    if (result < 0) {
        printf("test_new_matrix_4x4_identity() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_new_matrix_4x4_identity() passed.\n");
    }

    result = test_transpose_4x4_matrix();
    if (result < 0) {
        printf("test_transpose_4x4_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_transpose_4x4_matrix() passed.\n");
    }

    result = test_det_2x2_matrix();
    if (result < 0) {
        printf("test_det_2x2_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_det_2x2_matrix() passed.\n");
    }

    result = test_submatrix_3x3();
    if (result < 0) {
        printf("test_submatrix_3x3() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_submatrix_3x3() passed.\n");
    }

    result = test_submatrix_4x4();
    if (result < 0) {
        printf("test_submatrix_4x4() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_submatrix_4x4() passed.\n");
    }

    result = test_minor_3x3_matrix();
    if (result < 0) {
        printf("test_minor_3x3_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_minor_3x3_matrix() passed.\n");
    }

    result = test_cofactor_3x3_matrix();
    if (result < 0) {
        printf("test_cofactor_3x3_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_cofactor_3x3_matrix() passed.\n");
    }

    result = test_det_3x3_matrix();
    if (result < 0) {
        printf("test_det_3x3_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_det_3x3_matrix() passed.\n");
    }

    result = test_det_4x4_matrix();
    if (result < 0) {
        printf("test_det_4x4_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_det_4x4_matrix() passed.\n");
    }

    result = test_is_invertable_4x4_matrix();
    if (result < 0) {
        printf("test_is_invertable_4x4_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_is_invertable_4x4_matrix() passed.\n");
    }

    result = test_inverse_4x4_matrix();
    if (result < 0) {
        printf("test_inverse_4x4_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_inverse_4x4_matrix() passed.\n");
    }

    result = test_inverse_4x4_matrix_extra();
    if (result < 0) {
        printf("test_inverse_4x4_matrix_extra() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_inverse_4x4_matrix_extra() passed.\n");
    }

    result = test_inverse_4x4_matrix_multiplication();
    if (result < 0) {
        printf("test_inverse_4x4_matrix_multiplication() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_inverse_4x4_matrix_multiplication() passed.\n");
    }

    return num_failed;
}

int chapter_four_tests()
{
    int result = 0;
    int num_failed = 0;

    result = test_translation_matrix();
    if (result < 0) {
        printf("test_translation_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_translation_matrix() passed.\n");
    }

    result = test_translation_inversion();
    if (result < 0) {
        printf("test_translation_inversion() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_translation_inversion() passed.\n");
    }

    result = test_translation_vector();
    if (result < 0) {
        printf("test_translation_vector() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_translation_vector() passed.\n");
    }

    result = test_scaling_matrix();
    if (result < 0) {
        printf("test_scaling_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_scaling_matrix() passed.\n");
    }

    result = test_scaling_vector();
    if (result < 0) {
        printf("test_scaling_vector() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_scaling_vector() passed.\n");
    }

    result = test_scaling_inversion();
    if (result < 0) {
        printf("test_scaling_inversion() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_scaling_inversion() passed.\n");
    }

    result = test_scaling_reflection();
    if (result < 0) {
        printf("test_scaling_reflection() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_scaling_reflection() passed.\n");
    }

    result = test_rotation_x_matrix();
    if (result < 0) {
        printf("test_rotation_x_matrix() failed with code: %i\n", result);
        num_failed++;
    }
    else {
        printf("test_rotation_x_matrix() passed.\n");
    }

    return num_failed;
}