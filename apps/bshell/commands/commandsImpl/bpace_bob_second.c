//
// Created by Maria Chmyreva on 3/21/18.
//

#include <bee2/defs.h>
#include <bee2/crypto/bake.h>
#include <bpace_util.h>
#include <command.h>
#include <string_util.h>
#include <malloc.h>
#include <bee2/core/err.h>

int on_success(octet *out, bake_bpace_o *state, int l) {
    printAnswer("Fourth step out: %s\n", out, (size_t) SIZE_OF_BOB_SECOND_MESSAGE(l));
    return final_step_run(state, (char *) FILE_STATE_BOB_NAME);
}

int bpace_bob_second_run(int argc, char **argv) {
    int l;
    char *in = get_in_parameter(argc, argv);
    char *password = get_required_argument_value(argc, argv, PASSWORD_PARAMETER);
    bake_bpace_o *state = get_state_from_file(password, (char *) FILE_STATE_BOB_NAME, &l);
    octet *out = malloc((size_t) SIZE_OF_BOB_SECOND_MESSAGE(l));
    err_t code = bakeBPACEStep4(out, (const octet *) in, state);
    CODE_CHECK_WITH_RETURN(code, on_success(out, state, l))
    return ERROR_CODE;
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