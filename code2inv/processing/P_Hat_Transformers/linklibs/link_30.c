
/*
 * Linkage file for
 * for 30.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& x) { (x = 100); }

void loopbody_f2(long long int choices, long long int& x) {
    {
        // loop body
        (x = (x - 1));
    }
}
