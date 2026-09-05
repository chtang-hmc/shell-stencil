#include "input.h"

#include "util/memset.h"
#include "util/string.h"

#include <stdlib.h> // for malloc, realloc, free only!

/*
 * @brief Initialize string parsing attributes for an input
 *
 * Hint: what should the initial values of each of the attributes be input
 *       attributes be?
 */
void userinput_init() {
    input_length = 0; 
    num_tokens = 0;
}

/*
 * TODO: implement me!
 *
 * Hint: is there anything else that can be reused here?
 */
void userinput_reset() {
    userinput_init();

    // free tokens
    for (long i = 0; i < num_tokens; ++i) {
        free(tokens[i]);
    }
    free(tokens);
}

/*
 * TODO: implement me!
 * 
 * Hint: reset all values... anything that was dynamically allocated should be
 *       freed!
 */
void userinput_cleanup() {
    userinput_reset();
}

/*
 * TODO: implement me!
 *
 * Hints:
 *   - user input may be messy with its whitespace, be sure the command is not
 *   - command should end with '\0'
 *   - don't forget about the error cases! what behaviors should be undefined?
 */
 // TODO: handle errors and return -1
long handle_user_input(const char *user_input, long strlen, char **command) {
    // identify beginning whitespaces
    long i = 0;
    while (*(user_input + i) == ' ') {
        ++i;
    }

    // allocate new string
    char *newstring = malloc(strlen * sizeof(char));
    long newstring_length = 0;

    // go through the user input
    long num_whitespaces = 0;
    while (*(user_input + i) != '\n' || i < strlen) {
        // filter out extra whitespaces
        if (*(user_input + i)  != ' ') {num_whitespaces = 0;}
        else {++num_whitespaces;}

        if (num_whitespaces <= 1) {
            // add to buffer
            newstring[newstring_length] = *(user_input + i);
            newstring_length++;
        }

        i++;
    }

    // handle trailing white space
    if (*(user_input + i) == '\n') {
        if (num_whitespaces != 0) { // there was a whitespace before \n
            newstring[newstring_length - 1] = '\0';
        } else {
            newstring[newstring_length] = '\0';
        }
    }

    newstring = (char *) realloc(newstring, sizeof(char) * (newstring_length + 1));

    // copy newstring to command
    for (i = 0; i <= newstring_length; ++i) {
        *(*command+i) = newstring[i];
    }

    // return!
    free(newstring);
    return newstring_length;
}

/*
 * TODO: implement me!
 *
 * Hints:
 *   - we assume that str is a clean string... given this, what error cases
 *     might occur?
 *   - think about tokens' type... we have a pointer to an array of strings
 *     (which are themselves arrays...) how big is the array of strings?
 *      --> you may need to dynamically resize the array
 *      --> see "man 3 malloc" for further hints
 *   - be sure to modify the input string so that each token ends with a NULL
 *     character!
 */
long tokenize_input(char *str, long strlen, char ***tokens) {
    char **tokens_array = malloc(sizeof(char *) * something);

    long i = 0;
    long current_token_len = 0;

    while (i < strlen) {
        // find word length
        while (*(str + i + current_token_len) != ' ' && *(str + i + current_token_len) != '\n') {
            current_token_len++;
        }

        // create token for word
        char *token = malloc(sizeof(char) * current_token_len);
        for (long j = 0; j < current_token_len; ++j) {
            *(token + j) = *(str + i + j);
        }
        tokens_array[num_tokens] = token;
        num_tokens++;

        // handle end of command
        if (*(str + i + current_token_len) == '\n') {
            token = malloc(sizeof(NULL));
            tokens_array[num_tokens] = token;
            num_tokens++;
            tokens = &tokens_array; // return the allocated tokens array
            return num_tokens;
        }

        i += current_token_len + 1;
    }

    return -1;
}


