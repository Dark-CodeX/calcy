#include "./lexer.h"

bool calcy_lexer_init(calcy_lexer *lexer)
{
    if (!lexer)
        return false;
    lexer->M_token_len = 0;
    lexer->M_token_cap = 10;
    lexer->M_tokens = calloc(lexer->M_token_cap, sizeof(calcy_token));
    if (!lexer->M_tokens)
    {
        free(lexer);
        return false;
    }
    lexer->M_src = NULL;
    lexer->M_current_lexer = 0;
    return true;
}

bool calcy_lexer_resize(calcy_lexer *lexer)
{
    if (!lexer)
        return false;
    lexer->M_token_cap += 10;
    lexer->M_tokens = realloc((void *)lexer->M_tokens, lexer->M_token_cap * sizeof(calcy_token));
    if (!lexer->M_tokens)
        return false;
    return true;
}

bool calcy_lexer_assign_source(calcy_lexer *lexer, const char *src)
{
    if (!lexer)
        return false;
    if (!src)
        return false;
    lexer->M_src = src; // both now points to the same memory segment ;)
    return true;
}

bool calcy_lexer_add_token(calcy_lexer *lexer, const char *tok, size_t tok_len, calcy_token_type type, size_t start, size_t end)
{
    if (!lexer)
        return false;
    lexer->M_tokens[lexer->M_token_len].M_start = start;
    lexer->M_tokens[lexer->M_token_len].M_end = end;
    lexer->M_tokens[lexer->M_token_len].M_type = type;
    lexer->M_tokens[lexer->M_token_len].M_lexeme = calloc(tok_len + 1, sizeof(char));
    for (size_t i = 0; i < tok_len; i++)
    {
        lexer->M_tokens[lexer->M_token_len].M_lexeme[i] = tok[i];
    }

    lexer->M_token_len++;
    if (lexer->M_token_cap == lexer->M_token_len)
        calcy_lexer_resize(lexer);
    return true;
}

bool calcy_lexer_scan_tokens(calcy_lexer *lexer)
{
    if (!lexer)
        return false;
    char ch;
    for (lexer->M_current_lexer = 0; lexer->M_src[lexer->M_current_lexer];)
    {
        ch = lexer->M_src[lexer->M_current_lexer];
        switch (ch)
        {
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            lexer->M_current_lexer++;
            break;

        case '+':
            calcy_lexer_add_token(lexer, &ch, 1, TOKEN_OPERATOR_ADD, lexer->M_current_lexer, lexer->M_current_lexer + 1);
            lexer->M_current_lexer++;
            break;

        case '-':
            calcy_lexer_add_token(lexer, &ch, 1, TOKEN_OPERATOR_SUBSTRACT, lexer->M_current_lexer, lexer->M_current_lexer + 1);
            lexer->M_current_lexer++;
            break;

        case '*':
            calcy_lexer_add_token(lexer, &ch, 1, TOKEN_OPERATOR_MULTIPLY, lexer->M_current_lexer, lexer->M_current_lexer + 1);
            lexer->M_current_lexer++;
            break;

        case '/':
            calcy_lexer_add_token(lexer, &ch, 1, TOKEN_OPERATOR_DIVIDE, lexer->M_current_lexer, lexer->M_current_lexer + 1);
            lexer->M_current_lexer++;
            break;

        case '^':
            calcy_lexer_add_token(lexer, &ch, 1, TOKEN_OPERATOR_EXPONENTIAL, lexer->M_current_lexer, lexer->M_current_lexer + 1);
            lexer->M_current_lexer++;
            break;

        case '(':
            calcy_lexer_add_token(lexer, &ch, 1, TOKEN_LEFT_PAREN, lexer->M_current_lexer, lexer->M_current_lexer + 1);
            lexer->M_current_lexer++;
            break;

        case ')':
            calcy_lexer_add_token(lexer, &ch, 1, TOKEN_RIGHT_PAREN, lexer->M_current_lexer, lexer->M_current_lexer + 1);
            lexer->M_current_lexer++;
            break;

        case '=':
            calcy_lexer_add_token(lexer, &ch, 1, TOKEN_EQUAL_TO, lexer->M_current_lexer, lexer->M_current_lexer + 1);
            lexer->M_current_lexer++;
            break;
        default:
            if (isdigit(ch) || ch == '.')
            {
                calcy_lexer_scan_numbers(lexer);
            }
            else if (isalpha(ch))
            {
                calcy_lexer_scan_alpha(lexer);
            }
            else
                lexer->M_current_lexer++;
            break;
        }
    }
    calcy_lexer_add_token(lexer, NULL, 0, TOKEN_EOF, -1, -1);
    return true;
}

bool calcy_lexer_has_reached_eof(const calcy_lexer *lexer)
{
    if (!lexer)
        return false;
    return lexer->M_src[lexer->M_current_lexer] == 0; // true if has reached EOF, otherwise false
}

bool calcy_lexer_scan_numbers(calcy_lexer *lexer)
{
    size_t pos_start = lexer->M_current_lexer;
    char ch = lexer->M_src[lexer->M_current_lexer];
    bool is_decimal = false;
    if (ch == '.')
    {
        is_decimal = true;
        ch = lexer->M_src[++lexer->M_current_lexer];
    }
    while (isdigit(ch))
    {
        ch = lexer->M_src[++lexer->M_current_lexer];
        if (ch == '.')
        {
            if (is_decimal)
                break;
            is_decimal = true;
            ch = lexer->M_src[++lexer->M_current_lexer];
        }
    }
    calcy_lexer_add_token(lexer, lexer->M_src + pos_start, lexer->M_current_lexer - pos_start, TOKEN_NUMBER, pos_start, lexer->M_current_lexer);
    return true;
}

bool calcy_lexer_scan_alpha(calcy_lexer *lexer)
{
    size_t pos_start = lexer->M_current_lexer;
    char ch = lexer->M_src[lexer->M_current_lexer];
    while (isalpha(ch))
    {
        ch = lexer->M_src[++lexer->M_current_lexer];
    }
    calcy_lexer_add_token(lexer, lexer->M_src + pos_start, lexer->M_current_lexer - pos_start, TOKEN_ALPHA, pos_start, lexer->M_current_lexer);
    return true;
}

void calcy_lexer_free(calcy_lexer *lexer)
{
    if (!lexer)
        return;
    if (lexer->M_src)
        free((void *)lexer->M_src);
    lexer->M_current_lexer = 0;

    for (size_t i = 0; i < lexer->M_token_len; i++)
        free(lexer->M_tokens[i].M_lexeme);
    free(lexer->M_tokens);
    lexer->M_token_len = 0;
    lexer->M_token_cap = 0;
    free(lexer);
}
