
/*
 * Linkage file for
 * for 16.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& x, long long int& m, long long int& n) {
    (x = 0);
    (m = 0);
}

void loopbody_f2(long long int choices, long long int& x, long long int& m, long long int& n) {
    {
        // loop body
        // non-deterministic
        if (choices > 3500) {
            m = x;
        }
        x = x + 1;
    }
}
