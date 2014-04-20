#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#if 0
#include <stdio.h>
static void matrix_print(struct matrix *m)
{
	unsigned int i, j;

	for(i=0; i<m->row; i++)
	{
		for(j=0; j<m->column; j++)
			printf("%f    ", MATRIX(m, i, j));
		putchar('\n');
	}
}
#endif

static inline double my_abs(double x)
{
	return (x<0)? -x:x;
}

void matrix_swap_row(struct matrix *m, unsigned int i, unsigned int j)
{
	unsigned int k;
	double tmp;

	if((i<m->row) && (j<m->row))
	{
		for(k=0; k<m->column; k++)
		{
			tmp = MATRIX(m, i, k);
			MATRIX(m, i, k) = MATRIX(m, j, k);
			MATRIX(m, j, k) = tmp;
		}
	}
}
void matrix_swap_column(struct matrix *m, unsigned int i, unsigned int j)
{
	unsigned int k;
	double tmp;

	if((i<m->column) && (j<m->column))
	{
		for(k=0; k<m->column; k++)
		{
			tmp = MATRIX(m, k, i);
			MATRIX(m, k, i) = MATRIX(m, k, j);
			MATRIX(m, k, j) = tmp;
		}
	}
}

void matrix_mov(struct matrix *to, struct matrix *from)
{
	unsigned int i, j;

	to->row = from->row;
	to->column = from->column;

	for(i=0; i<from->row; i++)
		for(j=0; j<from->column; j++)
		{
			MATRIX(to, i, j) = MATRIX(from, i, j);
		}
}

void matrix_transpose(struct matrix *to, struct matrix *from)
{
	unsigned int i, j;

	to->row = from->column;
	to->column = from->row;

	for(i=0; i<from->row; i++)
	{
		for(j=0; j<from->column; j++)
			MATRIX(to, j, i) = MATRIX(from, i, j);
	}
}

void matrix_add(struct matrix *sum, struct matrix *a, struct matrix *b)
{
	unsigned int i, j;

	if((a->row==b->row) && (a->column==b->column))
	{
		sum->row = a->row;
		sum->column = a->column;

		for(i=0; i<a->row; i++)
		{
			for(j=0; j<a->column; j++)
			{
				MATRIX(sum, i, j) = MATRIX(a, i, j) + MATRIX(b, i, j);
			}
		}
	}
}

void matrix_sub(struct matrix *sub, struct matrix *a, struct matrix *b)
{
	unsigned int i, j;

	if((a->row==b->row) && (a->column==b->column))
	{
		sub->row = a->row;
		sub->column = a->column;

		for(i=0; i<a->row; i++)
		{
			for(j=0; j<a->column; j++)
			{
				MATRIX(sub, i, j) = MATRIX(a, i, j) - MATRIX(b, i, j);
			}
		}
	}
}

int matrix_mul(struct matrix *mul, struct matrix *a, struct matrix *b)
{
	unsigned int i, j, k;

	if(a->column == b->row)
	{
		mul->row = a->row;
		mul->column = b->column;

		for(i=0; i<mul->row; i++)
		{
			for(j=0; j<mul->column; j++)
			{
				MATRIX(mul, i, j) = 0;

				for(k=0; k<a->column; k++)
				{
					MATRIX(mul, i, j) += MATRIX(a, i, k) * MATRIX(b, k, j);
				}
			}
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

int matrix_inv(struct matrix *inv, struct matrix *a)
{
	int i, j, k;

	unsigned int is[a->row];
	unsigned int js[a->row];
	double max = my_abs(MATRIX(a, 0, 0));

	if(a->row != a->column)
	{
		return -2;
	}

	matrix_mov(inv, a);

	for(k=0; k<inv->row; k++)
	{

		//step 1, 全选主元
		max = MATRIX(inv, k, k);
		is[k] = k;
		js[k] = k;
		for(i=k; i<inv->row; i++)
		{
			for(j=k; j<inv->row; j++)
			{
				if(max < my_abs(MATRIX(inv, i, j)))
				{
					max = my_abs(MATRIX(inv, i, j));
					is[k] = i;
					js[k] = j;
				}
			}
		}

		//无逆矩阵
		if(max < 0.0001)
		{
			return -1;
		}

		//交换
		if(is[k] != k)
		{
			matrix_swap_row(inv, k, is[k]);
		}
		if(js[k] != k)
		{
			matrix_swap_column(inv, k, js[k]);
		}

		MATRIX(inv, k, k) = 1 / MATRIX(inv, k, k);

		for(j=0; j<inv->column; j++)
		{
			if(j != k)
			{
				MATRIX(inv, k, j) *= MATRIX(inv, k, k);
			}
		}
		for(i=0; i<inv->row; i++)
		{
			if(i != k)
			{
				for(j=0; j<inv->column; j++)
				{
					if(j != k)
					{
						MATRIX(inv, i, j) -= MATRIX(inv, i, k) * MATRIX(inv, k, j);
					}
				}
			}
		}
		for(i=0; i<inv->row; i++)
		{
			if(i != k)
			{
				MATRIX(inv, i, k) *= (-MATRIX(inv, k, k));
			}
		}

	}

	//恢复
	//本来 row <-> is[k], column <-> js[k]
	//恢复时：row <-> js[k], column <-> is[k]
	for(k=inv->row-1; k>=0; k--)
	{
		if(js[k] != k)
		{
			matrix_swap_column(inv, k, is[k]);
		}
		if(is[k] != k)
		{
			matrix_swap_row(inv, k, js[k]);
		}
	}

	return 0;
}


int matrix_constructor(struct matrix *m, unsigned int row, unsigned int column)
{
	if(NULL == m)
	{
		return -1;
	}

	m->row = row;
	m->column = column;
	m->matrix = malloc(row * column * sizeof(double));

	return (m->matrix)? 0:-1;
}

void matrix_destructor(struct matrix *m)
{
	if(NULL == m)
	{
		return;
	}

	m->row = 0;
	m->column = 0;

	if(NULL != m->matrix)
	{
		free(m->matrix);
	}
}
