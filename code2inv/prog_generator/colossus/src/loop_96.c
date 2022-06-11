
/*
 * P-Hat Transformation
 * for Colossus : 96.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_96.h>
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

#define INV(i, j, x, y) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int i, int j, int x, int y) {
    int f = preflag;
    setflag(INV(i, j, x, y), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_i, int temp_j, int temp_x, int temp_y, int i, int j, int x, int y) {
    int f = loopflag;
    setflag(INV(i, j, x, y), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", temp_i, "j", temp_j, "x",
               temp_x, "y", temp_y);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, i, j, x, y)                         \
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
               i, "j", j, "x", x, "y", y); /* assert(0); */ \
        \ 
}                                                  \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int i;
    int j;
    int x;
    int y;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&i, sizeof(i), "i_sym");
    klee_make_symbolic(&y, sizeof(y), "y_sym");
    klee_make_symbolic(&j, sizeof(j), "j_sym");
    klee_make_symbolic(&x, sizeof(x), "x_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        j = 0;
        i = 0;
        y = 1;
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(i, j, x, y);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(i, j, x, y));
        // Loop Condition
        if (i <= x) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((i <= x) && unroll--) {
                // assume((loopflag == 0));
                int temp_i = i;
                int temp_j = j;
                int temp_x = x;
                int temp_y = y;

                // loop body
                i = i + 1;
                j = j + y;
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_i, temp_j, temp_x, temp_y, i, j, x, y);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((i != j)) {
                postcheck((y != 1), i, j, x, y)
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
