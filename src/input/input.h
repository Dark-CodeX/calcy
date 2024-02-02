#ifndef CALCY_INPUT_H
#define CALCY_INPUT_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Takes input through (stdin) of any length.
 * @param len pointer to length (stores the length of the returned string)
 * @returns user input, NOTE: To be free by user
 * @returns NULL if something goes wrong
 */
char *calcy_input(size_t *len);

#endif