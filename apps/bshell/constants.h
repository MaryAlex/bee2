//
// Created by Maria Chmyreva on 3/18/18.
//

#ifndef BEE2_CONSTANTS_H
#define BEE2_CONSTANTS_H

#include <bee2/math/ec.h>
#include <bee2/crypto/bake.h>

#define ERROR_CODE 1
#define SUCCESS_CODE 0

#define OCTET_SIZE 8
#define KEY_SIZE 32

// All sizes below are divided by octet size so we can get size in bytes
#define SIZE_OF_BOB_FIRST_MESSAGE(l) ((l) / OCTET_SIZE) // Just Yb(l)
#define SIZE_OF_BOB_SECOND_MESSAGE(l) (4 * (l) / OCTET_SIZE) // Just Vb(4l)
#define SIZE_OF_ALICE_FIRST_MESSAGE(l) (5 * (l) / OCTET_SIZE) // Size of Ya(l) + size of Va(4l)

/**
 * @brief Return ERROR_CODE if NULL
 */
#define NULL_CHECK(variable)\
    if (NULL == (variable)) {\
        return ERROR_CODE;\
    }

/**
* @brief Return NULL if NULL
*/
#define NULL_CHECK_FOR_POINTER_FUNCTION(variable)\
    if (NULL == (variable)) {\
        return NULL;\
    }

/**
 * @brief Code check and print error, if needed
 */
#define CODE_CHECK(code, on_success)\
    if (SUCCESS_CODE == (code)) {\
        (on_success);\
    } else if (ERR_BAD_POINT == (code)) {\
        printf("Bad point error");\
    } else if (ERR_BAD_INPUT == (code)) {\
        printf("Bad input error");\
    }  else {\
        printf("Some error appear during step: ===%d===\n", code);\
    }

/**
 * @brief Code check and print error, if needed. Do return from function
 */
#define CODE_CHECK_WITH_RETURN(code, return_value)\
    if (SUCCESS_CODE == (code)) {\
        return (return_value);\
    } else if (ERR_BAD_POINT == (code)) {\
        printf("Bad point error");\
    } else if (ERR_BAD_INPUT == (code)) {\
        printf("Bad input error");\
    } else {\
        printf("Some error appear during step: ===%d===\n", code);\
    }


static const int possible_security_levels[] = {128, 192, 256};

static const int POSSIBLE_SECURITY_LEVELS_SIZE = 3;
static const int DEFAULT_SECURITY_LEVEL = 128;

/**
 * @brief ending for file creating by this program
 */
static const char TMP_FILE_ENDING[] = ".bs";

/**
 * @brief file state default name during bpace for Alice's functions and for Bob's
 */
static const char FILE_STATE_BOB_NAME[] = "bpaceBobState";
static const char FILE_STATE_ALICE_NAME[] = "bpaceAliceState";


/**
 * @brief parameters that user can input
 */
static const char PASSWORD_PARAMETER[] = "password";
static const char IN_PARAMETER[] = "in";
static const char SECURITY_LEVEL_PARAMETER[] = "l";

#endif //BEE2_CONSTANTS_H
