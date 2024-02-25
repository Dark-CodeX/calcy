#ifndef CALCY_PARSER_H
#define CALCY_PARSER_H

#include "../token/token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct parser
{
    const calcy_token *M_tokens;
    size_t M_current_parser;
} calcy_parser;

typedef long double DATA_TYPE;

bool calcy_parser_init(calcy_parser *parser, const calcy_token *toks);
DATA_TYPE calcy_parser_perform(calcy_parser *parser);
DATA_TYPE calcy_parser_expr(calcy_parser *parser);
DATA_TYPE calcy_parser_term(calcy_parser *parser);
DATA_TYPE calcy_parser_expo(calcy_parser *parser);
DATA_TYPE calcy_parser_factor(calcy_parser *parser);

#endif