
/*
 * P-Hat Transformation
 * for Colossus : 39.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_39.h>
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

#define INV(n, c) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int n, int c) {
    int f = preflag;
    setflag(INV(n, c), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d\n", "n", n, "c", c);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_n, int temp_c, int n, int c) {
    int f = loopflag;
    setflag(INV(n, c), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d\n", "n", temp_n, "c", temp_c);
        printf("LoopEnd : %s : %d, %s : %d\n", "n", n, "c", c);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, n, c)               \
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
 "n",                                       \
               n, "c", c); /* assert(0); */ \
        \ 
}                                  \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int n;
    int c;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&n, sizeof(n), "n_sym");
    klee_make_symbolic(&c, sizeof(c), "c_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        klee_assume(n > 0);
        (c = 0);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(n, c);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(n, c));
        // Loop Condition
        if ((choices > 2500)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((choices > 2500) && unroll--) {
                // assume((loopflag == 0));
                int temp_n = n;
                int temp_c = c;

                {
                    // loop body
                    if (c == n) {
                        c = 1;
                    } else {
                        c = c + 1;
                    }
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_n, temp_c, n, c);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if (c == n) {
                postcheck((c >= 0), n, c) postcheck((c <= n), n, c)
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
