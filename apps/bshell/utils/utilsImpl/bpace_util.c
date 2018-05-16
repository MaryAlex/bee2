//
// Created by Maria Chmyreva on 3/21/18.
//

#include <stdlib.h>
#include <bee2/crypto/bake.h>
#include <stdbool.h>
#include <bee2/core/rng.h>
#include <memory.h>
#include <bee2/core/err.h>
#include <file_util.h>
#include <string_util.h>
#include <bee2/core/hex.h>
#include <stdio.h>
#include "../../constants.h"

static const char *possible_curve_names[] =
/**
 * @link Was taken from:
 * @file: bign.c
 * @line: 37
 * @name bign-curve128v1
 * @date march 18 2018
 */
        {"1.2.112.0.2.0.34.101.45.3.1",
/**
* @link Was taken from:
* @file: bign.c
* @line: 79
* @name bign-curve192v1
* @date april 21 2018
*/
         "1.2.112.0.2.0.34.101.45.3.2",
/**
* @link Was taken from:
* @file: bign.c
* @line: 79
* @name bign-curve256v1
* @date april 21 2018
*/
         "1.2.112.0.2.0.34.101.45.3.3"};

/**
 * @brief Do memory allocation to setting and init it
 * @return reference to allocated memory
 */
bake_settings *get_setting() {
    bake_settings *settings = malloc(sizeof(bake_settings));
    settings->kca = false;
    settings->kcb = false;
    settings->helloa = NULL;
    settings->hellob = NULL;
    settings->rng = rngStepR;
    return settings;
}

/**
 * @param l - security level
 * @return curve name according bign.c to use it in bignStdParams
 */
const char *get_curve_name(int l) {
    int i;
    for (i = 0; i < POSSIBLE_SECURITY_LEVELS_SIZE; ++i) {
        if (l == possible_security_levels[i]) {
            return possible_curve_names[i];
        }
    }
    return NULL;
}

/**
 * @brief Do memory allocation to curve params and init it
 * @param l - security level for curve
 * @return reference to allocated memory
 */
bign_params *get_params(int l) {
    bign_params *params = (bign_params *) malloc(sizeof(bign_params));
    const char *curve_name = get_curve_name(l);
    NULL_CHECK_FOR_POINTER_FUNCTION(curve_name)
    bignStdParams(params, curve_name);
    return params;
};

bake_bpace_o *get_state(char *password, int l) {
    bake_bpace_o *state = malloc(bakeBPACE_keep((size_t) l));
    bign_params *params = get_params(l);
    bake_settings *settings = get_setting();
    err_t code = bakeBPACEStart(state, params, settings, (const octet *) password, strlen(password));
    free(params);
    free(settings);
    CODE_CHECK_WITH_RETURN(code, state)
    return NULL;
};


bake_bpace_o *get_state_from_file(char *password, char *file_state_name, int *l) {
    bake_bpace_o *state;
    read_security_level_from_file(file_state_name, l);
    state = get_state(password, *l);
    if (NULL != state) {
        read_state_from_file(file_state_name, state);
    }
    return state;
};

void printAnswer(const char *preface, void *answer, size_t size) {
    char *dest = malloc(size * OCTET_SIZE);
    hexFrom(dest, answer, size);
    printf(preface, dest);
}

/**
 * @brief Print common key and remove file
 * @param key
 * @param file_state_name
 */
void on_success_final_step(octet key[], char *file_state_name) {
    printAnswer("Common key is %s\n", key, KEY_SIZE);
    remove(get_full_file_name(file_state_name));
}

err_t final_step_run(bake_bpace_o *state, char *file_state_name) {
    octet key[KEY_SIZE];
    err_t code = bakeBPACEStepG(key, state);
    CODE_CHECK(code, on_success_final_step(key, file_state_name))
    return code;
}

/**
 * @param l - security level
 * @return is security level contains in possible_security_levels
 */
bool is_correct_security_level(int l) {
    int i;
    for (i = 0; i < POSSIBLE_SECURITY_LEVELS_SIZE; ++i) {
        if (l == possible_security_levels[i]) {
            return true;
        }
    }
    return false;
}

int get_security_level_parameter(int argc, char **argv) {
    char *entered_l = get_optional_argument_value(argc, argv, SECURITY_LEVEL_PARAMETER);
    if (NULL != entered_l) {
        int l = atoi(entered_l);
        if (is_correct_security_level(l)) {
            return l;
        }
    }
    return DEFAULT_SECURITY_LEVEL;
}

err_t start_command_run(int argc, char **argv, const char *file_state_name, err_t (*next_step)(int, bake_bpace_o *)) {
    err_t code;
    char *password = get_required_argument_value(argc, argv, PASSWORD_PARAMETER);
    int l = get_security_level_parameter(argc, argv);
    bake_bpace_o *state = get_state(password, l);
    NULL_CHECK(state)
    code = next_step(l, state);
    write_bpace_info_to_file(file_state_name, state, l);
    free(state);
    return code;
}

char *get_in_parameter(int argc, char **argv) {
    char *in = get_required_argument_value(argc, argv, IN_PARAMETER);
    char *dest = malloc(strlen(in));
    hexTo(dest, in);
    return dest;
}

