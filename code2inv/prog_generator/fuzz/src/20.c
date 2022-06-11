
/*
 * P-Hat Transformation
 * for 20.c file
 */

#include <20.h>
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

#define INV(z1, z2, z3, x, m, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int z1, long long int z2,
              long long int z3, long long int x, long long int m, long long int n) {
    int f = preflag;
    setflag(INV(z1, z2, z3, x, m, n), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "z1", z1, "z2", z2, "z3", z3, "x", x, "m", m, "n", n);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_z1, long long int temp_z2,
               long long int temp_z3, long long int temp_x, long long int temp_m,
               long long int temp_n, long long int z1, long long int z2, long long int z3,
               long long int x, long long int m, long long int n) {
    int f = loopflag;
    setflag(INV(z1, z2, z3, x, m, n), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "z1", temp_z1, "z2", temp_z2, "z3", temp_z3, "x", temp_x, "m", temp_m, "n", temp_n);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "z1", z1, "z2", z2, "z3", z3, "x", x, "m", m, "n", n);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, z1, z2, z3, x, m, n) \
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
 "z1",                                                              \
                z1, "z2", z2, "z3", z3, "x", x, "m", m, "n", n);    \
            assert(0);                                              \
        \ 
}                                                          \
    }

int main(int argc, char** argv) {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int z1;
    long long int z2;
    long long int z3;
    long long int x;
    long long int m;
    long long int n;
#endif

    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    FILE* inputs = fopen("inputs/inputs_20.txt", "a");
    setvbuf(inputs, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "z1", z1, "z2", z2, "z3", z3, "x", x, "m", m, "n", n);

    if (INV(z1, z2, z3, x, m, n)) {
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
        long long int z1 = honggBuf[0];
        long long int z2 = honggBuf[1];
        long long int z3 = honggBuf[2];
        long long int x = honggBuf[3];
        long long int m = honggBuf[4];
        long long int n = honggBuf[5];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "z1", z1, "z2", z2, "z3", z3, "x", x, "m", m, "n", n);

        fprintf(inputs, "%lld, %lld, %lld, %lld, %lld, %lld, %lld\n", z1, z2, z3, x, m, n, choices);

        // Translate()
        if (choices > 10000) {
            (x = 0);
            (m = 0);
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, z1, z2, z3, x, m, n);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(z1, z2, z3, x, m, n));

            // Loop Condition
            if ((x < n)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((x < n) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_z1 = z1;
                    long long int temp_z2 = z2;
                    long long int temp_z3 = z3;
                    long long int temp_x = x;
                    long long int temp_m = m;
                    long long int temp_n = n;

                    {
                        // loop body
                        // non-deterministic
                        if (choices > 3500) {
                            m = x;
                        }
                        x = x + 1;
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_z1, temp_z2, temp_z3, temp_x, temp_m, temp_n, z1, z2,
                              z3, x, m, n);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                if (n > 0) {
                    postcheck(fptr, vars, (m >= 0), z1, z2, z3, x, m, n)
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
