//
// Created by Maria Chmyreva on 3/10/18.
//

#include <stdio.h>
#include "../command.h"
#include "../help.h"
#include "../../constants.h"

int print_all() {
    printf("\nInput commands after -- and parameters after -\n\n");
    for (int i = 0; i < COMMANDS_LENGTH; ++i) {
        Command command = commands[i];
        printf("--%s  %s\n\n", command.name, command.description);
    }
    return SUCCESS_CODE;
}

const Command help = {
        .name = "help",
        .description = "print all commands and there description",
        .run = (int (*)(int, char **)) &print_all,
        .is_random_needed = false
};
