
/*
 * P-Hat Transformation
 * for Colossus : 31.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_31.h>
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

#define INV(n, v1, v2, v3, x) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int n, int v1, int v2, int v3, int x) {
    int f = preflag;
    setflag(INV(n, v1, v2, v3, x), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", n, "v1", v1, "v2", v2,
               "v3", v3, "x", x);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_n, int temp_v1, int temp_v2, int temp_v3, int temp_x, int n, int v1, int v2,
               int v3, int x) {
    int f = loopflag;
    setflag(INV(n, v1, v2, v3, x), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", temp_n, "v1",
               temp_v1, "v2", temp_v2, "v3", temp_v3, "x", temp_x);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", n, "v1", v1, "v2",
               v2, "v3", v3, "x", x);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, n, v1, v2, v3, x)                                 \
    \ 
{                                                                    \
        \ 
    int f = postflag;                                                     \
        \ 
   setflag(cond, postflag);                                               \
        \ 
    if (f == 0 && postflag == 1) {                                        \
            \ 
        printf("Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", \ 
 "n",                                                                     \
               n, "v1", v1, "v2", v2, "v3", v3, "x", x); /* assert(0); */ \
        \ 
}                                                                \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int n;
    int v1 = 0;
    int v2 = 0;
    int v3 = 0;
    int x;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&x, sizeof(x), "x_sym");
    klee_make_symbolic(&n, sizeof(n), "n_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (x = n);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(n, v1, v2, v3, x);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(n, v1, v2, v3, x));
        // Loop Condition
        if ((x > 1)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x > 1) && unroll--) {
                // assume((loopflag == 0));
                int temp_n = n;
                int temp_v1 = v1;
                int temp_v2 = v2;
                int temp_v3 = v3;
                int temp_x = x;

                {
                    // loop body
                    (x = (x - 1));
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_n, temp_v1, temp_v2, temp_v3, temp_x, n, v1, v2, v3, x);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((x != 1)) {
                postcheck(((n < 0)), n, v1, v2, v3, x)
            }
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
