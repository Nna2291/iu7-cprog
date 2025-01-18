#include "errors.h"
#include "mtr_alloc.h"
#include <stdio.h>
#include "mtr_io.h"


static int matrix_read(FILE *f, double **data, size_t n, size_t m)
{
	if (!f)
	{
		return ERR_IO;
	}

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			if (fscanf(f, "%lf ", &data[i][j]) != 1)
			{
				return ERR_IO;
			}
		}
	}

	if (!feof(f))
	{
		return ERR_IO;
	}

	return ERR_OK;		
}


static int matrix_create_internal(FILE *f, double ***data, size_t *n, size_t *m)
{
	if (!f)
	{
		return ERR_IO;
	}

	double **tmp;
	int rc = ERR_OK;

	*data = NULL;

	if (fscanf(f, "%zu %zu", n, m) != 2)
	{
		return ERR_IO;
	}

	tmp = matrix_alloc(*n, *m);

	if (!tmp)
	{
		return ERR_MEMORY;
	}

	rc = matrix_read(f, tmp, *n, *m);

	if (rc != ERR_OK)
	{
		matrix_free(tmp, *n);
		return rc;
	}

	*data = tmp;
	return ERR_OK;
}


int matrix_create(const char *fname, double ***data, size_t *n, size_t *m)
{
	FILE *f = fopen(fname, "r");
	int rc = ERR_OK;

	if (!f)
	{
		return ERR_IO;
	}

	rc = matrix_create_internal(f, data, n, m);

	fclose(f);

	return rc;
}


static int matrix_internal_fprint(FILE *f, const double **a, size_t n, size_t m)
{
	if (fprintf(f, "%zu %zu\n", n, m) < 0)
	{
		return ERR_IO;
	}
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			if (fprintf(f, "%lf ", a[i][j]) < 0)
			{
				return ERR_IO;
			}
		}
		if (fprintf(f, "\n") < 0)
		{
			return ERR_IO;
		}
	}

	return ERR_OK;
}

int matrix_fprint(const char *filename, const double **mtr, size_t rows, size_t columns)
{
	int rc = ERR_OK;
	
	FILE *f = fopen(filename, "w");

	if (!f)
	{
		return ERR_IO;
	}

	rc = matrix_internal_fprint(f, mtr, rows, columns);
	fclose(f);
	return rc;
}
