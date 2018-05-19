//
// Created by Maria Chmyreva on 3/11/18.
//

#include <command.h>
#include <bee2/defs.h>
#include <bee2/crypto/bake.h>
#include <bee2/core/err.h>
#include <bpace_util.h>
#include "../../constants.h"

#ifndef OS_APPLE
    #include <malloc.h>
#else
    #include <stdlib.h>
#endif

err_t second_step_run(int l, bake_bpace_o *state) {
    size_t size_of_bob_first_message = (size_t) SIZE_OF_BOB_FIRST_MESSAGE(l);
    octet *out = malloc(size_of_bob_first_message);
    err_t code = bakeBPACEStep2(out, state);
    CODE_CHECK(code, printAnswer("Send this: %s\n", out, size_of_bob_first_message))
    free(out);
    return code;
}

int bpace_bob_start_run(int argc, char **argv) {
    return start_command_run(argc, argv, FILE_STATE_BOB_NAME, second_step_run);
}

const Command bpace_bob_start = {
        .name = "bpaceBobStart",
        .description = "Run and init bpace from Bob side. Creates state file for Bob.\n"
                       BELOW_GOES_PARAMETERS_DESC
                       PASSWORD_DESC
                       SECURITY_LEVEL_DESC
                       USER_ID_DESC
                       "Output: message that need to be sended to Alice.",
        .run = &bpace_bob_start_run,
        .is_random_needed = true
};
