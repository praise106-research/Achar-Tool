
/*
 * Linkage file for
 * for 93.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& i, long long int& n, long long int& x,
                long long int& y) {
    assume((n >= 0));
    (i = 0);
    (x = 0);
    (y = 0);
}

void loopbody_f2(long long int choices, long long int& i, long long int& n, long long int& x,
                 long long int& y) {
    {
        // loop body
        (i = (i + 1));
        // non-deterministic
        if (choices > 3500) {
            (x = (x + 1));
            (y = (y + 2));
        } else {
            (x = (x + 2));
            (y = (y + 1));
        }
    }
}
