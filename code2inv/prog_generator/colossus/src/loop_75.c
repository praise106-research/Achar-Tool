
/*
 * P-Hat Transformation
 * for Colossus : 75.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_75.h>
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

#define INV(c, y, z) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int c, int y, int z) {
    int f = preflag;
    setflag(INV(c, y, z), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d\n", "c", c, "y", y, "z", z);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_c, int temp_y, int temp_z, int c, int y, int z) {
    int f = loopflag;
    setflag(INV(c, y, z), loopflag);
    if (f == 0 && loopflag == 1) {
        printf("LoopStart : %s : %d, %s : %d, %s : %d\n", "c", temp_c, "y", temp_y, "z", temp_z);
        printf("LoopEnd : %s : %d, %s : %d, %s : %d\n", "c", c, "y", y, "z", z);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, c, y, z)                    \
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
 "c",                                               \
               c, "y", y, "z", z); /* assert(0); */ \
        \ 
}                                          \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int c;
    int y;
    int z;
    int x1 = 0;
    int x2 = 0;
    int x3 = 0;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&c, sizeof(c), "c_sym");
    klee_make_symbolic(&y, sizeof(y), "y_sym");
    klee_make_symbolic(&z, sizeof(z), "z_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (c = 0);
        klee_assume((y >= 0));
        klee_assume((y >= 127));
        (z = (36 * y));
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(c, y, z);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(c, y, z));
        // Loop Condition
        if ((choices > 2500)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((choices > 2500) && unroll--) {
                // assume((loopflag == 0));
                int temp_c = c;
                int temp_y = y;
                int temp_z = z;

                {
                    // loop body
                    if ((c < 36)) {
                        (z = (z + 1));
                        (c = (c + 1));
                    }
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_c, temp_y, temp_z, c, y, z);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((c < 36)) {
                postcheck(((z < 4608)), c, y, z)
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
