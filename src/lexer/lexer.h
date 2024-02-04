#ifndef CALCY_LEXER_H
#define CALCY_LEXER_H

#include "../token/token.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct lexer
{
    calcy_token *M_tokens;
    size_t M_token_len, M_token_cap;

    size_t M_current_lexer;
    const char *M_src;

} calcy_lexer;

bool calcy_lexer_init(calcy_lexer *lexer);
bool calcy_lexer_resize(calcy_lexer *lexer);
bool calcy_lexer_assign_source(calcy_lexer *lexer, const char *src);
bool calcy_lexer_add_token(calcy_lexer *lexer, const char *tok, size_t tok_len, calcy_token_type type, size_t start, size_t end);
bool calcy_lexer_scan_tokens(calcy_lexer *lexer);
bool calcy_lexer_has_reached_eof(const calcy_lexer *lexer);
bool calcy_lexer_scan_numbers(calcy_lexer *lexer);
void calcy_lexer_free(calcy_lexer *lexer);

void lex_print(const calcy_lexer *lexer);
#endif