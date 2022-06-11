
/*
 * Linkage file for
 * for 36.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& c) { (c = 0); }

void loopbody_f2(long long int choices, long long int& c) {
    {
        // loop body
        // non-deterministic
        if (choices > 3500) {
            if ((c != 40)) {
                (c = (c + 1));
            }
        } else {
            if ((c == 40)) {
                (c = 1);
            }
        }
    }
}
