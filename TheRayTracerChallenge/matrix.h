#pragma once
#include <stdio.h>
#include <string.h>
#include "tuple.h"
#include "misc.h"

struct Matrix
{
	float* elements;
	unsigned int rows;
	unsigned int cols;
};

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

struct Matrix new_matrix_4x4_identity()
{
	float identity_values[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

	struct Matrix m = new_matrix_4x4(identity_values);

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

struct Matrix new_matrix_3x3(float* values)
{
	struct Matrix m = new_matrix(3, 3);
	int index = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			set_matrix_element(&m, i, j, values[index]);
			index++;
		}
	}

	return m;
}

int is_equal_matrix(unsigned int rows, unsigned int cols, struct Matrix* A, struct Matrix* B)
{
	if ((A->rows != rows) || (A->cols != cols) || (B->rows != rows) || (B->cols != cols)) { return -1; }

	int index = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (!is_equal_float(A->elements[index], B->elements[index])) { return 0; }
			index++;
		}
	}

	return 1;
}

struct Matrix mult_4x4_matrices(struct Matrix* A, struct Matrix* B, int *error)
{
	struct Matrix p = new_matrix(4, 4);

	if ((A->rows != 4) || (A->cols != 4) || (B->rows != 4) || (B->cols != 4)) { *error = -1;  return p; }

	float tmp_prod = 0;
	int err = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp_prod += get_matrix_element(A, i, 0, &err) * get_matrix_element(B, 0, j, &err);
			tmp_prod += get_matrix_element(A, i, 1, &err) * get_matrix_element(B, 1, j, &err);
			tmp_prod += get_matrix_element(A, i, 2, &err) * get_matrix_element(B, 2, j, &err);
			tmp_prod += get_matrix_element(A, i, 3, &err) * get_matrix_element(B, 3, j, &err);

			set_matrix_element(&p, i, j, tmp_prod);
			tmp_prod = 0;
		}
	}
	*error = 1;
	return p;
}

struct Tuple mult_4x4_matrix_tuple(struct Matrix* A, struct Tuple* B, int *error)
{
	if ((A->rows != 4) || (A->cols != 4)) { *error = -1;  return new_tuple(0,0,0,0); }
	
	float x = 0; float y = 0; float z = 0; float w = 0;

	x = (A->elements[0] * B->x) + (A->elements[1] * B->y) + (A->elements[2] * B->z) + (A->elements[3] * B->w);
	y = (A->elements[4] * B->x) + (A->elements[5] * B->y) + (A->elements[6] * B->z) + (A->elements[7] * B->w);
	z = (A->elements[8] * B->x) + (A->elements[9] * B->y) + (A->elements[10] * B->z) + (A->elements[11] * B->w);
	w = (A->elements[12] * B->x) + (A->elements[13] * B->y) + (A->elements[14] * B->z) + (A->elements[15] * B->w);

	return new_tuple(x, y, z, w);
}

void debug_print_matrix(unsigned int rows, unsigned int cols, struct Matrix* A)
{
	int error = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%f ", get_matrix_element(A, i, j, &error));
		}
		printf("\n");
	}
}