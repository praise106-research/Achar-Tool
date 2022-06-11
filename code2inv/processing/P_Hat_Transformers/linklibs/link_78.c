
/*
 * Linkage file for
 * for 78.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& i, long long int& x, long long int& y) {
    (i = 0);
    assume((x >= 0));
    assume((y >= 0));
    assume((x >= y));
}

void loopbody_f2(long long int choices, long long int& i, long long int& x, long long int& y) {
    {
        // loop body
        if ((i < y)) {
            (i = (i + 1));
        }
    }
}
