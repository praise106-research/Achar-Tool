
/*
 * P-Hat Transformation
 * for Colossus : 127.c file
 */

#include <assert.h>
#include <klee/klee.h>
#include <loop_127.h>
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

#define INV(i, j, x, y, z1, z2, z3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(int i, int j, int x, int y, int z1, int z2, int z3) {
    int f = preflag;
    setflag(INV(i, j, x, y, z1, z2, z3), preflag);
    if (f == 0 && preflag == 1) {
        printf("Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j",
               j, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
        /* assert(0); */
    }
}

// COMMENT : Loopcheck function
void loopcheck(int temp_i, int temp_j, int temp_x, int temp_y, int temp_z1, int temp_z2,
               int temp_z3, int i, int j, int x, int y, int z1, int z2, int z3) {
    int f = loopflag;
    setflag(INV(i, j, x, y, z1, z2, z3), loopflag);
    if (f == 0 && loopflag == 1) {
        printf(
            "LoopStart : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, "
            "%s : %d\n",
            "i", temp_i, "j", temp_j, "x", temp_x, "y", temp_y, "z1", temp_z1, "z2", temp_z2, "z3",
            temp_z3);
        printf(
            "LoopEnd : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s "
            ": %d\n",
            "i", i, "j", j, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
        /* assert(0); */
    }
}

// COMMENT : Postcheck Macro
#define postcheck(cond, i, j, x, y, z1, z2, z3)                                           \
    \ 
{                                                                                    \
        \ 
    int f = postflag;                                                                     \
        \ 
   setflag(cond, postflag);                                                               \
        \ 
    if (f == 0 && postflag == 1) {                                                        \
            \ 
        printf("Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", \ 
 "i",                                                                                     \
               i, "j", j, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3); /* assert(0); */ \
        \ 
}                                                                                \
    }

int main(int argc, char* argv[]) {
    // variable declarations

    int i;
    int j;
    int x;
    int y;
    int z1 = 0;
    int z2 = 0;
    int z3 = 0;
    int choices;
    // klee make symbolic calls.
    klee_make_symbolic(&x, sizeof(x), "x_sym");
    klee_make_symbolic(&y, sizeof(y), "y_sym");
    klee_make_symbolic(&j, sizeof(j), "j_sym");
    klee_make_symbolic(&i, sizeof(i), "i_sym");
    klee_make_symbolic(&choices, sizeof(choices), "choices_sym");

    // Translate() Colossus
    if (choices > 10000) {
        (i = x);
        (j = y);
        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(i, j, x, y, z1, z2, z3);
    } else {
        // loop-check program
        // assume((loopflag + postflag < 2));
        klee_assume(INV(i, j, x, y, z1, z2, z3));
        // Loop Condition
        if ((x != 0)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x != 0) && unroll--) {
                // assume((loopflag == 0));
                int temp_i = i;
                int temp_j = j;
                int temp_x = x;
                int temp_y = y;
                int temp_z1 = z1;
                int temp_z2 = z2;
                int temp_z3 = z3;

                {
                    // loop body
                    (x = (x - 1));
                    (y = (y - 1));
                }
                // fprintf(fptr, "Loop\n");
                // fprintf(fptr, "Flag : %d\n", reach_flag);
                // assume(reach_flag);

                loopcount++;
                loopcheck(temp_i, temp_j, temp_x, temp_y, temp_z1, temp_z2, temp_z3, i, j, x, y, z1,
                          z2, z3);
            }
        } else {
            // post-check program
            // assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((y != 0)) {
                postcheck(((i != j)), i, j, x, y, z1, z2, z3)
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
