#include "./parser.h"

bool calcy_parser_init(calcy_parser *parser, const calcy_token *toks)
{
    if (!parser)
        return false;
    parser->M_tokens = toks;
    parser->M_current_parser = 0;
    return true;
}

DATA_TYPE calcy_parser_perform(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    return calcy_parser_expr(parser);
}

DATA_TYPE calcy_parser_expr(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    DATA_TYPE res = calcy_parser_term(parser);
    while (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_ADD || parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_SUBSTRACT)
    {
        calcy_token_type curr_type = parser->M_tokens[parser->M_current_parser].M_type;
        parser->M_current_parser++;
        if (curr_type == TOKEN_OPERATOR_ADD)
            res += calcy_parser_term(parser);
        else
            res -= calcy_parser_term(parser);
    }
    return res;
}

DATA_TYPE calcy_parser_term(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    DATA_TYPE res = calcy_parser_expo(parser);
    while (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_MULTIPLY || parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_DIVIDE)
    {
        calcy_token_type curr_type = parser->M_tokens[parser->M_current_parser].M_type;
        parser->M_current_parser++;
        if (curr_type == TOKEN_OPERATOR_MULTIPLY)
            res *= calcy_parser_expo(parser);
        else
        {
            DATA_TYPE divisor = calcy_parser_expo(parser);
            if (divisor == 0)
                return INFINITY;
            res /= divisor;
        }
    }
    return res;
}

DATA_TYPE calcy_parser_expo(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    DATA_TYPE res = calcy_parser_factor(parser);
    while (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_EXPONENTIAL)
    {
        parser->M_current_parser++;
        res = powl(res, calcy_parser_factor(parser));
    }
    return res;
}

DATA_TYPE calcy_parser_factor(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    return strtold(parser->M_tokens[parser->M_current_parser++].M_lexeme, NULL);
}
