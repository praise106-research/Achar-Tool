
/*
 * P-Hat Transformation
 * for Colossus : 52.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_52.h>
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

#define INV(c) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int c) {
    int f = preflag;
    setflag(INV(c), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d\n", "c", c);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_c, int c) {
    int f = loopflag;
    setflag(INV(c), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d\n", "c", temp_c);
        printf("LoopEnd : %s : %d\n", "c", c);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, c)          \
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
 "c",                               \
               c); /* assert(0); */ \
        \ 
}                          \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int c;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&c, sizeof(c), "c_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (c = 0);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(c);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(c));
        // Loop Condition
        if ((choices > 2500)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((choices > 2500) && unroll--) {
                // assume((loopflag == 0));
                int temp_c = c;

                {
                    // loop body
                    {
                        // non-deterministic
                        if (choices > 4500) {
                            if ((c != 4)) {
                                (c = (c + 1));
                            }
                        } else {
                            if ((c == 4)) {
                                (c = 1);
                            }
                        }
                    }
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_c, c);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((c < 0)) {
                if ((c > 4)) {
                    postcheck(((c == 4)), c)
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
