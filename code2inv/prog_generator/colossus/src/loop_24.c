
/*
 * P-Hat Transformation
 * for Colossus : 24.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <limits.h>
#include <loop_24.h>
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

#define INV(i, j) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int i, int j) {
    int f = preflag;
    setflag(INV(i, j), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d\n", "i", i, "j", j);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_i, int temp_j, int i, int j) {
    int f = loopflag;
    setflag(INV(i, j), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d\n", "i", temp_i, "j", temp_j);
        printf("LoopEnd : %s : %d, %s : %d\n", "i", i, "j", j);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, i, j)               \
    \ 
{                                      \
        \ 
    int f = postflag;                       \
        \ 
   setflag(cond, postflag);                 \
        \ 
    if (f == 0 && postflag == 1) {          \
            \ 
        printf("Post : %s : %d, %s : %d\n", \ 
 "i",                                       \
               i, "j", j); /* assert(0); */ \
        \ 
}                                  \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int i;
    int j;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&i, sizeof(i), "i_sym");
    klee_make_symbolic(&j, sizeof(j), "j_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // klee_assume(i < INT_MAX);
    // klee_assume(j < INT_MAX);

    // Translate() Colossus
    if (choices > 10000) {
        i = 1;
        j = 10;
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(i, j);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(i, j));
        // Loop Condition
        if (j >= i) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((j >= i) && unroll--) {
                // assume((loopflag == 0));
                int temp_i = i;
                int temp_j = j;

                // loop body
                i = i + 2;
                j = j - 1;
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_i, temp_j, i, j);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");
            // post-condition
            postcheck((j == 6), i, j)
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
