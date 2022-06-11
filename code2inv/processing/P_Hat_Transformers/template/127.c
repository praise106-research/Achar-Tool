
/*
 * P-Hat Transformation
 * for 127.c file
 */

#include <127.h>
#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!(cond)) flag = 1;

#define assume(cond) \
    if (!(cond)) continue;

#define INV(i, j, x, y, z1, z2, z3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int i, long long int j, long long int x,
              long long int y, long long int z1, long long int z2, long long int z3) {
    int f = preflag;
    setflag(INV(i, j, x, y, z1, z2, z3), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(
            fptr,
            "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "i", i, "j", j, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_i, long long int temp_j,
               long long int temp_x, long long int temp_y, long long int temp_z1,
               long long int temp_z2, long long int temp_z3, long long int i, long long int j,
               long long int x, long long int y, long long int z1, long long int z2,
               long long int z3) {
    int f = loopflag;
    setflag(INV(i, j, x, y, z1, z2, z3), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s "
                ": %lld\n",
                "i", temp_i, "j", temp_j, "x", temp_x, "y", temp_y, "z1", temp_z1, "z2", temp_z2,
                "z3", temp_z3);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld\n",
                "i", i, "j", j, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, i, j, x, y, z1, z2, z3) \
    \ 
{                                                                 \
        \ 
    int f = postflag;                                                  \
        \ 
   setflag(cond, postflag);                                            \
        \ 
    if (f == 0 && postflag == 1) {                                     \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i", i, "j", j, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);                                                         \
            assert(0);                                                 \
        \ 
}                                                             \
    }

int main(int argc, char** argv) {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int i;
    long long int j;
    long long int x;
    long long int y;
    long long int z1;
    long long int z2;
    long long int z3;
#endif

    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    FILE* inputs = fopen("inputs/inputs_127.txt", "a");
    setvbuf(inputs, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(
        fptr,
        "Checker : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
        "i", i, "j", j, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);

    if (INV(i, j, x, y, z1, z2, z3)) {
        fprintf(fptr, "True\n");
    } else {
        fprintf(fptr, "False\n");
    }
    assert(0);
#endif

    int reach_flag = 0;
    for (;;) {
        // Initialize HonggFuzz
        size_t len;
        const int16_t* honggBuf;
        HF_ITER(&honggBuf, &len);
        counter++;

        // Populate with Inputs
        long long int choices = honggBuf[10];

#ifndef READ_FROM_FLAG
        long long int i = honggBuf[0];
        long long int j = honggBuf[1];
        long long int x = honggBuf[2];
        long long int y = honggBuf[3];
        long long int z1 = honggBuf[4];
        long long int z2 = honggBuf[5];
        long long int z3 = honggBuf[6];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128,
                 "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "i", i, "j", j, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);

        fprintf(inputs, "%lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld\n", i, j, x, y, z1, z2, z3,
                choices);

        // Translate()
        if (choices > 10000) {
            (i = x);
            (j = y);
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, i, j, x, y, z1, z2, z3);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, j, x, y, z1, z2, z3));

            // Loop Condition
            if ((x != 0)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((x != 0) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_i = i;
                    long long int temp_j = j;
                    long long int temp_x = x;
                    long long int temp_y = y;
                    long long int temp_z1 = z1;
                    long long int temp_z2 = z2;
                    long long int temp_z3 = z3;

                    {
                        // loop body
                        (x = (x - 1));
                        (y = (y - 1));
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_i, temp_j, temp_x, temp_y, temp_z1, temp_z2, temp_z3,
                              i, j, x, y, z1, z2, z3);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                if ((y != 0)) {
                    postcheck(fptr, vars, ((i != j)), i, j, x, y, z1, z2, z3)
                }
            }
        }

        // Print the counters if no flags are hit
        if (preflag + loopflag + postflag == 0 && counter == 100) {
            fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount",
                    loopcount, "postcount", postcount);
            counter = 0;
        }

        // Close FILE with assert(0);
        if (preflag + loopflag + postflag >= 3) {
            fclose(fptr);
            assert(0);
        }
    }

    // Regular Close FILE
    fclose(fptr);
    return 0;
}
