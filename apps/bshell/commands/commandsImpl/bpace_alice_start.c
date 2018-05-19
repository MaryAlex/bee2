//
// Created by Maria Chmyreva on 3/11/18.
//

#include <bee2/defs.h>
#include <bee2/crypto/bake.h>
#include <command.h>
#include <bpace_util.h>
#include <bee2/core/err.h>
#include "../../constants.h"

#ifndef OS_APPLE
    #include <malloc.h>
#else
    #include <stdlib.h>
#endif

char *in;

err_t third_step_run(int l, bake_bpace_o *state) {
    size_t size_of_alice_first_message = (size_t) SIZE_OF_ALICE_FIRST_MESSAGE(l);
    octet *out = malloc(size_of_alice_first_message);
    err_t code = bakeBPACEStep3(out, (const octet *) in, state);
    CODE_CHECK(code, printAnswer("Send this: %s\n", out, size_of_alice_first_message))
    free(out);
    return code;
}

int bpace_alice_start_run(int argc, char **argv) {
    in = get_in_parameter(argc, argv);
    return start_command_run(argc, argv, FILE_STATE_ALICE_NAME, third_step_run);
}

const Command bpace_alice_start = {
        .name = "bpaceAliceStart",
        .description = "Run and init bpace from Alice side. Creates state file for Alice.\n"
                       "Parameters:\n"
                       "\tpassword - common password between Alice and Bob,\n"
                       "\tin - message that Alice received from Bob.\n"
                       "\tl - (Optional. Default value = 128) security level Can be only one of this: {128, 192, 256}.\n"
                       "Output: message that need to be sended to Bob.",
        .run = &bpace_alice_start_run,
        .is_random_needed = true
};