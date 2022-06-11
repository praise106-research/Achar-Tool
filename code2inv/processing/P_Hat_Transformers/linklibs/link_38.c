
/*
 * Linkage file for
 * for 38.c file
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
        if (c == n) {
            c = 1;
        } else {
            c = c + 1;
        }
    }
}
