
/*
 * Linkage file for
 * for 75.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& c, long long int& y, long long int& z) {
    (c = 0);
    assume((y >= 0));
    assume((y >= 127));
    (z = (36 * y));
}

void loopbody_f2(long long int choices, long long int& c, long long int& y, long long int& z) {
    {
        // loop body
        if ((c < 36)) {
            (z = (z + 1));
            (c = (c + 1));
        }
    }
}
