
/*
 * Linkage file for
 * for 84.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& x, long long int& y) { (x = -50); }

void loopbody_f2(long long int choices, long long int& x, long long int& y) {
    {
        // loop body
        {
            (x = (x + y));
            (y = (y + 1));
        }
    }
}
