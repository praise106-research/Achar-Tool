
/*
 * P-Hat Transformation
 * for Colossus : 16.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_16.h>
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

#define INV(x, m, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int x, int m, int n) {
    int f = preflag;
    setflag(INV(x, m, n), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d\n", "x", x, "m", m, "n", n);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_x, int temp_m, int temp_n, int x, int m, int n) {
    int f = loopflag;
    setflag(INV(x, m, n), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d\n", "x", temp_x, "m", temp_m, "n", temp_n);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d\n", "x", x, "m", m, "n", n);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, x, m, n)                    \
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
 "x",                                               \
               x, "m", m, "n", n); /* assert(0); */ \
        \ 
}                                          \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int x;
    int m;
    int n;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&x, sizeof(x), "x_sym");
    klee_make_symbolic(&m, sizeof(m), "m_sym");
    klee_make_symbolic(&n, sizeof(n), "n_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (x = 0);
        (m = 0);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(x, m, n);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(x, m, n));
        // Loop Condition
        if ((x < n)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x < n) && unroll--) {
                // assume((loopflag == 0));
                int temp_x = x;
                int temp_m = m;
                int temp_n = n;

                {
                    // loop body
                    // non-deterministic
                    if (choices > 4500) {
                        m = x;
                    }
                    x = x + 1;
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_x, temp_m, temp_n, x, m, n);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if (n > 0) {
                postcheck((m >= 0), x, m, n)
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
