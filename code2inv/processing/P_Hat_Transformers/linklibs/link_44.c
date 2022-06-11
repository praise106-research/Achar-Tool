
/*
 * Linkage file for
 * for 44.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& c, long long int& n) {
    assume((n > 0));
    (c = 0);
}

void loopbody_f2(long long int choices, long long int& c, long long int& n) {
    {
        // loop body
        {
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
}
