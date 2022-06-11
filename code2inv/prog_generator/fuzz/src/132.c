
/*
 * P-Hat Transformation
 * for 132.c file
 */

#include <132.h>
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

#define INV(i, j, c, t) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int i, long long int j, long long int c,
              long long int t) {
    int f = preflag;
    setflag(INV(i, j, c, t), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j, "c", c,
                "t", t);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_i, long long int temp_j,
               long long int temp_c, long long int temp_t, long long int i, long long int j,
               long long int c, long long int t) {
    int f = loopflag;
    setflag(INV(i, j, c, t), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", temp_i, "j",
                temp_j, "c", temp_c, "t", temp_t);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j, "c",
                c, "t", t);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, i, j, c, t) \
    \ 
{                                                     \
        \ 
    int f = postflag;                                      \
        \ 
   setflag(cond, postflag);                                \
        \ 
    if (f == 0 && postflag == 1) {                         \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                                      \
                i, "j", j, "c", c, "t", t);                \
            assert(0);                                     \
        \ 
}                                                 \
    }

int main(int argc, char** argv) {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int i;
    long long int j;
    long long int c;
    long long int t;
#endif

    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    FILE* inputs = fopen("inputs/inputs_132.txt", "a");
    setvbuf(inputs, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j, "c", c,
            "t", t);

    if (INV(i, j, c, t)) {
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
        long long int choices = honggBuf[17];

#ifndef READ_FROM_FLAG
        long long int i = honggBuf[82];
        long long int j = honggBuf[34];
        long long int c = honggBuf[56];
        long long int t = honggBuf[71];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j, "c", c,
                 "t", t);

        fprintf(inputs, "%lld, %lld, %lld, %lld, %lld\n", i, j, c, t, choices);

        // Translate()
        if (choices > 10000) {
            i = 0;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, i, j, c, t);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, j, c, t));

            // Loop Condition
            if ((choices > 2500)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((choices > 2500) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_i = i;
                    long long int temp_j = j;
                    long long int temp_c = c;
                    long long int temp_tt = t;

                    // loop body
                    if (c > 48) {
                        if (c < 57) {
                            j = i + i;
                            t = c - 48;
                            i = j + t;
                        }
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_i, temp_j, temp_c, temp_tt, i, j, c, t);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                postcheck(fptr, vars, (i >= 0), i, j, c, t)
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
