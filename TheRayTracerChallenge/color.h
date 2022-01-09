#pragma once
#include <stdio.h>
#include "misc.h"

struct Color
{
	float r;
	float g;
	float b;
};

void debug_print_color(struct Color *color)
{
	printf("R: %f G: %f B: %f\n", color->r, color->g, color->b);
}

int is_equal_color(struct Color *a, struct Color *b)
{
	if (!is_equal_float(a->r, b->r)) { return -1; }
	if (!is_equal_float(a->g, b->g)) { return -1; }
	if (!is_equal_float(a->b, b->b)) { return -1; }

	return 1;
}

int new_color(struct Color *color, float red, float green, float blue)
{
	color->r = red;
	color->g = green;
	color->b = blue;

	return 1;
}

int add_colors(struct Color *sum, struct Color *a, struct Color *b)
{
	sum->r = a->r + b->r;
	sum->g = a->g + b->g;
	sum->b = a->b + b->b;

	return 1;
}

int subtract_colors(struct Color *difference, struct Color *a, struct Color *b)
{
	difference->r = a->r - b->r;
	difference->g = a->g - b->g;
	difference->b = a->b - b->b;

	return 1;
}

int mult_color_scalar(struct Color *product, struct Color *a, float scalar)
{
	product->r = a->r * scalar;
	product->g = a->g * scalar;
	product->b = a->b * scalar;

	return 1;
}

int mult_colors(struct Color *product, struct Color *a, struct Color *b)
{
	struct Color color;
	product->r = a->r * b->r;
	product->g = a->g * b->g;
	product->b = a->b * b->b;

	return 1;
}