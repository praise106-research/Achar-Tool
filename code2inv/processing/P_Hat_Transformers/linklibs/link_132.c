
/*
 * Linkage file for
 * for 132.c file
 */

#include <stdio.h>
#include <stdlib.h>

#define assume(cond) \
    if (!(cond)) exit(0);

void prebody_f1(long long int choices, long long int& i, long long int& j, long long int& c,
                long long int& t) {
    (i = 0);
}

void loopbody_f2(long long int choices, long long int& i, long long int& j, long long int& c,
                 long long int& t) {
    {
        // loop body
        if (c > 48) {
            if (c < 57) {
                j = i + i;
                t = c - 48;
                i = j + t;
            }
        }
    }
}
