#include "./parser.h"

bool calcy_parser_init(calcy_parser *parser, const calcy_token *toks_start)
{
    if (!parser)
        return false;
    parser->M_tokens = toks_start;
    parser->M_current_parser = 0;
    return true;
}

DATA_TYPE calcy_parser_perform(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    RESULT_STATIC = calcy_parser_expr(parser);
    return RESULT_STATIC;
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
    DATA_TYPE res = calcy_parser_functions(parser);
    while (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_EXPONENTIAL)
    {
        parser->M_current_parser++;
        DATA_TYPE __power_expo = calcy_parser_functions(parser);
        if (res == (size_t)res && __power_expo == (size_t)__power_expo)
            res = fast_pow(res, __power_expo);
        else
            res = powl(res, __power_expo);
    }
    return res;
}

DATA_TYPE calcy_parser_functions(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    if (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_ALPHA)
    {
        while (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_ALPHA)
        {
            const char *function_name = parser->M_tokens[parser->M_current_parser++].M_lexeme;
            if (strcmp(function_name, "sin") == 0)
            {
                DATA_TYPE in_val = calcy_parser_brackets(parser);
                return sinl(in_val);
            }
            else if (strcmp(function_name, "ans") == 0 || strcmp(function_name, "ANS") == 0)
            {
                return RESULT_STATIC;
            }
            else if (strcmp(function_name, "inf") == 0 || strcmp(function_name, "INF") == 0)
            {
                return INFINITY;
            }
            else if (strcmp(function_name, "nan") == 0 || strcmp(function_name, "nan") == 0)
            {
                return NAN;
            }
            else if (strcmp(function_name, "e") == 0)
            {
                return M_E;
            }
            else if (strcmp(function_name, "pi") == 0 || strcmp(function_name, "PI") == 0)
            {
                return M_PI;
            }
            else if (strcmp(function_name, "sqrt") == 0)
            {
                DATA_TYPE in_val = calcy_parser_brackets(parser);
                return sqrtl(in_val);
            }
            else if (strcmp(function_name, "cbrt") == 0)
            {
                DATA_TYPE in_val = calcy_parser_brackets(parser);
                return cbrtl(in_val);
            }
            else if (strcmp(function_name, "fact") == 0)
            {
                DATA_TYPE in_val = calcy_parser_brackets(parser);
                return factorial(in_val);
            }
        }
    }
    else if (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_NUMBER || parser->M_tokens[parser->M_current_parser].M_type == TOKEN_LEFT_PAREN)
    {
        return calcy_parser_brackets(parser);
    }
    return INFINITY;
}

DATA_TYPE calcy_parser_brackets(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    if (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_LEFT_PAREN)
    {
        parser->M_current_parser++;
        calcy_parser ptemp;
        ptemp.M_current_parser = 0;
        ptemp.M_tokens = parser->M_tokens + parser->M_current_parser;
        DATA_TYPE result = calcy_parser_perform(&ptemp);
        parser->M_current_parser += ptemp.M_current_parser;
        if (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_RIGHT_PAREN)
            parser->M_current_parser++;
        return result;
    }
    else if (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_NUMBER)
    {
        return calcy_parser_factor(parser);
    }
    return INFINITY;
}

DATA_TYPE calcy_parser_factor(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    return strtold(parser->M_tokens[parser->M_current_parser++].M_lexeme, NULL);
}
