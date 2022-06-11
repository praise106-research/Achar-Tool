
/*
 * P-Hat Transformation
 * for Colossus : 118.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_118.h>
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

#define INV(i, size, sn) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int i, int size, int sn) {
    int f = preflag;
    setflag(INV(i, size, sn), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d\n", "i", i, "size", size, "sn", sn);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_i, int temp_size, int temp_sn, int i, int size, int sn) {
    int f = loopflag;
    setflag(INV(i, size, sn), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d\n", "i", temp_i, "size", temp_size, "sn",
               temp_sn);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d\n", "i", i, "size", size, "sn", sn);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, i, size, sn)                        \
    \ 
{                                                      \
        \ 
    int f = postflag;                                       \
        \ 
   setflag(cond, postflag);                                 \
        \ 
    if (f == 0 && postflag == 1) {                          \
            \ 
        printf("Post : %s : %d, %s : %d, %s : %d\n", \ 
 "i",                                                       \
               i, "size", size, "sn", sn); /* assert(0); */ \
        \ 
}                                                  \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int i;
    int size;
    int sn;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&i, sizeof(i), "i_sym");
    klee_make_symbolic(&sn, sizeof(sn), "sn_sym");
    klee_make_symbolic(&size, sizeof(size), "size_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (sn = 0);
        (i = 1);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(i, size, sn);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(i, size, sn));
        // Loop Condition
        if ((i <= size)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((i <= size) && unroll--) {
                // assume((loopflag == 0));
                int temp_i = i;
                int temp_size = size;
                int temp_sn = sn;

                {
                    // loop body
                    (i = (i + 1));
                    (sn = (sn + 1));
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_i, temp_size, temp_sn, i, size, sn);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((sn != size)) {
                postcheck(((sn == 0)), i, size, sn)
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
