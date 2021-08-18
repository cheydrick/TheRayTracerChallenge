#pragma once
#include <stdlib.h>
#include <string.h>
#include "color.h"


struct Canvas
{
	struct Color* canvas;
	unsigned int width;
	unsigned int height;
};

struct Canvas new_canvas(unsigned int width, unsigned int height)
{
	struct Canvas canvas;
	canvas.canvas = (struct Color*)malloc(sizeof(struct Color) * width * height);
	canvas.width = width;
	canvas.height = height;

	if (canvas.canvas == NULL) { return canvas; }

	unsigned int canvas_array_length = width * height;
	for (int i = 0; i < canvas_array_length; i++)
	{
		canvas.canvas[i] = new_color(0, 0, 0);
	}

	return canvas;
}

void debug_print_canvas(struct Canvas canvas)
{
	if (canvas.canvas == NULL)
	{
		printf("Canvas array is NULL.\n"); return;
	}

	int canvas_index = 0;
	for (int y = 0; y < canvas.height; y++)
	{
		for (int x = 0; x < canvas.width; x++)
		{
			printf("X:%i Y:%i ", x, y);
			debug_print_color(canvas.canvas[canvas_index]);
			canvas_index++;
		}
	}
}

void free_canvas(struct Canvas* canvas)
{
	if (canvas->canvas != NULL)
	{
		free(canvas->canvas);
		canvas->canvas = NULL;
	}
}