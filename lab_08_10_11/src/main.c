#include "mtr_alloc.h"
#include "mtr_io.h"
#include "errors.h"
#include "constants.h"
#include "mtr_op.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc != ARGS_LEN_SUM_MULTIPLY && argc != ARGS_LEN_SOLVE)
	{
		return ERR_ARGS;
	}

	int rc = ERR_OK;
	double **mtr1 = NULL, **mtr2 = NULL, **mtr3 = NULL;
	size_t rows1 = 0, columns1 = 0, rows2 = 0, columns2 = 0, rows3 = 0, columns3 = 0;
	if (argc == ARGS_LEN_SUM_MULTIPLY)
	{
		char *action = argv[ARGS_ACTION_INDEX];

		rc = matrix_create(argv[ARGS_FIRST_FILE_MATRIX_INDEX], &mtr1, &rows1, &columns1);

		rc = matrix_create(argv[ARGS_SECOND_FILE_MATRIX_INDEX], &mtr2, &rows2, &columns2);

		if (rc == ERR_OK && strcmp(action, MATRIX_SUM) == 0)
		{
			rc = sum_matrix((const double**) mtr1, rows1, columns1, (const double**) mtr2, rows2, columns2, &mtr3, &rows3, &columns3);
		}
		else if (rc == ERR_OK && strcmp(action, MATRIX_MULTI) == 0)
		{
			rc = multiply_matrix((const double**) mtr1, rows1, columns1, (const double**) mtr2, rows2, columns2, &mtr3, &rows3, &columns3);
		}
		else 
		{
			rc = ERR_ARGS;
		}
	}
	else if (argc == ARGS_LEN_SOLVE && (strcmp(argv[ARGS_ACTION_INDEX], MATRIX_SOLVE) == 0))
	{
		rc = matrix_create(argv[ARGS_FIRST_FILE_MATRIX_INDEX], &mtr1, &rows1, &columns1);

		if (rc == ERR_OK)
		{
			rows2 = rows1;
			columns2 = 1;
			mtr2 = matrix_alloc(rows2, columns2);
			
			if (mtr2)
			{
				rc = gauss_solve(mtr1, mtr2, rows1, columns1);
			}
			else
			{
				rc = ERR_MEMORY;	
			}
		}
	}
	else
	{
		rc = ERR_ARGS;
	}

	if (rc == ERR_OK)
	{
		if (argc == ARGS_LEN_SUM_MULTIPLY)
		{
			rc = matrix_fprint(argv[ARGS_RES_FILE_MATRIX_INDEX], (const double**) mtr3, rows3, columns3);
		}
		else
		{
			rc = matrix_fprint(argv[ARGS_RES_FILE_MATRIX_INDEX_SOLVE], (const double**) mtr2, rows2, columns2);
		}
	}
	matrix_free(mtr1, rows1);
	matrix_free(mtr2, rows2);
	matrix_free(mtr3, rows3);

	return rc;
}
