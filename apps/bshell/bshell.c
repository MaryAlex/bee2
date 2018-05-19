/**
 * @authors Maria Chmyreva
 * @brief Shell for some algorithms from library. In "/commandsImpl" you can see commands name and description.
 * @note If you want to add more commands just add there .h/.c files and add function to array in "init_commands" function
 */
#include <stdio.h>
#include <string_util.h>
#include <command.h>
#include "constants.h"

// TODO: argc and argv goes as parameters in every function. Bad. Need to be refactored.

int main(int argc, char **argv) {
    char *command;
    // One for name of program
    if (argc == 1) {
        printf("Please, input command u wanna use or --help.\n");
        return ERROR_CODE;
    }
    command = get_command_name(argv);
    if (command == NULL) {
        return ERROR_CODE;
    }
    init_commands();
    if (ERROR_CODE == execute_command(command, argc, argv)) {
        printf("Smth go wrong, command not done");
        return ERROR_CODE;
    }
    return 0;
}