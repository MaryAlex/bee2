//
// Created by Maria Chmyreva on 3/25/18.
//

#include <bpace_util.h>
#include <command.h>
#include "../../constants.h"

int bpace_alice_second_run(int argc, char **argv) {
    return second_command_run(argc, argv, FILE_STATE_ALICE_NAME, bakeBPACEStep5, false);
}

const Command bpace_alice_second = {
        .name = "bpaceAliceSecond",
        .description = "Run final steps of bpace from Alice side. Removes state file for Alice.\n"
                       BELOW_GOES_PARAMETERS_DESC
                       PASSWORD_DESC
                       IN_TO_ALICE_FROM_BOB_DESC
                       USER_ID_DESC
                       "Output: common key.",
        .run = &bpace_alice_second_run,
        .is_random_needed = true
};
