
/*
 * Linkage file for
 * for 94.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& i, long long int& j, long long int& k,
                long long int& n) {
    (i = 0);
    (j = 0);
}

void loopbody_f2(long long int choices, long long int& i, long long int& j, long long int& k,
                 long long int& n) {
    {
        // loop body
        {
            (i = (i + 1));
            (j = (j + i));
        }
    }
}
