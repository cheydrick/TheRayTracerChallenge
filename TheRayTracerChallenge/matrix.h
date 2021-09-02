#pragma once
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "tuple.h"
#include "misc.h"

struct Matrix
{
	float* elements;
	unsigned int rows;
	unsigned int cols;
};

struct Matrix new_matrix(unsigned int, unsigned int);
void free_matrix(struct Matrix*);
int set_matrix_element(struct Matrix*, unsigned int, unsigned int, float);
float get_matrix_element(struct Matrix*, unsigned int, unsigned int, int*);
struct Matrix new_matrix_4x4(float*);
struct Matrix new_matrix_4x4_identity();
struct Matrix new_matrix_2x2(float*);
struct Matrix new_matrix_3x3(float*);
int is_equal_matrix(unsigned int, unsigned int, struct Matrix*, struct Matrix*);
struct Matrix mult_4x4_matrices(struct Matrix*, struct Matrix*, int*);
struct Tuple mult_4x4_matrix_tuple(struct Matrix*, struct Tuple*, int*);
struct Matrix transpose_4x4_matrix(struct Matrix*, int*);
float det_2x2_matrix(struct Matrix*, int*);
struct Matrix submatrix_3x3(struct Matrix*, unsigned int, unsigned int, int*);
struct Matrix submatrix_4x4(struct Matrix*, unsigned int, unsigned int, int*);
float minor_3x3_matrix(struct Matrix*, unsigned int, unsigned int, int*);
float cofactor_3x3_matrix(struct Matrix*, unsigned int, unsigned int, int*);
float cofactor_4x4_matrix(struct Matrix*, unsigned int, unsigned int, int*);
float det_3x3_matrix(struct Matrix*, int*);
float minor_4x4_matrix(struct Matrix*, unsigned int, unsigned int, int*);
float det_4x4_matrix(struct Matrix*, int*);
unsigned int is_invertable_4x4_matrix(struct Matrix*, int *);
struct Matrix inverse_4x4_matrix(struct Matrix*, int*);
void debug_print_matrix(unsigned int, unsigned int, struct Matrix*);

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

int set_matrix_element(struct Matrix* matrix, unsigned int row, unsigned int col, float value)
{
	if (matrix->elements == NULL) { return -1; }
	if (row > (matrix->rows - 1)) { return -2; }
	if (col > (matrix->cols - 1)) { return -3; }

	int offset = (row * matrix->cols) + col;
	if (offset > (matrix->cols * matrix->rows) - 1) { return -4; }

	matrix->elements[offset] = value;
	return 1;
}

float get_matrix_element(struct Matrix* matrix, unsigned int row, unsigned int col, int* error)
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

struct Matrix mult_4x4_matrices(struct Matrix* A, struct Matrix* B, int* error)
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

struct Tuple mult_4x4_matrix_tuple(struct Matrix* A, struct Tuple* B, int* error)
{
	if ((A->rows != 4) || (A->cols != 4)) { *error = -1;  return new_tuple(0, 0, 0, 0); }

	float x = 0; float y = 0; float z = 0; float w = 0;

	x = (A->elements[0] * B->x) + (A->elements[1] * B->y) + (A->elements[2] * B->z) + (A->elements[3] * B->w);
	y = (A->elements[4] * B->x) + (A->elements[5] * B->y) + (A->elements[6] * B->z) + (A->elements[7] * B->w);
	z = (A->elements[8] * B->x) + (A->elements[9] * B->y) + (A->elements[10] * B->z) + (A->elements[11] * B->w);
	w = (A->elements[12] * B->x) + (A->elements[13] * B->y) + (A->elements[14] * B->z) + (A->elements[15] * B->w);

	return new_tuple(x, y, z, w);
}

struct Matrix transpose_4x4_matrix(struct Matrix* A, int* error)
{
	float t_values[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	if ((A->rows != 4) || (A->cols != 4)) { *error = -1;  return new_matrix_4x4(t_values); }

	t_values[0] = A->elements[0]; t_values[1] = A->elements[4]; t_values[2] = A->elements[8]; t_values[3] = A->elements[12];
	t_values[4] = A->elements[1]; t_values[5] = A->elements[5]; t_values[6] = A->elements[9]; t_values[7] = A->elements[13];
	t_values[8] = A->elements[2]; t_values[9] = A->elements[6]; t_values[10] = A->elements[10]; t_values[11] = A->elements[14];
	t_values[12] = A->elements[3]; t_values[13] = A->elements[7]; t_values[14] = A->elements[11]; t_values[15] = A->elements[15];

	*error = 1;
	return new_matrix_4x4(t_values);
}

float det_2x2_matrix(struct Matrix* A, int* error)
{
	if ((A->rows != 2) || (A->cols != 2)) { *error = -1;  return 0; }

	*error = 1;
	return ((A->elements[0] * A->elements[3]) - (A->elements[1] * A->elements[2]));
}

struct Matrix submatrix_3x3(struct Matrix* A, unsigned int row, unsigned int col, int* error)
{
	float b_values[4] = { 0,0,0,0 };

	if ((A->rows != 3) || (A->cols != 3)) { *error = -1;  return new_matrix_2x2(b_values); }

	//
	if (row == 0 && col == 0) { b_values[0] = A->elements[4]; b_values[1] = A->elements[5]; b_values[2] = A->elements[7]; b_values[3] = A->elements[8]; }
	if (row == 0 && col == 1) { b_values[0] = A->elements[3]; b_values[1] = A->elements[5]; b_values[2] = A->elements[6]; b_values[3] = A->elements[8]; }
	if (row == 0 && col == 2) { b_values[0] = A->elements[3]; b_values[1] = A->elements[4]; b_values[2] = A->elements[6]; b_values[3] = A->elements[7]; }

	//
	if (row == 1 && col == 0) { b_values[0] = A->elements[1]; b_values[1] = A->elements[2]; b_values[2] = A->elements[7]; b_values[3] = A->elements[8]; }
	if (row == 1 && col == 1) { b_values[0] = A->elements[0]; b_values[1] = A->elements[2]; b_values[2] = A->elements[6]; b_values[3] = A->elements[8]; }
	if (row == 1 && col == 2) { b_values[0] = A->elements[0]; b_values[1] = A->elements[1]; b_values[2] = A->elements[6]; b_values[3] = A->elements[7]; }

	//
	if (row == 2 && col == 0) { b_values[0] = A->elements[1]; b_values[1] = A->elements[2]; b_values[2] = A->elements[4]; b_values[3] = A->elements[5]; }
	if (row == 2 && col == 1) { b_values[0] = A->elements[0]; b_values[1] = A->elements[2]; b_values[2] = A->elements[3]; b_values[3] = A->elements[5]; }
	if (row == 2 && col == 2) { b_values[0] = A->elements[0]; b_values[1] = A->elements[1]; b_values[2] = A->elements[3]; b_values[3] = A->elements[4]; }

	*error = 1;
	return new_matrix_2x2(b_values);
}

struct Matrix submatrix_4x4(struct Matrix* A, unsigned int row, unsigned int col, int* error)
{
	float b_values[9] = { 0,0,0,0,0,0,0,0,0 };

	if ((A->rows != 4) || (A->cols != 4)) { *error = -1;  return new_matrix_3x3(b_values); }

	//
	if (row == 0 && col == 0) {
		b_values[0] = A->elements[5]; b_values[1] = A->elements[6]; b_values[2] = A->elements[7];
		b_values[3] = A->elements[9]; b_values[4] = A->elements[10]; b_values[5] = A->elements[11];
		b_values[6] = A->elements[13]; b_values[7] = A->elements[14]; b_values[8] = A->elements[15];
	}

	if (row == 0 && col == 1) {
		b_values[0] = A->elements[4]; b_values[1] = A->elements[6]; b_values[2] = A->elements[7];
		b_values[3] = A->elements[8]; b_values[4] = A->elements[10]; b_values[5] = A->elements[11];
		b_values[6] = A->elements[12]; b_values[7] = A->elements[14]; b_values[8] = A->elements[15];
	}

	if (row == 0 && col == 2) {
		b_values[0] = A->elements[4]; b_values[1] = A->elements[5]; b_values[2] = A->elements[7];
		b_values[3] = A->elements[8]; b_values[4] = A->elements[9]; b_values[5] = A->elements[11];
		b_values[6] = A->elements[12]; b_values[7] = A->elements[13]; b_values[8] = A->elements[15];
	}

	if (row == 0 && col == 3) {
		b_values[0] = A->elements[4]; b_values[1] = A->elements[5]; b_values[2] = A->elements[6];
		b_values[3] = A->elements[8]; b_values[4] = A->elements[9]; b_values[5] = A->elements[10];
		b_values[6] = A->elements[12]; b_values[7] = A->elements[13]; b_values[8] = A->elements[14];
	}

	//
	if (row == 1 && col == 0) {
		b_values[0] = A->elements[1]; b_values[1] = A->elements[2]; b_values[2] = A->elements[3];
		b_values[3] = A->elements[9]; b_values[4] = A->elements[10]; b_values[5] = A->elements[11];
		b_values[6] = A->elements[13]; b_values[7] = A->elements[14]; b_values[8] = A->elements[15];
	}

	if (row == 1 && col == 1) {
		b_values[0] = A->elements[0]; b_values[1] = A->elements[2]; b_values[2] = A->elements[3];
		b_values[3] = A->elements[8]; b_values[4] = A->elements[10]; b_values[5] = A->elements[11];
		b_values[6] = A->elements[12]; b_values[7] = A->elements[14]; b_values[8] = A->elements[15];
	}

	if (row == 1 && col == 2) {
		b_values[0] = A->elements[0]; b_values[1] = A->elements[1]; b_values[2] = A->elements[3];
		b_values[3] = A->elements[8]; b_values[4] = A->elements[9]; b_values[5] = A->elements[11];
		b_values[6] = A->elements[12]; b_values[7] = A->elements[13]; b_values[8] = A->elements[15];
	}

	if (row == 1 && col == 3) {
		b_values[0] = A->elements[0]; b_values[1] = A->elements[1]; b_values[2] = A->elements[2];
		b_values[3] = A->elements[8]; b_values[4] = A->elements[9]; b_values[5] = A->elements[10];
		b_values[6] = A->elements[12]; b_values[7] = A->elements[13]; b_values[8] = A->elements[14];
	}

	//
	if (row == 2 && col == 0) {
		b_values[0] = A->elements[1]; b_values[1] = A->elements[2]; b_values[2] = A->elements[3];
		b_values[3] = A->elements[5]; b_values[4] = A->elements[6]; b_values[5] = A->elements[7];
		b_values[6] = A->elements[13]; b_values[7] = A->elements[14]; b_values[8] = A->elements[15];
	}

	if (row == 2 && col == 1) {
		b_values[0] = A->elements[0]; b_values[1] = A->elements[2]; b_values[2] = A->elements[3];
		b_values[3] = A->elements[4]; b_values[4] = A->elements[6]; b_values[5] = A->elements[7];
		b_values[6] = A->elements[12]; b_values[7] = A->elements[14]; b_values[8] = A->elements[15];
	}

	if (row == 2 && col == 2) {
		b_values[0] = A->elements[0]; b_values[1] = A->elements[1]; b_values[2] = A->elements[3];
		b_values[3] = A->elements[4]; b_values[4] = A->elements[5]; b_values[5] = A->elements[7];
		b_values[6] = A->elements[12]; b_values[7] = A->elements[13]; b_values[8] = A->elements[15];
	}

	if (row == 2 && col == 3) {
		b_values[0] = A->elements[0]; b_values[1] = A->elements[1]; b_values[2] = A->elements[2];
		b_values[3] = A->elements[4]; b_values[4] = A->elements[5]; b_values[5] = A->elements[6];
		b_values[6] = A->elements[12]; b_values[7] = A->elements[13]; b_values[8] = A->elements[14];
	}

	//
	if (row == 3 && col == 0) {
		b_values[0] = A->elements[1]; b_values[1] = A->elements[2]; b_values[2] = A->elements[3];
		b_values[3] = A->elements[5]; b_values[4] = A->elements[6]; b_values[5] = A->elements[7];
		b_values[6] = A->elements[9]; b_values[7] = A->elements[10]; b_values[8] = A->elements[11];
	}

	if (row == 3 && col == 1) {
		b_values[0] = A->elements[0]; b_values[1] = A->elements[2]; b_values[2] = A->elements[3];
		b_values[3] = A->elements[4]; b_values[4] = A->elements[6]; b_values[5] = A->elements[7];
		b_values[6] = A->elements[8]; b_values[7] = A->elements[10]; b_values[8] = A->elements[11];
	}

	if (row == 3 && col == 2) {
		b_values[0] = A->elements[0]; b_values[1] = A->elements[1]; b_values[2] = A->elements[3];
		b_values[3] = A->elements[4]; b_values[4] = A->elements[5]; b_values[5] = A->elements[7];
		b_values[6] = A->elements[8]; b_values[7] = A->elements[9]; b_values[8] = A->elements[11];
	}

	if (row == 3 && col == 3) {
		b_values[0] = A->elements[0]; b_values[1] = A->elements[1]; b_values[2] = A->elements[2];
		b_values[3] = A->elements[4]; b_values[4] = A->elements[5]; b_values[5] = A->elements[6];
		b_values[6] = A->elements[8]; b_values[7] = A->elements[9]; b_values[8] = A->elements[10];
	}

	*error = 1;
	return new_matrix_3x3(b_values);

}

float minor_3x3_matrix(struct Matrix* A, unsigned int row, unsigned int col, int* error)
{
	struct Matrix B = submatrix_3x3(A, row, col, error);
	float det = det_2x2_matrix(&B, error);

	*error = 1;
	return det;
}

float cofactor_3x3_matrix(struct Matrix* A, unsigned int row, unsigned int col, int* error)
{
	int local_error = 0;

	float minor = minor_3x3_matrix(A, row, col, &local_error);
	if (local_error != 1) { *error = -1; return 0; }

	if ((row + col) % 2 != 0) { minor = minor * -1; }

	*error = 1;
	return minor;
}

float cofactor_4x4_matrix(struct Matrix* A, unsigned int row, unsigned int col, int* error)
{
	int local_error = 0;

	float minor = minor_4x4_matrix(A, row, col, &local_error);
	if (local_error != 1) { *error = -1; return 0; }

	if ((row + col) % 2 != 0) { minor = minor * -1; }

	*error = 1;
	return minor;
}

float det_3x3_matrix(struct Matrix* A, int* error)
{
	if ((A->rows != 3) || (A->cols != 3)) { *error = -1;  return 0; }

	int local_error = 0;
	float sum = 0;

	sum += get_matrix_element(A, 0, 0, &local_error) * cofactor_3x3_matrix(A, 0, 0, &local_error);
	sum += get_matrix_element(A, 0, 1, &local_error) * cofactor_3x3_matrix(A, 0, 1, &local_error);
	sum += get_matrix_element(A, 0, 2, &local_error) * cofactor_3x3_matrix(A, 0, 2, &local_error);

	*error = 1;
	return sum;
}

float minor_4x4_matrix(struct Matrix* A, unsigned int row, unsigned int col, int* error)
{
	if ((A->rows != 4) || (A->cols != 4)) { *error = -1;  return 0; }

	int local_error = 0;
	struct Matrix submatrix = submatrix_4x4(A, row, col, &local_error);
	if (local_error != 1) { *error = -2; return 0; }

	float det = det_3x3_matrix(&submatrix, &local_error);
	if (local_error != 1) { *error = -3; return 0; }

	*error = 1;
	return det;
}

float det_4x4_matrix(struct Matrix* A, int* error)
{
	if ((A->rows != 4) || (A->cols != 4)) { *error = -1;  return 0; }

	int local_error = 0;
	float sum = 0;

	sum += get_matrix_element(A, 0, 0, &local_error) * cofactor_4x4_matrix(A, 0, 0, &local_error);
	sum += get_matrix_element(A, 0, 1, &local_error) * cofactor_4x4_matrix(A, 0, 1, &local_error);
	sum += get_matrix_element(A, 0, 2, &local_error) * cofactor_4x4_matrix(A, 0, 2, &local_error);
	sum += get_matrix_element(A, 0, 3, &local_error) * cofactor_4x4_matrix(A, 0, 3, &local_error);

	*error = 1;
	return sum;
}

unsigned int is_invertable_4x4_matrix(struct Matrix* A, int *error)
{
	if ((A->rows != 4) || (A->cols != 4)) { *error = -1;  return 0; }

	int local_error = 0;
	float det = det_4x4_matrix(A, &local_error);

	if (local_error != 1) { *error = -2; return 0; }

	if (is_equal_float(det, 0.0)) { return 0; }
	else { return 1; }
}

struct Matrix inverse_4x4_matrix(struct Matrix* A, int* error)
{
	float cofactor_matrix_values[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	float inverse_matrix_values[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	// Construct cofactor matrix values
	int local_error = 0;
	int cofactor_values_index = 0;
	float tmp_cofactor = 0;
	for (int i = 0; i < A->rows; i++)
	{
		for (int j = 0; j < A->cols; j++)
		{
			tmp_cofactor = cofactor_4x4_matrix(A, i, j, &local_error);
			cofactor_matrix_values[cofactor_values_index] = tmp_cofactor;
			cofactor_values_index++;
		}
	}

	struct Matrix cofactor_matrix = new_matrix_4x4(cofactor_matrix_values);
	
	// Transpose the cofactor matrix
	struct Matrix transposed_cofactor_matrix = transpose_4x4_matrix(&cofactor_matrix, &local_error);

	float det = det_4x4_matrix(A, &local_error);

	int inverse_values_index = 0;
	for (int i = 0; i < A->rows; i++)
	{
		for (int j = 0; j < A->cols; j++)
		{
			inverse_matrix_values[inverse_values_index] = get_matrix_element(&transposed_cofactor_matrix, i, j, &local_error) / det;
			inverse_values_index++;
		}
	}

	struct Matrix inverse_matrix = new_matrix_4x4(inverse_matrix_values);

	free_matrix(&cofactor_matrix);
	free_matrix(&transposed_cofactor_matrix);

	*error = 1;
	return inverse_matrix;
}

struct Matrix new_translation_matrix(float x, float y, float z)
{
	struct Matrix tmp_translation_matrix = new_matrix_4x4_identity();
	tmp_translation_matrix.elements[3] = x;
	tmp_translation_matrix.elements[7] = y;
	tmp_translation_matrix.elements[11] = z;

	return tmp_translation_matrix;
}

struct Matrix new_scaling_matrix(float x, float y, float z)
{
	struct Matrix tmp_scaling_matrix = new_matrix_4x4_identity();
	tmp_scaling_matrix.elements[0] = x;
	tmp_scaling_matrix.elements[5] = y;
	tmp_scaling_matrix.elements[10] = z;

	return tmp_scaling_matrix;
}

struct Matrix new_rotation_x_matrix(float radians)
{
	struct Matrix tmp_rotation_matrix = new_matrix_4x4_identity();

	tmp_rotation_matrix.elements[5] = cos(radians);
	tmp_rotation_matrix.elements[6] = -1.0 * sin(radians);
	tmp_rotation_matrix.elements[9] = sin(radians);
	tmp_rotation_matrix.elements[10] = cos(radians);

	return tmp_rotation_matrix;
}

struct Matrix new_rotation_y_matrix(float radians)
{
	struct Matrix tmp_rotation_matrix = new_matrix_4x4_identity();

	tmp_rotation_matrix.elements[0] = cos(radians);
	tmp_rotation_matrix.elements[2] = sin(radians);
	tmp_rotation_matrix.elements[8] = -1 * sin(radians);
	tmp_rotation_matrix.elements[10] = cos(radians);

	return tmp_rotation_matrix;
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