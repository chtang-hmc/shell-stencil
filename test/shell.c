#include "exec.h"
#include "input.h"

#include "util/string.h"

#include <errno.h>    // to dump error message
#include <stdio.h>    // to print output
#include <stdlib.h>   // for malloc, realloc, free
#include <sys/wait.h> // for waitpid

int do_shell()
{
    while (1)
    {
        fprintf(stdout, "> ");

        // receiver user input from stdin, interactive mode!
        char *command = NULL;
        long command_length = 0;
        while (fgets(input_buffer, BUFFER_SIZE, stdin))
        {
            command_length += strlen(input_buffer);
            command = (char *)realloc(command, sizeof(char) * command_length);
            command = strncat(command, input_buffer, BUFFER_SIZE);

            if (strstr(command, "\0") != NULL)
            {
                // we have reached the end of the command, break!
                break;
            }
        }

        // clean the messy input string up
        const char *messy = command;
        command_length = handle_user_input(messy, command_length, &command);

        if (strncmp(command, "exit", 4) == 1)
        {
            // we have reached the end! exit out of the main loop
            break;
        }

        // tokenize input... (num_)tokens are a field of the input.h header
        num_tokens = tokenize_input(command, command_length, &tokens);

        pid_t child_pid = execute_process(command, tokens);
        if (child_pid == -1)
        {
            // this is our child returning from a bad input!
            fprintf(stderr, "Could not execute command \"%s\"...\n", command);
            return -1;
        }
        else
        {
            int stat_loc;
            waitpid(child_pid, &stat_loc, 0);
        }

        // userinput_reset();
    }

    return 0;
}

void system_setup()
{
    userinput_init();
    exec_init("PATH=/bin:/usr/bin/");
}

void system_cleanup()
{
    userinput_cleanup();
    exec_cleanup();
}

int main(int argc, char **argv)
{
    system_setup();
    int to_ret = do_shell();
    system_cleanup();

    return to_ret;
}
