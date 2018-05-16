//
// Created by Maria Chmyreva on 3/21/18.
//

#include <bee2/defs.h>
#include <bee2/crypto/bake.h>
#include "../constants.h"

#ifndef BEE2_BPACE_UTIL_H
#define BEE2_BPACE_UTIL_H

/**
 * @brief Do memory allocation and initialization for bpace state and other structs that can be needed from given parameters
 * @param password
 * @param l - security level
 * @return Initialized bpace state
 */
bake_bpace_o *get_state(char *password, int l);

/**
 * @brief Do memory allocation for bpace state and other structs that can be needed.
 *        Security level takes from file with name file_state_name.
 *        Then init states Ra, Rb(or V instead both R) and U(Ua or Ub) from the same file.
 * @param password
 * @param file_state_name
 * @param l - reference to int where we will save security level from file. Must be passed by reference
 * @return Initialized bpace state
 */
bake_bpace_o *get_state_from_file(char *password, const char *file_state_name, int *l);

/**
 * @brief Call bakeBPACEStepG. Print common key. Remove state file.
 * @param state
 * @param file_state_name
 * @return code of error or success code
 */
err_t final_step_run(bake_bpace_o *state, const char *file_state_name);

/**
 * @brief Initialize state. Call next_step. Write state to file.
 * @param argc - argument count
 * @param argv - argument vector
 * @param file_state_name
 * @param next_step - first step after bakeBPACEStart in bpace protocol for current side
 * @return code of error or success code
 */
err_t start_command_run(int argc, char **argv, const char *file_state_name, err_t (*next_step)(int, bake_bpace_o *));

/**
 * @param argc - argument count
 * @param argv - argument vector
 * @return -in parameter
 */
char *get_in_parameter(int argc, char **argv);
/**
 * @param argc - argument count
 * @param argv - argument vector
 * @return -l(security level) parameter
 */
int get_security_level_parameter(int argc, char **argv);

/**
 * @brief Print readable string of answer bytes
 * @param preface - text that contains preface to output. Must contain at least %s
 * @param answer - reference to bytes to output.
 * @param size - count of answer's bytes
 */
void printAnswer(const char *preface, void *answer, size_t size);

#endif //BEE2_BPACE_UTIL_H
