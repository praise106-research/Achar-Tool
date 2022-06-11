
/*
 * Linkage file for
 * for 106.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& a, long long int& m, long long int& j,
                long long int& k) {
    assume(a <= m);
    assume(j < 1);
    (k = 0);
}

void loopbody_f2(long long int choices, long long int& a, long long int& m, long long int& j,
                 long long int& k) {
    {
        // loop body
        if (m < a) {
            m = a;
        }
        k = k + 1;
    }
}
