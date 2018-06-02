//
// Created by Maria Chmyreva on 3/10/18.
//

#include <stdio.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../constants.h"

// We ask to input command as first parameter
static const int COMMAND_PLACE = 1;
static const char COMMAND_STARTS_WITH[] = "--";
static const char PARAMETERS_STARTS_WITH[] = "-";
static const int COMMAND_STARTS_WITH_LENGTH = 2;
static const int PARAMETERS_STARTS_WITH_LENGTH = 1;
static const int EQUALS_RETURN = 0;
static const int PARAMETERS_STARTS_FROM_POSITION = 2;

bool is_line_start_with(char *line, const char *with) {
    return EQUALS_RETURN == strncmp(line, with, strlen(with));
}

char *get_command_name(char **argv) {
    char *command = argv[COMMAND_PLACE];
    if (!is_line_start_with(command, COMMAND_STARTS_WITH)) {
        printf("Please, input command as first parameter and start it with %s\n", COMMAND_STARTS_WITH);
        return NULL;
    }
    return command + COMMAND_STARTS_WITH_LENGTH;
}

char *get_argument_value(int argc, char **argv, const char *argument_name, bool isOptional) {
    int i;
    for (i = PARAMETERS_STARTS_FROM_POSITION; i < argc; i += 2) {
        char *arg = argv[i];
        if (!is_line_start_with(arg, PARAMETERS_STARTS_WITH)) {
            printf("Please, start all parameters with %s\n", PARAMETERS_STARTS_WITH);
            exit(NO_REQUIRED_PARAMETERS_ERROR_CODE);
        }
        if (EQUALS_RETURN == strcmp((arg + PARAMETERS_STARTS_WITH_LENGTH), argument_name)) {
            // Value after key
            return argv[i + 1];
        }
    }
    if (!isOptional) {
        printf("Please input next argument: %s\n", argument_name);
        exit(NO_REQUIRED_PARAMETERS_ERROR_CODE);
    }
    return NULL;
}

char *get_optional_argument_value(int argc, char **argv, const char *argument_name) {
    return get_argument_value(argc, argv, argument_name, true);
}

char *get_required_argument_value(int argc, char **argv, const char *argument_name) {
    return get_argument_value(argc, argv, argument_name, false);
}