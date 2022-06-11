
/*
 * P-Hat Transformation
 * for Colossus : 113.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_113.h>
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

#define INV(i, n, sn, v1, v2, v3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int i, int n, int sn, int v1, int v2, int v3) {
    int f = preflag;
    setflag(INV(i, n, sn, v1, v2, v3), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "n", n, "sn",
               sn, "v1", v1, "v2", v2, "v3", v3);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_i, int temp_n, int temp_sn, int temp_v1, int temp_v2, int temp_v3, int i,
               int n, int sn, int v1, int v2, int v3) {
    int f = loopflag;
    setflag(INV(i, n, sn, v1, v2, v3), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", temp_i,
               "n", temp_n, "sn", temp_sn, "v1", temp_v1, "v2", temp_v2, "v3", temp_v3);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "n", n,
               "sn", sn, "v1", v1, "v2", v2, "v3", v3);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, i, n, sn, v1, v2, v3)                                       \
    \ 
{                                                                              \
        \ 
    int f = postflag;                                                               \
        \ 
   setflag(cond, postflag);                                                         \
        \ 
    if (f == 0 && postflag == 1) {                                                  \
            \ 
        printf("Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", \ 
 "i",                                                                               \
               i, "n", n, "sn", sn, "v1", v1, "v2", v2, "v3", v3); /* assert(0); */ \
        \ 
}                                                                          \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int i;
    int n;
    int sn;
    int v1 = 0;
    int v2 = 0;
    int v3 = 0;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&n, sizeof(n), "n_sym");
    klee_make_symbolic(&sn, sizeof(sn), "sn_sym");
    klee_make_symbolic(&i, sizeof(i), "i_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (sn = 0);
        (i = 1);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(i, n, sn, v1, v2, v3);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(i, n, sn, v1, v2, v3));
        // Loop Condition
        if ((i <= n)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((i <= n) && unroll--) {
                // assume((loopflag == 0));
                int temp_i = i;
                int temp_n = n;
                int temp_sn = sn;
                int temp_v1 = v1;
                int temp_v2 = v2;
                int temp_v3 = v3;

                {
                    // loop body
                    (i = (i + 1));
                    (sn = (sn + 1));
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_i, temp_n, temp_sn, temp_v1, temp_v2, temp_v3, i, n, sn, v1, v2, v3);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((sn != 0)) {
                postcheck(((sn == n)), i, n, sn, v1, v2, v3)
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
