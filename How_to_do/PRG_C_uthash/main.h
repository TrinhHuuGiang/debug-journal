/**
 * Test uthash
 * Refer guide: https://troydhanson.github.io/uthash/userguide.html
 */

// C
#include <stdio.h>  // print
#include <string.h> // 
#include <stdlib.h> // allocate, random
#include <time.h>   // get time to randome

// UT
#include "uthash.h"



/**
 * ***************************************************
 * Definition
 * ***************************************************
 */

typedef enum
{
    UTH_ER_MALLOC_FAIL,
    UTH_ER_DUPLICATED_KEY_DETECTED,

} uh_err_ret;