
/*
 * Linkage file for
 * for 21.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& z1, long long int& z2, long long int& z3,
                long long int& x, long long int& m, long long int& n) {
    (x = 1);
    (m = 1);
}

void loopbody_f2(long long int choices, long long int& z1, long long int& z2, long long int& z3,
                 long long int& x, long long int& m, long long int& n) {
    {
        // loop body
        // non-deterministic
        if (choices > 3500) {
            m = x;
        }
        x = x + 1;
    }
}
