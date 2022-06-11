
/*
 * Linkage file for
 * for 68.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& x, long long int& y, long long int& n) {
    (x = 1);
}

void loopbody_f2(long long int choices, long long int& x, long long int& y, long long int& n) {
    {
        // loop body
        y = n - x;
        x = x + 1;
    }
}
