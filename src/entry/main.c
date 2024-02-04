#include "../lexer/lexer.h"
#include "../input/input.h"
#include "../parser/parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    size_t expr_length;
    char *expr = calcy_input(&expr_length);
    if (!expr)
    {
        fprintf(stderr, "%s: error: cannot get user input due to memory issue\n", argv[0]);
        return EXIT_FAILURE;
    }

    calcy_lexer *lexer = calloc(1, sizeof(calcy_lexer));
    if (!calcy_lexer_init(lexer))
    {
        fprintf(stderr, "%s: error: cannot allocate memory on heap section\n", argv[0]);
        return EXIT_FAILURE;
    }
    calcy_lexer_assign_source(lexer, expr);
    calcy_lexer_scan_tokens(lexer);
    lex_print(lexer);
    calcy_lexer_free(lexer);

    return EXIT_SUCCESS;
}