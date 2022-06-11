
/*
 * Linkage file for
 * for 53.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& c, long long int& n, long long int& v1,
                long long int& v2, long long int& v3) {
    (c = 0);
    assume((n > 0));
}

void loopbody_f2(long long int choices, long long int& c, long long int& n, long long int& v1,
                 long long int& v2, long long int& v3) {
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
