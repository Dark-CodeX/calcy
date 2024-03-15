#ifndef CALCY_PARSER_H
#define CALCY_PARSER_H

#undef __STRICT_ANSI__

#include "../token/token.h"
#include "../math/math.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

typedef struct parser
{
    const calcy_token *M_tokens;
    size_t M_current_parser;
} calcy_parser;

#ifndef LDTYPE_DEF
#define LDTYPE_DEF
typedef long double DATA_TYPE;
#endif

#ifndef CONST_TOLERANCE_LEVEL
#define CONST_TOLERANCE_LEVEL
static const DATA_TYPE TOLERANCE_LEVEL = 1e-10;
#endif

static DATA_TYPE RESULT_STATIC;

bool calcy_parser_init(calcy_parser *parser, const calcy_token *toks_start);
DATA_TYPE calcy_parser_perform(calcy_parser *parser);
DATA_TYPE calcy_parser_expr(calcy_parser *parser);
DATA_TYPE calcy_parser_term(calcy_parser *parser);
DATA_TYPE calcy_parser_expo(calcy_parser *parser);
DATA_TYPE calcy_parser_functions(calcy_parser *parser);
DATA_TYPE calcy_parser_brackets(calcy_parser *parser);
DATA_TYPE calcy_parser_factor(calcy_parser *parser);

#endif