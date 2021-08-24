#pragma once
#include <stdio.h>
#include <string.h>
#include "misc.h"

struct Matrix
{
	float* elements;
	unsigned int rows;
	unsigned int cols;
};

void debug_print_matrix(unsigned int rows, unsigned int cols)
{
	//
}

struct Matrix new_matrix(unsigned int rows, unsigned int cols)
{
	struct Matrix m;
	m.rows = rows;
	m.cols = cols;
	m.elements = (float*)malloc(sizeof(float) * rows * cols);
	if (m.elements != NULL) { memset(m.elements, 0, sizeof(float) * rows * cols); }

	return m;
}

void free_matrix(struct Matrix* matrix)
{
	if (matrix->elements != NULL) { free(matrix->elements); }
}

int set_matrix_element(struct Matrix *matrix, unsigned int row, unsigned int col, float value)
{
	if (matrix->elements == NULL) { return -1; }
	if (row > (matrix->rows - 1)) { return -2; }
	if (col > (matrix->cols - 1)) { return -3; }

	int offset = (row * matrix->cols) + col;
	if (offset > (matrix->cols * matrix->rows) - 1) { return -4; }
	
	matrix->elements[offset] = value;
	return 1;
}

float get_matrix_element(struct Matrix* matrix, unsigned int row, unsigned int col, int *error)
{
	if (matrix->elements == NULL) { *error = -1; return -1; }
	if (row > (matrix->rows - 1)) { *error = -2; return -2; }
	if (col > (matrix->cols - 1)) { *error = -3; return -3; }

	int offset = (row * matrix->cols) + col;
	if (offset > (matrix->cols * matrix->rows) - 1) { *error = -4; return -4; }

	if (matrix->elements != NULL) { *error = 1;  return matrix->elements[offset]; }
	else { *error = -4; return -5; }
}

struct Matrix new_matrix_4x4(float* values)
{
	struct Matrix m = new_matrix(4, 4);
	int index = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			set_matrix_element(&m, i, j, values[index]);
			index++;
		}
	}

	return m;
}

struct Matrix new_matrix_2x2(float* values)
{
	struct Matrix m = new_matrix(2, 2);
	int index = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			set_matrix_element(&m, i, j, values[index]);
			index++;
		}
	}

	return m;
}