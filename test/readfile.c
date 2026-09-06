#include "exec.h"
#include "input.h"

#include "util/string.h"

#include <errno.h>    // to dump error message
#include <stdio.h>    // to print output
#include <stdlib.h>   // for malloc, realloc, free
#include <sys/wait.h> // for waitpid

FILE *readfile;

int do_shell()
{
    while (1)
    {
        // receiver user input from stdin, interactive mode!
        char *command = NULL;
        long command_length = 0;
        char c;
        while ((c = fgetc(readfile)) != EOF)
        {
            command = (char *)realloc(command, sizeof(char) * command_length);
            command[command_length] = c;
            command_length++;

            if (strstr(command, "\n") != NULL)
            {
                // add a NULL byte to the end of the command string
                command_length++;
                command = (char *)realloc(command,
                                          sizeof(char) * command_length);
                command = strncat(command, "\0", BUFFER_SIZE);

                // we have reached the end of the command, break!
                break;
            }
        }

        // clean the messy input string up
        const char *messy = command;
        command_length = handle_user_input(messy, command_length, &command);

        if (strlen(command) == 0 || strncmp(command, "exit", 4) == 1)
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
    int to_ret;
    system_setup();
    if (argc == 2)
    {
        char *filename = argv[1];
        readfile = fopen(filename, "r");
        to_ret = do_shell();
    }
    else
    {
        fprintf(stdout, "Could not find input file... exiting\n");
    }
    system_cleanup();

    return to_ret;
}
