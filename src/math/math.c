#include "./math.h"

DATA_TYPE factorial(DATA_TYPE num)
{
    if (num == 1 || num == 0)
        return 1;
    else if (num == NAN || num == INFINITY)
        return INFINITY;
    DATA_TYPE result = 1;
    for (size_t i = 1; i <= num; i++)
        result *= i;
    return result;
}