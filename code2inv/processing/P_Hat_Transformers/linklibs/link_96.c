
/*
 * Linkage file for
 * for 96.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& i, long long int& j, long long int& x,
                long long int& y) {
    (j = 0);
    (i = 0);
    (y = 1);
}

void loopbody_f2(long long int choices, long long int& i, long long int& j, long long int& x,
                 long long int& y) {
    {
        // loop body
        {
            (i = (i + 1));
            (j = (j + y));
        }
    }
}
