
/*
 * P-Hat Transformation
 * for Colossus : 131.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <limits.h>
#include <loop_131.h>
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

#define INV(d1, d2, d3, x1, x2, x3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int d1, int d2, int d3, int x1, int x2, int x3) {
    int f = preflag;
    setflag(INV(d1, d2, d3, x1, x2, x3), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "d1", d1, "d2", d2,
               "d3", d3, "x1", x1, "x2", x2, "x3", x3);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_d1, int temp_d2, int temp_d3, int temp_x1, int temp_x2, int temp_x3, int d1,
               int d2, int d3, int x1, int x2, int x3) {
    int f = loopflag;
    setflag(INV(d1, d2, d3, x1, x2, x3), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "d1", temp_d1,
               "d2", temp_d2, "d3", temp_d3, "x1", temp_x1, "x2", temp_x2, "x3", temp_x3);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "d1", d1, "d2",
               d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, d1, d2, d3, x1, x2, x3)                                        \
    \ 
{                                                                                 \
        \ 
    int f = postflag;                                                                  \
        \ 
   setflag(cond, postflag);                                                            \
        \ 
    if (f == 0 && postflag == 1) {                                                     \
            \ 
        printf("Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", \ 
 "d1",                                                                                 \
               d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3); /* assert(0); */ \
        \ 
}                                                                             \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int d1 = 1;
    int d2 = 1;
    int d3 = 1;
    int x1;
    int x2;
    int x3;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&x1, sizeof(x1), "x1_sym");
    klee_make_symbolic(&x2, sizeof(x2), "x2_sym");
    klee_make_symbolic(&x3, sizeof(x3), "x3_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    klee_assume(x1 < INT_MAX);
    klee_assume(x2 < INT_MAX);
    klee_assume(x3 < INT_MAX);

    // Translate() Colossus
    if (choices > 10000) {
        d1 = 1;
        d2 = 1;
        d3 = 1;
        x1 = 1;
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(d1, d2, d3, x1, x2, x3);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(d1, d2, d3, x1, x2, x3));
        // Loop Condition
        if ((x1 > 0)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x1 > 0) && unroll--) {
                // assume((loopflag == 0));
                int temp_d1 = d1;
                int temp_d2 = d2;
                int temp_d3 = d3;
                int temp_x1 = x1;
                int temp_x2 = x2;
                int temp_x3 = x3;

                // loop body
                if (x2 > 0) {
                    if (x3 > 0) {
                        x1 = x1 - d1;
                        x2 = x2 - d2;
                        x3 = x3 - d3;
                    }
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_d1, temp_d2, temp_d3, temp_x1, temp_x2, temp_x3, d1, d2, d3, x1, x2,
                          x3);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            postcheck((x3 >= 0), d1, d2, d3, x1, x2, x3)
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
