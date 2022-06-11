
/*
 * P-Hat Transformation
 * for Colossus : 62.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_62.h>
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

#define INV(c, n, v1, v2, v3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int c, int n, int v1, int v2, int v3) {
    int f = preflag;
    setflag(INV(c, n, v1, v2, v3), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "c", c, "n", n, "v1", v1,
               "v2", v2, "v3", v3);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_c, int temp_n, int temp_v1, int temp_v2, int temp_v3, int c, int n, int v1,
               int v2, int v3) {
    int f = loopflag;
    setflag(INV(c, n, v1, v2, v3), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "c", temp_c, "n",
               temp_n, "v1", temp_v1, "v2", temp_v2, "v3", temp_v3);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "c", c, "n", n, "v1", v1,
               "v2", v2, "v3", v3);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, c, n, v1, v2, v3)                                 \
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
 "c",                                                                     \
               c, "n", n, "v1", v1, "v2", v2, "v3", v3); /* assert(0); */ \
        \ 
}                                                                \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int c;
    int n;
    int v1 = 0;
    int v2 = 0;
    int v3 = 0;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&n, sizeof(n), "n_sym");
    klee_make_symbolic(&c, sizeof(c), "c_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (c = 0);
        klee_assume((n > 0));
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(c, n, v1, v2, v3);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(c, n, v1, v2, v3));
        // Loop Condition
        if ((choices > 2500)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((choices > 2500) && unroll--) {
                // assume((loopflag == 0));
                int temp_c = c;
                int temp_n = n;
                int temp_v1 = v1;
                int temp_v2 = v2;
                int temp_v3 = v3;

                {
                    // loop body
                    {
                        // non-deterministic
                        if (choices > 4500) {
                            if ((c != n)) {
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
                loopcheck(temp_c, temp_n, temp_v1, temp_v2, temp_v3, c, n, v1, v2, v3);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((n > -1)) {
                postcheck(((c != n)), c, n, v1, v2, v3)
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
