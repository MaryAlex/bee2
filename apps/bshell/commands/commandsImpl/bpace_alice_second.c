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
                       "Parameters:\n"
                       "\tpassword - common password between Alice and Bob,\n"
                       "\tin - message that Alice received from Bob.\n"
                       "Output: common key.",
        .run = &bpace_alice_second_run,
        .is_random_needed = true
};
