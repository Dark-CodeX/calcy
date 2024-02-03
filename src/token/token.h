#ifndef CALCY_TOKEN_H
#define CALCY_TOKEN_H

#include "../token_type/token_type.h"
#include <stddef.h>

typedef struct token{
    char *M_lexeme;
    calcy_token_type M_type;
    size_t M_start;
    size_t M_end;
} calcy_token;

#endif