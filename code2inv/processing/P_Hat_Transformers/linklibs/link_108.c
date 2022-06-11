
/*
 * Linkage file for
 * for 108.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& a, long long int& m, long long int& j,
                long long int& k, long long int& c) {
    assume((a <= m));
    (j = 0);
    (k = 0);
}

void loopbody_f2(long long int choices, long long int& a, long long int& m, long long int& j,
                 long long int& k, long long int& c) {
    {
        // loop body
        if (m < a) {
            m = a;
        }
        k = k + 1;
    }
}
