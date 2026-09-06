#include "exec.h"

#include <stdlib.h> // for malloc, realloc, and free
#include <unistd.h> // for fork

/*
 * TODO: implement me!
 */
void exec_init(char *environment) {
    env = environment;
}

/*
 * TODO: implement me!
 */
void exec_cleanup() {
    env = NULL;
}

/*
 * TODO: implement me!
 */
pid_t execute_process(const char *command, char **argv) {
    pid_t pid = fork();

    if (pid < 0) {
        return (pid_t) -1;
    } else if (pid == 0) {
        char *environment[] = {env, NULL};
        execve(command, argv, environment); 
        _exit(1);
    }

    return pid;
}

