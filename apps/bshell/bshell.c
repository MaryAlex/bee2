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
    int error_code;
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
    error_code = execute_command(command, argc, argv);
    if (SUCCESS_CODE != error_code) {
        printf("Smth go wrong, command not done. Error code: %d\n", error_code);
        return ERROR_CODE;
    }
    return SUCCESS_CODE;
}