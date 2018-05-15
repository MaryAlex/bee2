//
// Created by Maria Chmyreva on 3/11/18.
//


#include <command.h>
#include <bee2/defs.h>
#include <bee2/crypto/bake.h>
#include <malloc.h>
#include <bee2/core/err.h>
#include <bpace_util.h>
#include "../../constants.h"

err_t second_step_run(int l, bake_bpace_o *state) {
    size_t size_of_bob_first_message = (size_t) SIZE_OF_BOB_FIRST_MESSAGE(l);
    octet *out = malloc(size_of_bob_first_message);
    err_t code = bakeBPACEStep2(out, state);
    CODE_CHECK(code, printAnswer("Send this: %s\n", out, size_of_bob_first_message))
    free(out);
    return code;
}

int bpace_bob_start_run(int argc, char **argv) {
    return start_command_run(argc, argv, (char *) FILE_STATE_BOB_NAME, second_step_run);
}

const Command bpace_bob_start = {
        .name = "bpaceBobStart",
        .description = "Run and init bpace from Bob side. Creates state file for Bob.\n"
                       "Parameters:\n"
                       "\tpassword - common password between Alice and Bob.\n"
                       "\tl - (Optional. Default value = 128) security level Can be only one of this: {128, 192, 256}.\n"
                       "Output: message that need to be sended to Alice.",
        .run = &bpace_bob_start_run,
        .is_random_needed = true
};
