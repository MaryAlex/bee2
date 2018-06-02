//
// Created by Maria Chmyreva on 3/21/18.
//

#include <bee2/crypto/bake.h>
#include <memory.h>
#include "../../constants.h"
#include <string_util.h>
#include <stdlib.h>

#ifndef OS_APPLE
    #include <malloc.h>
#endif

char *get_full_file_name(int argc, char **argv, const char *file_name) {
    char *user_id = get_optional_argument_value(argc, argv, USER_ID_PARAMETER);
    char *full_name = malloc(strlen(file_name) + strlen(TMP_FILE_ENDING));
    strcpy(full_name, file_name);
    if (NULL != user_id) {
        strcat(full_name, user_id);
    }
    strcat(full_name, TMP_FILE_ENDING);
    return full_name;
}

/**
 *
 * @param argc - argument count
 * @param argv - argument vector
 * @param file_name
 * @param in_modes - string of modes how open file
 * @return opened file with name file_name
 */
FILE *get_opened_file(int argc, char **argv, const char *file_name, const char *in_modes) {
    FILE *file = NULL;
    char *full_name = get_full_file_name(argc, argv, file_name);
    if (NULL == (file = fopen(full_name, in_modes))) {
        printf("Can't open file with name %s in %s mode.\n", full_name, in_modes);
        return NULL;
    }
    return file;
}

/**
 * Just fread function only with check that all objects were read and do exit otherwise
 * @param in file to read from
 * @param size of one object
 * @param objects_number number of objects that must be read
 * @param to pointеr to memory to where objects must be written
 */
void fread_with_check(FILE *in, size_t size, size_t objects_number, void *to) {
    if (fread(to, size, objects_number, in) < objects_number) {
        perror ("The following error occurred during reading");
        exit(FILE_READ_ERROR_CODE);
    }
}

/**
 * Just write function only with check that all objects were read and do exit otherwise
 * @param from pointеr to memory from where objects must be read
 * @param size of one object
 * @param objects_number number of objects that must be written
 * @param out  file to write to
 */
void fwrite_with_check(void *from, size_t size, size_t objects_number, FILE *out) {
    if (fwrite(from, size, objects_number, out) < objects_number) {
        perror ("The following error occurred during writing");
        exit(FILE_WRITE_ERROR_CODE);
    }
}

int write_bpace_info_to_file(int argc, char **argv, const char *file_name, bake_bpace_o *what, int l) {
    FILE *out;
    FILE_NULL_CHECK(out = get_opened_file(argc, argv, file_name, "wb+"))
    // State have pointers inside it and we don't need all this fields, so we must write them manually,
    // So we will write data not memory address
    fwrite_with_check(&l, sizeof(int), 1, out);
    fwrite_with_check(what->R, sizeof(octet), what->ec->f->no, out);
    fwrite_with_check(what->u, sizeof(word), what->ec->f->n, out);
    fclose(out);
    return SUCCESS_CODE;
}

err_t read_security_level_from_file(int argc, char **argv, const char *file_name, int *l) {
    FILE *in;
    FILE_NULL_CHECK(in = get_opened_file(argc, argv, file_name, "rb"))
    fread_with_check(in, sizeof(int), 1, l);
    fclose(in);
    return SUCCESS_CODE;
}

int read_state_from_file(int argc, char **argv, const char *file_name, bake_bpace_o *what) {
    FILE *in;
    FILE_NULL_CHECK(in = get_opened_file(argc, argv, file_name, "rb"))
    fseek(in, sizeof(int), SEEK_SET);
    fread_with_check(in, sizeof(octet), what->ec->f->no, what->R);
    fread_with_check(in, sizeof(word), what->ec->f->n, what->u);
    fclose(in);
    return SUCCESS_CODE;
}
