
/*
 * Linkage file for
 * for 130.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& d1, long long int& d2, long long int& d3,
                long long int& x1, long long int& x2, long long int& x3) {
    (d1 = 1);
    (d2 = 1);
    (d3 = 1);
    (x1 = 1);
}

void loopbody_f2(long long int choices, long long int& d1, long long int& d2, long long int& d3,
                 long long int& x1, long long int& x2, long long int& x3) {
    {
        // loop body
        if (x2 > 0) {
            if (x3 > 0) {
                x1 = x1 - d1;
                x2 = x2 - d2;
                x3 = x3 - d3;
            }
        }
    }
}
