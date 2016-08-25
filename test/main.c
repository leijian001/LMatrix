#include    <stdio.h>
#include    "../matrix.h"

void matrix_print(matrix_t *m)
{
	unsigned int i, j;

	for(i=0; i<m->row; i++)
	{
		for(j=0; j<m->col; j++)
			printf("%f    ", MATRIX(m, i, j));
		putchar('\n');
	}
}

float table[][4] =
{
	{1, 2, 3, 4},
	{6, 5, 4, 8},
	{8, 7, 9, 6},
	{2, 3, 4, 1}
};

int main(int argc, char *argv[])
{
	matrix_t m, y, mul;

	matrix_init(&m);
	matrix_init(&y);
	matrix_init(&mul);

	matrix_reshape(&m, 4, 4);

	for(int i=0; i<m.row; i++)
	{
		for(int j=0; j<m.col; j++)
		{
			matrix_set(&m, i, j, table[i][j]);
		}
	}

	matrix_inv(&y, &m);

	printf("inv:\n");
	matrix_print(&y);

	matrix_matmul(&mul, &m, &y);

	printf("mul:\n");
	matrix_print(&mul);

	matrix_release(&m);

	return 0;
}
