
/*
 * Linkage file for
 * for 100.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& n, long long int& x, long long int& y) {
    (x = n);
    (y = 0);
}

void loopbody_f2(long long int choices, long long int& n, long long int& x, long long int& y) {
    {
        // loop body
        {
            (y = (y + 1));
            (x = (x - 1));
        }
    }
}
