
/*
 * P-Hat Transformation
 * for 74.c file
 */

#include <74.h>
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

#define INV(c, y, z, x1, x2, x3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int c, long long int y, long long int z,
              long long int x1, long long int x2, long long int x3) {
    int f = preflag;
    setflag(INV(c, y, z, x1, x2, x3), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "c", c, "y", y, "z", z, "x1", x1, "x2", x2, "x3", x3);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_c, long long int temp_y,
               long long int temp_z, long long int temp_x1, long long int temp_x2,
               long long int temp_x3, long long int c, long long int y, long long int z,
               long long int x1, long long int x2, long long int x3) {
    int f = loopflag;
    setflag(INV(c, y, z, x1, x2, x3), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "c", temp_c, "y", temp_y, "z", temp_z, "x1", temp_x1, "x2", temp_x2, "x3", temp_x3);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "c",
                c, "y", y, "z", z, "x1", x1, "x2", x2, "x3", x3);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, c, y, z, x1, x2, x3) \
    \ 
{                                                              \
        \ 
    int f = postflag;                                               \
        \ 
   setflag(cond, postflag);                                         \
        \ 
    if (f == 0 && postflag == 1) {                                  \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "c",                                                               \
                c, "y", y, "z", z, "x1", x1, "x2", x2, "x3", x3);   \
            assert(0);                                              \
        \ 
}                                                          \
    }

int main(int argc, char** argv) {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int c;
    long long int y;
    long long int z;
    long long int x1;
    long long int x2;
    long long int x3;
#endif

    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    FILE* inputs = fopen("inputs/inputs_74.txt", "a");
    setvbuf(inputs, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "c", c, "y", y, "z", z, "x1", x1, "x2", x2, "x3", x3);

    if (INV(c, y, z, x1, x2, x3)) {
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
        long long int c = honggBuf[0];
        long long int y = honggBuf[1];
        long long int z = honggBuf[2];
        long long int x1 = honggBuf[3];
        long long int x2 = honggBuf[4];
        long long int x3 = honggBuf[5];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "c", c, "y", y, "z", z, "x1", x1, "x2", x2, "x3", x3);

        fprintf(inputs, "%lld, %lld, %lld, %lld, %lld, %lld, %lld\n", c, y, z, x1, x2, x3, choices);

        // Translate()
        if (choices > 10000) {
            (c = 0);
            assume((y >= 0));
            assume((y >= 127));
            (z = (36 * y));
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, c, y, z, x1, x2, x3);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(c, y, z, x1, x2, x3));

            // Loop Condition
            if ((choices > 2500)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((choices > 2500) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_c = c;
                    long long int temp_y = y;
                    long long int temp_z = z;
                    long long int temp_x1 = x1;
                    long long int temp_x2 = x2;
                    long long int temp_x3 = x3;

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
                    loopcheck(fptr, vars, temp_c, temp_y, temp_z, temp_x1, temp_x2, temp_x3, c, y,
                              z, x1, x2, x3);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                if ((c < 36)) {
                    postcheck(fptr, vars, ((z >= 0)), c, y, z, x1, x2, x3)
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
