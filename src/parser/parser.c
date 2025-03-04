#include "./parser.h"

char *str_lwr(char *__s)
{
    if (!__s)
        return NULL;
    for (char *tmp = __s; *tmp; tmp++)
        *tmp = tolower(*tmp);
    return __s;
}

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
    DATA_TYPE res = calcy_parser_implicit_mul(parser);
    while (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_MULTIPLY || parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_DIVIDE)
    {
        calcy_token_type curr_type = parser->M_tokens[parser->M_current_parser].M_type;
        parser->M_current_parser++;
        if (curr_type == TOKEN_OPERATOR_MULTIPLY)
            res *= calcy_parser_implicit_mul(parser);
        else
        {
            DATA_TYPE divisor = calcy_parser_implicit_mul(parser);
            if (divisor == 0)
                return INFINITY;
            res /= divisor;
        }
    }
    return res;
}

DATA_TYPE calcy_parser_implicit_mul(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    DATA_TYPE res = calcy_parser_expo(parser);
    while (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_LEFT_PAREN || parser->M_tokens[parser->M_current_parser].M_type == TOKEN_ALPHA)
    {
        res *= calcy_parser_expo(parser);
    }
    return res;
}

DATA_TYPE calcy_parser_expo(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    DATA_TYPE res = calcy_parser_unary_operators(parser);
    while (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_EXPONENTIAL)
    {
        parser->M_current_parser++;
        DATA_TYPE __power_expo = calcy_parser_unary_operators(parser);
        if (res == (size_t)res && __power_expo == (size_t)__power_expo)
            res = fast_pow(res, __power_expo);
        else
            res = cpowl(res, __power_expo);
    }
    return res;
}

DATA_TYPE calcy_parser_unary_operators(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    if (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_SUBSTRACT || parser->M_tokens[parser->M_current_parser].M_type == TOKEN_OPERATOR_ADD)
    {
        calcy_token_type opr = parser->M_tokens[parser->M_current_parser++].M_type;
        return opr == TOKEN_OPERATOR_SUBSTRACT ? calcy_parser_unary_operators(parser) * (DATA_TYPE)-1 : calcy_parser_unary_operators(parser);
    }
    return calcy_parser_functions(parser);
}

DATA_TYPE calcy_parser_functions(calcy_parser *parser)
{
    if (!parser)
        return INFINITY;
    if (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_ALPHA)
    {
        while (parser->M_tokens[parser->M_current_parser].M_type == TOKEN_ALPHA)
        {
            char *function_name = parser->M_tokens[parser->M_current_parser++].M_lexeme;
            // convert function_name to lowercase
            function_name = str_lwr(function_name);
            if (strcmp(function_name, "sin") == 0)
            {
                DATA_TYPE ret_val = csinl(calcy_parser_brackets(parser));
                return (cabsl(ret_val) > TOLERANCE_LEVEL ? ret_val : 0);
            }
            else if (strcmp(function_name, "cos") == 0)
            {
                DATA_TYPE ret_val = ccosl(calcy_parser_brackets(parser));
                return (cabsl(ret_val) > TOLERANCE_LEVEL ? ret_val : 0);
            }
            else if (strcmp(function_name, "tan") == 0)
            {
                DATA_TYPE ret_val = ctanl(calcy_parser_brackets(parser));
                return (cabsl(ret_val) > TOLERANCE_LEVEL ? ret_val : 0);
            }
            else if (strcmp(function_name, "cot") == 0)
            {
                DATA_TYPE x = ctanl(calcy_parser_brackets(parser));
                DATA_TYPE ret_val = 1 / (cabsl(x) > TOLERANCE_LEVEL ? x : 0);
                return (cabsl(ret_val) > TOLERANCE_LEVEL ? ret_val : 0);
            }
            else if (strcmp(function_name, "sec") == 0)
            {
                DATA_TYPE x = ccosl(calcy_parser_brackets(parser));
                DATA_TYPE ret_val = 1 / (cabsl(x) > TOLERANCE_LEVEL ? x : 0);
                return (cabsl(ret_val) > TOLERANCE_LEVEL ? ret_val : 0);
            }
            else if (strcmp(function_name, "cosec") == 0 || strcmp(function_name, "csc") == 0)
            {
                DATA_TYPE x = csinl(calcy_parser_brackets(parser));
                DATA_TYPE ret_val = 1 / (cabsl(x) > TOLERANCE_LEVEL ? x : 0);
                return (cabsl(ret_val) > TOLERANCE_LEVEL ? ret_val : 0);
            }
            else if (strcmp(function_name, "ans") == 0)
            {
                return RESULT_STATIC;
            }
            else if (strcmp(function_name, "inf") == 0)
            {
                return INFINITY;
            }
            else if (strcmp(function_name, "nan") == 0)
            {
                return NAN;
            }
            else if (strcmp(function_name, "e") == 0)
            {
                return M_E;
            }
            else if (strcmp(function_name, "i") == 0)
            {
                return I;
            }
            else if (strcmp(function_name, "pi") == 0)
            {
                return M_PI;
            }
            else if (strcmp(function_name, "sqrt") == 0)
            {
                return csqrtl(calcy_parser_brackets(parser));
            }
            else if (strcmp(function_name, "cbrt") == 0)
            {
                return cbrtl(calcy_parser_brackets(parser));
            }
            else if (strcmp(function_name, "fact") == 0)
            {
                return factorial(calcy_parser_brackets(parser));
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
        DATA_TYPE result = calcy_parser_perform(parser);
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

int calcy_print(DATA_TYPE result)
{
    long double r_img = cimagl(result), r_real = creall(result);
    if (r_img == 0)
    {
        return printf("%.16Lg\n", r_real);
    }
    else if (r_real == 0 && r_img != 0)
    {
        return printf("%.16Lgi\n", r_img);
    }
    else if (r_img < 0)
    {
        return printf("%.16Lg - %.16Lgi\n", r_real, r_img * -1);
    }
    else
    {
        return printf("%.16Lg + %.16Lgi\n", r_real, r_img);
    }
}