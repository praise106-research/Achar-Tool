
/*
 * Linkage file for
 * for 40.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& n, long long int& c) {
    assume(n > 0);
    (c = 0);
}

void loopbody_f2(long long int choices, long long int& n, long long int& c) {
    {
        // loop body
        // non-deterministic
        if (choices > 3500) {
            if ((c > n)) {
                (c = (c + 1));
            }
        } else {
            if ((c == n)) {
                (c = 1);
            }
        }
    }
}
