#ifndef CALCY_TOKEN_TYPE_H
#define CALCY_TOKEN_TYPE_H

typedef enum token_type
{
    TOKEN_NUMBER,               // Represents numbers (1, 3.14, ...)
    TOKEN_ALPHA,                // Represents functions (sin, cos, ...)
    TOKEN_OPERATOR_ADD,         // Represents addition operator (+)
    TOKEN_OPERATOR_SUBSTRACT,   // Represents substraction (-)
    TOKEN_OPERATOR_MULTIPLY,    // Represents multiplication (*)
    TOKEN_OPERATOR_DIVIDE,      // Represents division (/)
    TOKEN_OPERATOR_EXPONENTIAL, // Represents exponential (^)
    TOKEN_LEFT_PAREN,           // Represents left parenthesis (
    TOKEN_RIGHT_PAREN,          // Represents right parenthesis )
    TOKEN_EQUAL_TO,             // Represents equal to (=)
    TOKEN_EOF                   // Represents END OF FILE
} calcy_token_type;

#endif