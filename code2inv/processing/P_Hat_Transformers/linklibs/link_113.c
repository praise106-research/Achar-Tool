
/*
 * Linkage file for
 * for 113.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& i, long long int& n, long long int& sn,
                long long int& v1, long long int& v2, long long int& v3) {
    (sn = 0);
    (i = 1);
}

void loopbody_f2(long long int choices, long long int& i, long long int& n, long long int& sn,
                 long long int& v1, long long int& v2, long long int& v3) {
    {
        // loop body
        (i = (i + 1));
        (sn = (sn + 1));
    }
}
