
/*
 * P-Hat Transformation
 * for Colossus : 115.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_115.h>
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

#define INV(sn, x) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int sn, int x) {
    int f = preflag;
    setflag(INV(sn, x), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d\n", "sn", sn, "x", x);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_sn, int temp_x, int sn, int x) {
    int f = loopflag;
    setflag(INV(sn, x), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d\n", "sn", temp_sn, "x", temp_x);
        printf("LoopEnd : %s : %d, %s : %d\n", "sn", sn, "x", x);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, sn, x)               \
    \ 
{                                       \
        \ 
    int f = postflag;                        \
        \ 
   setflag(cond, postflag);                  \
        \ 
    if (f == 0 && postflag == 1) {           \
            \ 
        printf("Post : %s : %d, %s : %d\n", \ 
 "sn",                                       \
               sn, "x", x); /* assert(0); */ \
        \ 
}                                   \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int sn;
    int x;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&sn, sizeof(sn), "sn_sym");
    klee_make_symbolic(&x, sizeof(x), "x_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (sn = 0);
        (x = 0);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(sn, x);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(sn, x));
        // Loop Condition
        if ((choices > 2500)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((choices > 2500) && unroll--) {
                // assume((loopflag == 0));
                int temp_sn = sn;
                int temp_x = x;

                {
                    // loop body
                    (x = (x + 1));
                    (sn = (sn + 1));
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_sn, temp_x, sn, x);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((sn != -1)) {
                postcheck(((sn == x)), sn, x)
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
