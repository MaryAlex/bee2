//
// Created by Maria Chmyreva on 3/10/18.
//

#include <command.h>
#include <bee2/core/rng.h>
#include <bpace_bob_second.h>
#include <bpace_bob_start.h>
#include <bpace_alice_second.h>
#include <bpace_alice_start.h>
#include <help.h>
#include <memory.h>
#include <stdio.h>
#include "../../constants.h"

static const int EQUALS_RETURN = 0;
Command commands[COMMANDS_LENGTH];

// WARNING!
// Don't forget to change COMMANDS_LENGTH value in .h file when edit commands initialization
void init_commands() {
    commands[0] = help;
    commands[1] = bpace_alice_start;
    commands[2] = bpace_alice_second;
    commands[3] = bpace_bob_start;
    commands[4] = bpace_bob_second;
}

int run_command(Command command, int argc, char **argv) {
    if (command.is_random_needed) {
        rngCreate(NULL, NULL);
    }
    int code = command.run(argc, argv);
    if (command.is_random_needed) {
        rngClose();
    }
    return code;
}

int execute_command(char *command_name, int argc, char **argv) {
    for (int i = 0; i < COMMANDS_LENGTH; ++i) {
        Command command = commands[i];
        if (EQUALS_RETURN == strcmp(command.name, command_name)) {
            return run_command(command, argc, argv);
        }
    }
    printf("The is no such command. Please, input --help to see possible commands.\n");
    return ERROR_CODE;
}