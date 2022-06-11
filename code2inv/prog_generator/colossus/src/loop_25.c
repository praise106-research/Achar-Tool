
/*
 * P-Hat Transformation
 * for Colossus : 25.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_25.h>
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

#define INV(x) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int x) {
    int f = preflag;
    setflag(INV(x), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d\n", "x", x);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_x, int x) {
    int f = loopflag;
    setflag(INV(x), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d\n", "x", temp_x);
        printf("LoopEnd : %s : %d\n", "x", x);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, x)          \
    \ 
{                              \
        \ 
    int f = postflag;               \
        \ 
   setflag(cond, postflag);         \
        \ 
    if (f == 0 && postflag == 1) {  \
            \ 
        printf("Post : %s : %d\n", \ 
 "x",                               \
               x); /* assert(0); */ \
        \ 
}                          \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int x;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&x, sizeof(x), "x_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (x = 10000);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(x);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(x));
        // Loop Condition
        if ((x > 0)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x > 0) && unroll--) {
                // assume((loopflag == 0));
                int temp_x = x;

                {
                    // loop body
                    (x = (x - 1));
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_x, x);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            postcheck(((x == 0)), x)
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
