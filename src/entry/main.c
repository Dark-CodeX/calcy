#include "../lexer/lexer.h"
#include "../input/input.h"
#include "../parser/parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    while (true)
    {
        printf("> ");
        size_t expr_length;
        char *expr = calcy_input(&expr_length);
        if (!expr)
        {
            fprintf(stderr, "%s: error: cannot get user input due to memory issue\n", argv[0]);
            return EXIT_FAILURE;
        }
        if (strcmp(expr, "exit") == 0)
            break;
        else if (strcmp(expr, "") == 0)
            continue;

        calcy_lexer *lexer = calloc(1, sizeof(calcy_lexer));
        if (!calcy_lexer_init(lexer))
        {
            fprintf(stderr, "%s: error: cannot allocate memory on heap section\n", argv[0]);
            return EXIT_FAILURE;
        }
        calcy_lexer_assign_source(lexer, expr);
        calcy_lexer_scan_tokens(lexer);

        // resolving any negative number
        calcy_lexer_neg(lexer);

        calcy_parser *parser = calloc(1, sizeof(calcy_parser));
        if (!calcy_parser_init(parser, lexer->M_tokens))
        {
            fprintf(stderr, "%s: error: cannot allocate memory on heap section\n", argv[0]);
            return EXIT_FAILURE;
        }
        DATA_TYPE result = calcy_parser_perform(parser);
        printf("%.16Lg\n", result);
        free(parser);
        calcy_lexer_free(lexer);
    }
    return EXIT_SUCCESS;
}