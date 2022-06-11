
/*
 * Linkage file for
 * for 23.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& i, long long int& j) {
    (i = 1);
    (j = 20);
}

void loopbody_f2(long long int choices, long long int& i, long long int& j) {
    {
        // loop body
        (i = (i + 2));
        (j = (j - 1));
    }
}
