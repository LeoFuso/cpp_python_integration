#include <stdio.h>
#include "c_square_root.h"

int
main(void)
{
    const double value = 25.0;
    double result = 0.0;

    result = calculate_single(value);

    printf(" VALUE: %f\nRESULT: %f\n", value, result);

    return 0;
}
