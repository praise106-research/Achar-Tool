
/*
 * Linkage file for
 * for 6.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& v1, long long int& v2, long long int& v3,
                long long int& x, long long int& size, long long int& y, long long int& z) {
    (x = 0);
}

void loopbody_f2(long long int choices, long long int& v1, long long int& v2, long long int& v3,
                 long long int& x, long long int& size, long long int& y, long long int& z) {
    {
        // loop body
        x = x + 1;
        if (z <= y) {
            y = z;
        }
    }
}
