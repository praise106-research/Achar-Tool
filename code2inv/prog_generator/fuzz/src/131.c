
/*
 * P-Hat Transformation
 * for 131.c file
 */

#include <131.h>
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

#define INV(d1, d2, d3, x1, x2, x3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int d1, long long int d2,
              long long int d3, long long int x1, long long int x2, long long int x3) {
    int f = preflag;
    setflag(INV(d1, d2, d3, x1, x2, x3), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_d1, long long int temp_d2,
               long long int temp_d3, long long int temp_x1, long long int temp_x2,
               long long int temp_x3, long long int d1, long long int d2, long long int d3,
               long long int x1, long long int x2, long long int x3) {
    int f = loopflag;
    setflag(INV(d1, d2, d3, x1, x2, x3), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "d1", temp_d1, "d2", temp_d2, "d3", temp_d3, "x1", temp_x1, "x2", temp_x2, "x3",
                temp_x3);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, d1, d2, d3, x1, x2, x3) \
    \ 
{                                                                 \
        \ 
    int f = postflag;                                                  \
        \ 
   setflag(cond, postflag);                                            \
        \ 
    if (f == 0 && postflag == 1) {                                     \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "d1",                                                                 \
                d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3); \
            assert(0);                                                 \
        \ 
}                                                             \
    }

int main(int argc, char** argv) {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int d1;
    long long int d2;
    long long int d3;
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

    FILE* inputs = fopen("inputs/inputs_131.txt", "a");
    setvbuf(inputs, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);

    if (INV(d1, d2, d3, x1, x2, x3)) {
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
        long long int d1 = honggBuf[92];
        long long int d2 = honggBuf[34];
        long long int d3 = honggBuf[88];
        long long int x1 = honggBuf[64];
        long long int x2 = honggBuf[92];
        long long int x3 = honggBuf[39];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);

        fprintf(inputs, "%lld, %lld, %lld, %lld, %lld, %lld, %lld\n", d1, d2, d3, x1, x2, x3,
                choices);

        // Translate()
        if (choices > 10000) {
            d1 = 1;
            d2 = 1;
            d3 = 1;
            x1 = 1;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, d1, d2, d3, x1, x2, x3);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(d1, d2, d3, x1, x2, x3));

            // Loop Condition
            if (x1 > 0) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((x1 > 0) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_d1 = d1;
                    long long int temp_d2 = d2;
                    long long int temp_d3 = d3;
                    long long int temp_x1 = x1;
                    long long int temp_x2 = x2;
                    long long int temp_x3 = x3;

                    // loop body
                    if (x2 > 0) {
                        if (x3 > 0) {
                            x1 = x1 - d1;
                            x2 = x2 - d2;
                            x3 = x3 - d3;
                        }
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_d1, temp_d2, temp_d3, temp_x1, temp_x2, temp_x3, d1,
                              d2, d3, x1, x2, x3);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                postcheck(fptr, vars, (x3 >= 0), d1, d2, d3, x1, x2, x3)
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
