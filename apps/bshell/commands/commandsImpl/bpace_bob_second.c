//
// Created by Maria Chmyreva on 3/21/18.
//

#include <bpace_util.h>
#include <command.h>
#include "../../constants.h"

int bpace_bob_second_run(int argc, char **argv) {
    return second_command_run(argc, argv, FILE_STATE_BOB_NAME, bakeBPACEStep4, true);
}

const Command bpace_bob_second = {
        .name = "bpaceBobSecond",
        .description = "Run final steps of bpace from Bob side. Removes state file for Bob.\n"
                       "Parameters:\n"
                       "\tpassword - common password between Alice and Bob,\n"
                       "\tin - message that Bob received from Alice.\n"
                       "Output: message that need to be sended to Alice and common key.",
        .run = &bpace_bob_second_run,
        .is_random_needed = true
};