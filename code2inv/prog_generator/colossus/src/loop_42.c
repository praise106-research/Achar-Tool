
/*
 * P-Hat Transformation
 * for Colossus : 42.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_42.h>
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

#define INV(c, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int c, int n) {
    int f = preflag;
    setflag(INV(c, n), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d\n", "c", c, "n", n);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_c, int temp_n, int c, int n) {
    int f = loopflag;
    setflag(INV(c, n), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d\n", "c", temp_c, "n", temp_n);
        printf("LoopEnd : %s : %d, %s : %d\n", "c", c, "n", n);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, c, n)               \
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
 "c",                                       \
               c, "n", n); /* assert(0); */ \
        \ 
}                                  \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int c;
    int n;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&n, sizeof(n), "n_sym");
    klee_make_symbolic(&c, sizeof(c), "c_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        klee_assume((n > 0));
        (c = 0);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(c, n);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(c, n));
        // Loop Condition
        if ((choices > 2500)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((choices > 2500) && unroll--) {
                // assume((loopflag == 0));
                int temp_c = c;
                int temp_n = n;

                {
                    // loop body
                    {
                        // non-deterministic
                        if (choices > 4500) {
                            if ((c > n)) {
                                (c = (c + 1));
                            }
                        } else {
                            if ((c == n)) {
                                (c = 1);
                            }
                        }
                    }
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_c, temp_n, c, n);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((c < 0)) {
                if ((c > n)) {
                    postcheck(((c == n)), c, n)
                }
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
