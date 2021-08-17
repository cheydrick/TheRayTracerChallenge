#pragma once
#include <stdio.h>
#include "misc.h"

struct Color
{
	float r;
	float g;
	float b;
};

void debug_print_color(struct Color color)
{
	printf("R: %f G: %f B: %f\n", color.r, color.g, color.b);
}

int is_equal_color(struct Color a, struct Color b)
{
	if (!is_equal_float(a.r, b.r)) { return -1; }
	if (!is_equal_float(a.g, b.g)) { return -1; }
	if (!is_equal_float(a.b, b.b)) { return -1; }

	return 1;
}

struct Color new_color(float red, float green, float blue)
{
	struct Color color;
	color.r = red;
	color.g = green;
	color.b = blue;

	return color;
}

struct Color add_colors(struct Color a, struct Color b)
{
	struct Color color;
	color.r = a.r + b.r;
	color.g = a.g + b.g;
	color.b = a.b + b.b;

	return color;
}

struct Color subtract_colors(struct Color a, struct Color b)
{
	struct Color color;
	color.r = a.r - b.r;
	color.g = a.g - b.g;
	color.b = a.b - b.b;

	return color;
}

struct Color mult_color_scalar(struct Color a, float scalar)
{
	struct Color color;
	color.r = a.r * scalar;
	color.g = a.g * scalar;
	color.b = a.b * scalar;

	return color;
}

struct Color mult_colors(struct Color a, struct Color b)
{
	struct Color color;
	color.r = a.r * b.r;
	color.g = a.g * b.g;
	color.b = a.b * b.b;

	return color;
}