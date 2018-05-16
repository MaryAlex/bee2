//
// Created by Maria Chmyreva on 3/21/18.
//

#include <bee2/crypto/bake.h>
#include <memory.h>
#include <stdio.h>
#include "../../constants.h"

#ifndef OS_APPLE
    #include <malloc.h>
#else
    #include <stdlib.h>
#endif

char *get_full_file_name(const char *file_name) {
    char *full_name = malloc(strlen(file_name) + strlen(TMP_FILE_ENDING));
    strcpy(full_name, file_name);
    strcat(full_name, TMP_FILE_ENDING);
    return full_name;
}

/**
 *
 * @param file_name
 * @param in_modes - string of modes how open file
 * @return opened file with name file_name
 */
FILE *get_opened_file(const char *file_name, const char *in_modes) {
    FILE *file = NULL;
    char *full_name = get_full_file_name(file_name);
    if (NULL == (file = fopen(full_name, in_modes))) {
        printf("Can't open file with name %s in %s mode.\n", full_name, in_modes);
        return NULL;
    }
    return file;
}

int write_bpace_info_to_file(const char *file_name, bake_bpace_o *what, int l) {
    FILE *out;
    NULL_CHECK(out = get_opened_file(file_name, "w+"))
    // State have pointers inside it and we don't need all this fields, so we must write them manually,
    // So we will write data not memory address
    fwrite(&l, sizeof(int), 1, out);
    fwrite(what->R, sizeof(octet) * what->ec->f->no, 1, out);
    fwrite(what->u, sizeof(word) * what->ec->f->n, 1, out);
    fclose(out);
    return SUCCESS_CODE;
}

void fread_with_check(FILE *in, size_t size, void *to) {
    size_t objects_number = 1;
    if (fread(to, size, objects_number, in) != objects_number) {
        printf("Some error appear during reading from file");
    }
}

int read_security_level_from_file(const char *file_name, int *l) {
    FILE *in;
    NULL_CHECK(in = get_opened_file(file_name, "r"))
    fread_with_check(in, sizeof(int), l);
    fclose(in);
    return SUCCESS_CODE;
}

int read_state_from_file(const char *file_name, bake_bpace_o *what) {
    FILE *in;
    NULL_CHECK(in = get_opened_file(file_name, "r"))
    fseek(in, sizeof(int), SEEK_SET);
    fread_with_check(in, sizeof(octet) * what->ec->f->no, what->R);
    fread_with_check(in, sizeof(word) * what->ec->f->n, what->u);
    fclose(in);
    return SUCCESS_CODE;
}
