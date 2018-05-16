//
// Created by Maria Chmyreva on 3/21/18.
//

#ifndef BEE2_FILE_UTIL_H
#define BEE2_FILE_UTIL_H

#include "../constants.h"
/**
 *
 * @param file_name
 * @return file_name plus TMP_FILE_ENDING
 */
char *get_full_file_name(const char *file_name);
/**
 *
 * @param in - reference to file where we will keep our opened file to use and close it later
 * @param file_name
 * @param l - reference to int where we will save security level from file. Must be passed by reference
 * @return code of error or success code
 */
int read_security_level_from_file(char *file_name, int *l);
/**
 * @brief Writing Ra, Rb(or V instead of both R), U(Ua or Ub) and l to binary file.
 *        Firstly l then others fields from 'what'.
 * @param file_name
 * @param what - state of bpace
 * @param l - security level
 * @return code of error or success code
 */
int write_bpace_info_to_file(const char *file_name, bake_bpace_o *what, int l);
/**
 * @brief Reading Ra, Rb(or V instead of both R), U(Ua or Ub) and l to binary file.
 * @param in - reference to file
 * @param what - state of bpace where fields will be saved
 */
int read_state_from_file(char *file_name, bake_bpace_o *what);

#endif //BEE2_FILE_UTIL_H
