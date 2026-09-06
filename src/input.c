#include "input.h"

#include "util/memset.h"
#include "util/string.h"

#include <stdlib.h> // for malloc, realloc, free only!

static char *prev_command = NULL;

/*
 * @brief Initialize string parsing attributes for an input
 */
void userinput_init()
{
    input_length = 0;
    num_tokens = 0;
    prev_command = NULL;
}

/*
 * @brief Free memory and reset values for next iteration through
 */
void userinput_reset()
{
    // free tokens
    for (long i = 0; i < num_tokens; ++i)
    {
        free(tokens[i]);
    }
    free(tokens);
    free(prev_command);

    userinput_init();
}

/*
 * @brief Clean up the attributes from input parsing
 */
void userinput_cleanup()
{
    userinput_reset();
}

/*
 * @brief Receives a user input string and returns a "cleaned" version of the string.
 * 
 * @param user_input: the (messy) user input string
 * @param strlen: the length of the user input string (to avoid buffer
 *                overflow!)
 * @param command: a pointer to the newly created string (likely a pointer to
 *                 be dereferenced created on the callers stack), this is how
 *                 the clean string is returned to the caller
 * @returns: the length of the clean input string on success, else -1
 */
long handle_user_input(const char *user_input, long strlen, char **command) {
    // identify beginning whitespaces
    long i = 0;
    while (i < strlen && *(user_input + i) == ' ')
    {
        ++i;
    }

    // allocate new string
    char *newstring = malloc((strlen + 1) * sizeof(char));
    long newstring_length = 0;

    // go through the user input
    long num_whitespaces = 0;
    while (i < strlen && *(user_input + i) != '\n')
    {
        // filter out extra whitespaces
        if (*(user_input + i) != ' ')
        {
            num_whitespaces = 0;
        }
        else
        {
            ++num_whitespaces;
        }

        if (num_whitespaces <= 1)
        {
            // add to buffer
            newstring[newstring_length] = *(user_input + i);
            newstring_length++;
        }

        i++;
    }

    // handle trailing white space
    if (i < strlen && *(user_input + i) == '\n')
    {
        if (num_whitespaces != 0)
        { // there was a whitespace before \n
            newstring_length--;
            newstring[newstring_length] = '\0';
        }
        else
        {
            newstring[newstring_length] = '\0';
        }
    }
    else
    { // we hit strlen without having a newline character
        return -1;
    }

    newstring = (char *)realloc(newstring, sizeof(char) * (newstring_length + 1));

    // copy newstring to command
    prev_command = newstring;
    *command = newstring;

    // return!
    return newstring_length;
}

/*
 * @brief Transforms a clean user string into an array of tokens.
 *
 * @param str: the clean input string to tokenize
 * @param strlen: the length of the input string
 * @param tokens: a pointer to the array of tokens to be created
 * @returns: the number of tokens created on success, else -1
 */
long tokenize_input(char *str, long strlen, char ***tokens) {
    num_tokens = 0;

    char **tokens_array = malloc(sizeof(char *) * (strlen + 1));

    long i = 0;
    long current_token_len = 0;

    while (i < strlen)
    {
        current_token_len = 0;

        // find word length
        while (*(str + i + current_token_len) != ' ' && *(str + i + current_token_len) != '\0')
        {
            current_token_len++;
        }

        // create token for word
        char *token = malloc(sizeof(char) * (current_token_len + 1));
        for (long j = 0; j < current_token_len; ++j)
        {
            *(token + j) = *(str + i + j);
        }
        *(token + current_token_len) = '\0';
        tokens_array[num_tokens] = token;
        num_tokens++;

        // handle end of command
        if (*(str + i + current_token_len) == '\0')
        {
            tokens_array[num_tokens] = NULL;

            tokens_array = (char **)realloc(tokens_array, sizeof(char *) * num_tokens);
            *tokens = tokens_array; // return the allocated tokens array
            return num_tokens;
        }

        i += current_token_len + 1;
    }

    free(tokens_array);
    return -1;
}
