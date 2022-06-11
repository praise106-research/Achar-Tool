
/*
 * P-Hat Transformation
 * for Colossus : 94.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_94.h>
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

#define INV(i, j, k, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int i, int j, int k, int n) {
    int f = preflag;
    setflag(INV(i, j, k, n), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "k", k, "n", n);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_i, int temp_j, int temp_k, int temp_n, int i, int j, int k, int n) {
    int f = loopflag;
    setflag(INV(i, j, k, n), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", temp_i, "j", temp_j, "k",
               temp_k, "n", temp_n);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "k", k, "n", n);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, i, j, k, n)                         \
    \ 
{                                                      \
        \ 
    int f = postflag;                                       \
        \ 
   setflag(cond, postflag);                                 \
        \ 
    if (f == 0 && postflag == 1) {                          \
            \ 
        printf("Post : %s : %d, %s : %d, %s : %d, %s : %d\n", \ 
 "i",                                                       \
               i, "j", j, "k", k, "n", n); /* assert(0); */ \
        \ 
}                                                  \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int i;
    int j;
    int k;
    int n;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&k, sizeof(k), "k_sym");
    klee_make_symbolic(&n, sizeof(n), "n_sym");
    klee_make_symbolic(&i, sizeof(i), "i_sym");
    klee_make_symbolic(&j, sizeof(j), "j_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (i = 0);
        (j = 0);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(i, j, k, n);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(i, j, k, n));
        // Loop Condition
        if ((i <= n)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((i <= n) && unroll--) {
                // assume((loopflag == 0));
                int temp_i = i;
                int temp_j = j;
                int temp_k = k;
                int temp_n = n;

                {
                    // loop body
                    {
                        (i = (i + 1));
                        (j = (j + i));
                    }
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_i, temp_j, temp_k, temp_n, i, j, k, n);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            postcheck((((i + (j + k)) > (2 * n))), i, j, k, n)
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
