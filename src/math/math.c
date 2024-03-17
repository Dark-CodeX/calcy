#include "./math.h"

DATA_TYPE factorial(DATA_TYPE num)
{
    long double NUM = creall(num);
    if (NUM == 1 || NUM == 0)
        return 1;
    else if (NUM == NAN || NUM == INFINITY)
        return INFINITY;
    DATA_TYPE result = 1;
    for (size_t i = 1; i <= NUM; i++)
        result *= i;
    return result;
}

DATA_TYPE fast_pow(DATA_TYPE num, size_t expo)
{
    if (expo == 0)
        return 1;
    else if (expo == 1)
        return num;
    else if (expo % 2 == 0)
        return fast_pow(num * num, expo / 2);
    else
        return num * fast_pow(num, expo - 1);
}