//
// Created by Maria Chmyreva on 3/25/18.
//

#include <bpace_util.h>
#include <command.h>
#include <string_util.h>
#include <bee2/core/err.h>
#include <stdio.h>

int bpace_alice_second_run(int argc, char **argv) {
    int l;
    char *in = get_in_parameter(argc, argv);
    char *password = get_required_argument_value(argc, argv, PASSWORD_PARAMETER);
    bake_bpace_o *state = get_state_from_file(password, (char *) FILE_STATE_ALICE_NAME, &l);
    err_t code = bakeBPACEStep5(NULL, (const octet *) in, state);
    CODE_CHECK_WITH_RETURN(code, final_step_run(state, (char *) FILE_STATE_ALICE_NAME))
    return ERROR_CODE;
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
