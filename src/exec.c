#include "exec.h"

#include <stdlib.h> // for malloc, realloc, and free
#include <unistd.h> // for fork

/*
 * @brief Initialize execution engine attributes for shell
 */
void exec_init(char *environment) {
    env = environment;
}

/*
 * @brief Clean up the attributes from execution
 */
void exec_cleanup() {
    env = NULL;
}

/*
 * @brief Takes a command and arguments array as input and executes the command in
 * a child process created by the function.
 *
 * @param command: the binary executable to run
 * @param argv: the arguments to the command to run
 * @returns: the pid_t of the child process created on success, else error code
 */
pid_t execute_process(const char *command, char **argv) {
    pid_t pid = fork();

    if (pid < 0) {
        return (pid_t) -1;
    } else if (pid == 0) {
        char *environment[] = {env, NULL};
        execve(argv[0], argv, environment); 
        _exit(1);
    }

    return pid;
}

