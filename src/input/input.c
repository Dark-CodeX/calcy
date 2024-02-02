#include "./input.h"

char *calcy_input(size_t *len)
{
    if (!len)
        return NULL;
    *len = 0; // just in case hehe ;)
    size_t cap = 32;
    char *buffer = calloc(cap, sizeof(char)); // calloc inits 0 to all memory segments
    if (!buffer)
        return NULL;
    char s_input;
    while ((s_input = getchar()))
    {
        if (s_input == 10 ||
            s_input == 0 ||
            s_input == EOF)
            break;
        buffer[(*len)++] = s_input;
        if (*len == cap)
        {
            cap += 32;
            buffer = realloc(buffer, sizeof(char) * cap);
            if (!buffer)
                return NULL;
        }
    }
    buffer[*len] = 0; // null termination
    return buffer;
}