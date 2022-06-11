
/*
 * Linkage file for
 * for 114.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& sn, long long int& v1, long long int& v2,
                long long int& v3, long long int& x) {
    (sn = 0);
    (x = 0);
}

void loopbody_f2(long long int choices, long long int& sn, long long int& v1, long long int& v2,
                 long long int& v3, long long int& x) {
    {
        // loop body
        (x = (x + 1));
        (sn = (sn + 1));
    }
}
