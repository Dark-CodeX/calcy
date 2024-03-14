#ifndef CALCY_MATH_H
#define CALCY_MATH_H

#include <math.h>
#include <stddef.h>

#ifndef LDTYPE_DEF
#define LDTYPE_DEF
typedef long double DATA_TYPE;
#endif

DATA_TYPE factorial(DATA_TYPE num);
DATA_TYPE fast_pow(DATA_TYPE num, size_t expo);

#endif