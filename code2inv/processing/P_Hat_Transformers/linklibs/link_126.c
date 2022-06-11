
/*
 * Linkage file for
 * for 126.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& i, long long int& j, long long int& x,
                long long int& y, long long int& z1, long long int& z2, long long int& z3) {
    (i = x);
    (j = y);
}

void loopbody_f2(long long int choices, long long int& i, long long int& j, long long int& x,
                 long long int& y, long long int& z1, long long int& z2, long long int& z3) {
    {
        // loop body
        (x = (x - 1));
        (y = (y - 1));
    }
}
