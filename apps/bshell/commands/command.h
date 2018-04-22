//
// Created by Maria Chmyreva on 3/10/18.
//

#ifndef BSHELL_COMMAND_H
#define BSHELL_COMMAND_H

#include <stdbool.h>

#define COMMANDS_LENGTH 5

struct Command {
    char *name;
    char *description;

    /***
     * @param count of arguments that was entered and arguments
     * @return success code
     */
    int (*run)(int, char **);
    /**
     * @brief To mark commands that needed random service, so we can init it and destroy in the end
     */
    bool is_random_needed;
};

typedef struct Command Command;

extern Command commands[COMMANDS_LENGTH];

/***
 * Initialize of commands variable
 */
void init_commands();

/***
 * @param command that was entered, count of arguments that was entered and arguments
 * @return success code
 */
int execute_command(char *, int, char **);

#endif //BSHELL_COMMAND_H
