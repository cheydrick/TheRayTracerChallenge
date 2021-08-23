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

	// Storage for RGB values converted from 0.0-1.0 to 0-255
	int tmp_r = 0; int tmp_b = 0; int tmp_g = 0;
	// Storage for converting RGB values to text prior to being written
	char tmp_data_r[8]; char tmp_data_g[8]; char tmp_data_b[8]; char tmp_data_rgb[24];
	// Index value for Canvas.canvas array of Color structs
	int canvas_index = 0;

	int line_char_length = 0;
	
	// Go through each Canvas.canvas Color struct and write RGB data in PPM format
	for (int y = 0; y < canvas.height; y++)
	{
		for (int x = 0; x < canvas.width; x++)
		{
			// Convert RGB values from 0.0-1.0 to 0-255, clamping when necessary
			tmp_r = (int)(roundf(canvas.canvas[canvas_index].r * 255.0)); if (tmp_r < 0) { tmp_r = 0; } if (tmp_r > 255) { tmp_r = 255; }
			tmp_g = (int)(roundf(canvas.canvas[canvas_index].g * 255.0)); if (tmp_g < 0) { tmp_g = 0; } if (tmp_g > 255) { tmp_g = 255; }
			tmp_b = (int)(roundf(canvas.canvas[canvas_index].b * 255.0)); if (tmp_b < 0) { tmp_b = 0; } if (tmp_b > 255) { tmp_b = 255; }

			// Clear temporary RGB text array
			memset(tmp_data_rgb, 0, 24);

			int tmp_data_rgb_len = 24;
			int offset = 0;

			offset = sprintf_s(tmp_data_rgb, tmp_data_rgb_len, "%i", tmp_r);
			offset += sprintf_s(tmp_data_rgb + offset, tmp_data_rgb_len - offset, "%s", " ");
			offset += sprintf_s(tmp_data_rgb + offset, tmp_data_rgb_len - offset, "%i", tmp_g);
			offset += sprintf_s(tmp_data_rgb + offset, tmp_data_rgb_len - offset, "%s", " ");
			offset += sprintf_s(tmp_data_rgb + offset, tmp_data_rgb_len - offset, "%i", tmp_b);
			// If Color being written is the last one in the row, don't write a space. Otherwise, do.
			if (x != canvas.width - 1) { offset += sprintf_s(tmp_data_rgb + offset, tmp_data_rgb_len - offset, "%s", " "); }

			if (line_char_length + strlen(tmp_data_rgb) > 70) { fwrite("\n", 1, 1, file); line_char_length = 0; }
			else { line_char_length += strlen(tmp_data_rgb); }
			
			fwrite(tmp_data_rgb, strlen(tmp_data_rgb), 1, file);

			canvas_index++;
		}
		line_char_length = 0;
		// If Color being written is the last one, don't write an extra newline. Otherwise, do.
		if (y != canvas.height - 1) { fwrite("\n", 1, 1, file); }
	}

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