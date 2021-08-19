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

struct Color get_pixel(struct Canvas canvas, unsigned int x, unsigned int y)
{
	if (canvas.canvas == NULL) { return new_color(1, 1, 1); }
	if (x > (canvas.width - 1)) { return new_color(1, 1, 1); }
	if (y > (canvas.height - 1)) { return new_color(1, 1, 1); }

	unsigned int canvas_array_index = (y * canvas.width) + x;

	return canvas.canvas[canvas_array_index];
}

int set_pixel(struct Canvas* canvas, unsigned int x, unsigned int y, struct Color color)
{
	if (canvas->canvas == NULL) { return -1; }
	if (x > (canvas->width - 1)) { return -2; }
	if (y > (canvas->height - 1)) { return -3; }

	unsigned int canvas_array_index = (y * canvas->width) + x;

	canvas->canvas[canvas_array_index] = color;

	return 1;
}

int set_all_pixels(struct Canvas* canvas, struct Color color)
{
	int res = 0;
	for (int y = 0; y < canvas->height; y++)
	{
		for (int x = 0; x < canvas->width; x++)
		{
			res = set_pixel(canvas, x, y, color);
			if (res != 1) { return res; }
		}
	}
	return 1;
}

int write_ppm(struct Canvas canvas, const char* filename)
{
	FILE* file;
	errno_t err = fopen_s(&file, filename, "w");
	if (err) { printf("Failed to open file %s\n", filename); return -1; }

	// Generate and write the header
	char header[64] = { 0 };
	sprintf_s(header, 64, "P3\n%i %i\n255\n", canvas.width, canvas.height);
	if (file != NULL) { fwrite(header, strlen(header), 1, file); }

	// Write canvas data
	// TBD
	
	// Write newline and close file
	if (file != NULL) { fwrite("\n", 1, 1, file); }
	if (file != NULL) { fclose(file); }
	return 1;
}

char* read_ppm(const char* filename, int* buffer_size)
{
	FILE* file;
	errno_t err = fopen_s(&file, filename, "r");
	if (err) { printf("Failed to open file %s\n", filename); return NULL; }

	// Get the file length
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = (char*)malloc((size_t)length);
	if (buffer == NULL)
	{
		printf("Couldn't allocate buffer in read_ppm()\n");
		return NULL;
	}
	memset(buffer, 0, length);

	int read = fread_s(buffer, length, 1, length, file);
	if (read == 0)
	{
		printf("Zero bytes returned from read_ppm.\n");
		free(buffer);
		return NULL;
	}
	*buffer_size = read;
	fclose(file);
	return buffer;
}