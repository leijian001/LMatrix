#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

#define VARIABLE_ARRAY		//! 支持可变长数组

#define FABS(x)		mathop(fabs)(x)


void matrix_map(matrix_t *s, matrix_t *x, real_t (*f)(real_t))
{
	unsigned int i, j;

	LM_ASSERT(a->row == b->row);
	LM_ASSERT(a->col == b->col);

	matrix_reshape(s, x->row, x->col);

	for(i=0; i<x->row; i++)
		for(j=0; j<x->col; j++)
			MATRIX(s, i, j) = f(MATRIX(x, i, j));
}

void matrix_swap_row(matrix_t *m, unsigned int i, unsigned int j)
{
	unsigned int k;
	real_t tmp;

	LM_ASSERT(i < m->row);
	LM_ASSERT(j < m->row);

	for(k=0; k<m->col; k++)
	{
		tmp = MATRIX(m, i, k);
		MATRIX(m, i, k) = MATRIX(m, j, k);
		MATRIX(m, j, k) = tmp;
	}
}

void matrix_swap_col(matrix_t *m, unsigned int i, unsigned int j)
{
	unsigned int k;
	real_t tmp;

	LM_ASSERT(i < m->col);
	LM_ASSERT(j < m->col);

	for(k=0; k<m->row; k++)
	{
		tmp = MATRIX(m, k, i);
		MATRIX(m, k, i) = MATRIX(m, k, j);
		MATRIX(m, k, j) = tmp;
	}
}

void matrix_copy(matrix_t *to, matrix_t *from)
{
	unsigned int i, j;

	matrix_reshape(to, from->row, from->col);

	for(i=0; i<from->row; i++)
		for(j=0; j<from->col; j++)
			MATRIX(to, i, j) = MATRIX(from, i, j);
}

void matrix_transpose(matrix_t *to, matrix_t *from)
{
	unsigned int i, j;

	matrix_reshape(to, from->col, from->row);

	for(i=0; i<from->row; i++)
		for(j=0; j<from->col; j++)
			MATRIX(to, j, i) = MATRIX(from, i, j);
}

void matrix_eye(matrix_t *m, unsigned int order)
{
	int i, j;

	matrix_reshape(m, order, order);

	for(i=0; i<order; i++)
		for(j=0; j<order; j++)
			MATRIX(m, i, j) = 0;

	for(i=0; i<order; i++)
		MATRIX(m, i, i) = 1;
}

void matrix_add(matrix_t *sum, matrix_t *a, matrix_t *b)
{
	unsigned int i, j;

	LM_ASSERT(a->row == b->row);
	LM_ASSERT(a->col == b->col);

	matrix_reshape(sum, a->row, a->col);

	for(i=0; i<a->row; i++)
		for(j=0; j<a->col; j++)
			MATRIX(sum, i, j) = MATRIX(a, i, j) + MATRIX(b, i, j);
}

void matrix_sub(matrix_t *sub, matrix_t *a, matrix_t *b)
{
	unsigned int i, j;

	LM_ASSERT(a->row == b->row);
	LM_ASSERT(a->col == b->col);

	matrix_reshape(sub, a->row, a->col);

	for(i=0; i<a->row; i++)
		for(j=0; j<a->col; j++)
			MATRIX(sub, i, j) = MATRIX(a, i, j) - MATRIX(b, i, j);
}

void matrix_mul_(matrix_t *mul, matrix_t *x, real_t k)
{
	unsigned int i, j;

	LM_ASSERT(a->row == b->row);
	LM_ASSERT(a->col == b->col);

	matrix_reshape(mul, x->row, x->col);

	for(i=0; i<x->row; i++)
		for(j=0; j<x->col; j++)
			MATRIX(mul, i, j) = k * MATRIX(x, i, j);
}

void matrix_mul(matrix_t *mul, matrix_t *a, matrix_t *b)
{
	unsigned int i, j;

	LM_ASSERT(a->row == b->row);
	LM_ASSERT(a->col == b->col);

	matrix_reshape(mul, a->row, a->col);

	for(i=0; i<a->row; i++)
		for(j=0; j<a->col; j++)
			MATRIX(mul, i, j) = MATRIX(a, i, j) * MATRIX(b, i, j);
}

void matrix_div(matrix_t *div, matrix_t *a, matrix_t *b)
{
	unsigned int i, j;

	LM_ASSERT(a->row == b->row);
	LM_ASSERT(a->col == b->col);

	matrix_reshape(div, a->row, a->col);

	for(i=0; i<a->row; i++)
		for(j=0; j<a->col; j++)
			MATRIX(div, i, j) = MATRIX(a, i, j) / MATRIX(b, i, j);
}

void matrix_pow(matrix_t *p, matrix_t *x, real_t y)
{
	unsigned int i, j;

	LM_ASSERT(a->row == b->row);
	LM_ASSERT(a->col == b->col);

	matrix_reshape(p, x->row, x->col);

	for(i=0; i<x->row; i++)
		for(j=0; j<x->col; j++)
			MATRIX(p, i, j) = mathop(pow)(MATRIX(x, i, j), y);
}

void matrix_sqrt(matrix_t *s, matrix_t *x)
{
	matrix_map(s, x, mathop(sqrt));
}

/**
 * @brief 自然对数
 */
void matrix_ln(matrix_t *s, matrix_t *x)
{
	matrix_map(s, x, mathop(log));
}

/**
 * @brief 以10为底对数
 */
void matrix_log(matrix_t *s, matrix_t *x)
{
	matrix_map(s, x, mathop(log10));
}

/**
 * @brief e的x次方
 */
void matrix_exp(matrix_t *s, matrix_t *x)
{
	matrix_map(s, x, mathop(exp));
}

void matrix_sin(matrix_t *s, matrix_t *x)
{
	matrix_map(s, x, mathop(sin));
}

void matrix_cos(matrix_t *s, matrix_t *x)
{
	matrix_map(s, x, mathop(cos));
}

void matrix_tan(matrix_t *s, matrix_t *x)
{
	matrix_map(s, x, mathop(tan));
}

void matrix_matmul(matrix_t *mul, matrix_t *a, matrix_t *b)
{
	unsigned int i, j, k;

	LM_ASSERT(a->col == b->row);

	matrix_reshape(mul, a->row, b->col);

	for(i=0; i<mul->row; i++)
	{
		for(j=0; j<mul->col; j++)
		{
			MATRIX(mul, i, j) = 0;

			for(k=0; k<a->col; k++)
			{
				MATRIX(mul, i, j) += MATRIX(a, i, k) * MATRIX(b, k, j);
			}
		}
	}
}

int matrix_inv(matrix_t *inv, matrix_t *a)
{
	int i, j, k;
	int ret = 0;

	//! 必须是方阵
	LM_ASSERT(a->row == a->col);

#ifdef VARIABLE_ARRAY
	unsigned int is[a->row];
	unsigned int js[a->col];
#else
	unsigned int *is = malloc(a->row * sizeof(unsigned int));
	unsigned int *js = malloc(a->col * sizeof(unsigned int));
#endif
	real_t max;

	matrix_reshape(inv, a->row, a->col);

	matrix_copy(inv, a);

	for(k=0; k<inv->row; k++)
	{
		//step 1, 全选主元
		max = 0;
		is[k] = k;
		js[k] = k;

		for(i=k; i<inv->row; i++)
		{
			for(j=k; j<inv->col; j++)
			{
				if(max < FABS(MATRIX(inv, i, j)))
				{
					max = FABS(MATRIX(inv, i, j));
					is[k] = i;
					js[k] = j;
				}
			}
		}

		if(max < 0.0001)
		{	//! 无逆矩阵
			ret = -1;
			goto end;
		}

		//交换
		if(is[k] != k)
		{
			matrix_swap_row(inv, k, is[k]);
		}
		if(js[k] != k)
		{
			matrix_swap_col(inv, k, js[k]);
		}

		MATRIX(inv, k, k) = 1 / MATRIX(inv, k, k);

		for(j=0; j<inv->col; j++)
		{
			if(j != k)
				MATRIX(inv, k, j) *= MATRIX(inv, k, k);
		}
		for(i=0; i<inv->row; i++)
		{
			if(i != k)
			{
				for(j=0; j<inv->col; j++)
				{
					if(j != k)
						MATRIX(inv, i, j) -= MATRIX(inv, i, k) * MATRIX(inv, k, j);
				}
			}
		}
		for(i=0; i<inv->row; i++)
		{
			if(i != k)
				MATRIX(inv, i, k) *= -MATRIX(inv, k, k);
		}

	}

	//恢复
	//本来 row <-> is[k], column <-> js[k]
	//恢复时：row <-> js[k], column <-> is[k]
	for(k=inv->row-1; k>=0; k--)
	{
		if(js[k] != k)
		{
			matrix_swap_row(inv, k, js[k]);
		}
		if(is[k] != k)
		{
			matrix_swap_col(inv, k, is[k]);
		}
	}

end:
#ifndef VARIABLE_ARRAY
	free(is);
	free(js);
#endif
	return ret;;
}

void matrix_init(matrix_t *m)
{
	LM_ASSERT(m != NULL);

	m->m = NULL;
	m->row = m->col = 0;
}

void matrix_init_with_shape(matrix_t *m, unsigned int row, unsigned int col)
{
	LM_ASSERT(m != NULL);
	LM_ASSERT(row != 0);
	LM_ASSERT(col != 0);

	m->m = malloc(row * col * sizeof(real_t));
	if (m->m != NULL)
	{
		m->row = row;
		m->col = col;
	}
	else
	{
		m->row = m->col = 0;
	}
}

int matrix_reshape(matrix_t *m, unsigned int row, unsigned int col)
{
	LM_ASSERT(m != NULL);
	LM_ASSERT(row != 0);
	LM_ASSERT(col != 0);

	if (row * col == m->row * m->col)
	{
		m->row = row;
		m->col = col;
	}
	else
	{
		if (m->m != NULL)
			free(m->m);

		m->m = malloc(row * col * sizeof(real_t));
		if (m->m != NULL)
		{
			m->row = row;
			m->col = col;
		}
		else
		{
			m->row = m->col = 0;
			return -1;
		}
	}

	return 0;
}

void matrix_release(matrix_t *m)
{
	if(m->m != NULL)
	{
		free(m->m);

		m->m = NULL;
		m->row = m->col = 0;
	}
}

real_t matrix_get(matrix_t *m, unsigned int row, unsigned int col)
{
	return MATRIX(m, row, col);
}

void matrix_set(matrix_t *m, unsigned int row, unsigned int col, real_t x)
{
	MATRIX(m, row, col) = x;
}
