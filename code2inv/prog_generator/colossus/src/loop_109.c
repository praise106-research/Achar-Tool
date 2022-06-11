
/*
 * P-Hat Transformation
 * for Colossus : 109.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_109.h>
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

#define INV(a, m, j, k, c) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int a, int m, int j, int k, int c) {
    int f = preflag;
    setflag(INV(a, m, j, k, c), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "a", a, "m", m, "j", j, "k",
               k, "c", c);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_a, int temp_m, int temp_j, int temp_k, int temp_c, int a, int m, int j,
               int k, int c) {
    int f = loopflag;
    setflag(INV(a, m, j, k, c), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "a", temp_a, "m",
               temp_m, "j", temp_j, "k", temp_k, "c", temp_c);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "a", a, "m", m, "j", j,
               "k", k, "c", c);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, a, m, j, k, c)                              \
    \ 
{                                                              \
        \ 
    int f = postflag;                                               \
        \ 
   setflag(cond, postflag);                                         \
        \ 
    if (f == 0 && postflag == 1) {                                  \
            \ 
        printf("Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", \ 
 "a",                                                               \
               a, "m", m, "j", j, "k", k, "c", c); /* assert(0); */ \
        \ 
}                                                          \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int a;
    int m;
    int j;
    int k;
    int c;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&m, sizeof(m), "m_sym");
    klee_make_symbolic(&a, sizeof(a), "a_sym");
    klee_make_symbolic(&j, sizeof(j), "j_sym");
    klee_make_symbolic(&k, sizeof(k), "k_sym");
    klee_make_symbolic(&c, sizeof(c), "c_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (j = 0);
        (k = 0);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(a, m, j, k, c);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(a, m, j, k, c));
        // Loop Condition
        if ((k < c)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((k < c) && unroll--) {
                // assume((loopflag == 0));
                int temp_a = a;
                int temp_m = m;
                int temp_j = j;
                int temp_k = k;
                int temp_c = c;

                {
                    // loop body
                    if (m < a) {
                        m = a;
                    }
                    k = k + 1;
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_a, temp_m, temp_j, temp_k, temp_c, a, m, j, k, c);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if (c > 0) {
                postcheck((a <= m), a, m, j, k, c)
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
