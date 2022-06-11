
/*
 * P-Hat Transformation
 * for Colossus : 100.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_100.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

#define UNROLL_LIMIT 1

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) exit(0);

#define INV(n, x, y) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int n, int x, int y) {
    int f = preflag;
    setflag(INV(n, x, y), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d\n", "n", n, "x", x, "y", y);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_n, int temp_x, int temp_y, int n, int x, int y) {
    int f = loopflag;
    setflag(INV(n, x, y), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d\n", "n", temp_n, "x", temp_x, "y", temp_y);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d\n", "n", n, "x", x, "y", y);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, n, x, y)                    \
    \ 
{                                              \
        \ 
    int f = postflag;                               \
        \ 
   setflag(cond, postflag);                         \
        \ 
    if (f == 0 && postflag == 1) {                  \
            \ 
        printf("Post : %s : %d, %s : %d, %s : %d\n", \ 
 "n",                                               \
               n, "x", x, "y", y); /* assert(0); */ \
        \ 
}                                          \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int n;
    int x;
    int y;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&n, sizeof(n), "n_sym");
    klee_make_symbolic(&x, sizeof(x), "x_sym");
    klee_make_symbolic(&y, sizeof(y), "y_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (x = n);
        (y = 0);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(n, x, y);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(n, x, y));
        // Loop Condition
        if ((x > 0)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x > 0) && unroll--) {
                // assume((loopflag == 0));
                int temp_n = n;
                int temp_x = x;
                int temp_y = y;

                {
                    // loop body
                    {
                        (y = (y + 1));
                        (x = (x - 1));
                    }
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_n, temp_x, temp_y, n, x, y);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            postcheck(((y == n)), n, x, y)
        }
    }

    // Print the counters if no flags are hit
    if (preflag + loopflag + postflag == 0 && counter == 100) {
        printf("%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount", loopcount,
               "postcount", postcount);
        counter = 0;
    }

    // Regular Close FILE
    return 0;
}
