#ifndef __MATRIX_H__
#define __MATRIX_H__

struct matrix
{
	unsigned int row;
	unsigned int column;
	double *matrix;
};

#define MATRIX(m, i, j) (*((m)->matrix + (i)*(m)->column + (j)))

void matrix_swap_row(struct matrix *m, unsigned int i, unsigned int j);
void matrix_swap_column(struct matrix *m, unsigned int i, unsigned int j);

void matrix_mov(struct matrix *to, struct matrix *from);
void matrix_transpose(struct matrix *to, struct matrix *from);
void matrix_add(struct matrix *sum, struct matrix *a, struct matrix *b);
void matrix_sub(struct matrix *sub, struct matrix *a, struct matrix *b);
int matrix_mul(struct matrix *mul, struct matrix *a, struct matrix *b);
int matrix_inv(struct matrix *inv, struct matrix *a);

#endif
