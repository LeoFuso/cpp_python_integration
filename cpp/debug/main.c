#include <stdio.h>
#include <malloc.h>
#include "../c_square_root.h"

int
main(void)
{
	const double value = 25.0;
	double result = 0.0;

	double *array = (double *) calloc(6, sizeof(double));

	unsigned int i;
	for (i = 0; i < 6; i++)
	{
		array[i] = i + 1;
	}

	result = calculate_single(value);

	printf(" VALUE: %f\nRESULT: %f\n", value, result);

	result = calculate_sequence(array, 6);

	printf(" VALUE: {1,2,3,4,5,6}\nRESULT: %f\n", result);

	return 0;
}
