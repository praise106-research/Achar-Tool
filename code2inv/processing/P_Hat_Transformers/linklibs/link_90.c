
/*
 * Linkage file for
 * for 90.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& lock, long long int& x, long long int& y,
                long long int& v1, long long int& v2, long long int& v3) {
    (y = (x + 1));  // sum_opaque
    (lock = 0);
}

void loopbody_f2(long long int choices, long long int& lock, long long int& x, long long int& y,
                 long long int& v1, long long int& v2, long long int& v3) {
    {
        // loop body
        // non-deterministic
        if (choices > 3500) {
            {
                (lock = 1);
                (x = y);
            }
        } else {
            {
                (lock = 0);
                (x = y);
                (y = (y + 1));
            }
        }
    }
}
