
/*
 * P-Hat Transformation
 * for example_14.c file
 */

#include <assert.h>
#include <example_14.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

// Multiply() adapted from the example_8.c file.
long long int multiply(long long int a, long long int b) {
    long long int r = 0ll;
    while (b != 0) {
        long long int shift = __builtin_ctz(b);
        if (shift) {
            r += a << shift;
            b -= 1 << shift;
        } else {
            r += a;
            b -= 1;
        }
    }

    return r;
}

// http://www.cs.ecu.edu/karl/3300/spr14/Notes/Algorithm/invariant.html
long long int factorial(long long int n) { return (n == 1 || n == 0) ? 1ll : factorial(n - 1) * n; }

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(res, k, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int res, long long int k,
              long long int n) {
    int f = preflag;
    setflag(INV(res, k, n), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "res", res, "k", k, "n", n);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_res, long long int temp_k,
               long long int temp_n, long long int res, long long int k, long long int n) {
    int f = loopflag;
    setflag(INV(res, k, n), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "res", temp_res, "k", temp_k,
                "n", temp_n);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "res", res, "k", k, "n", n);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, res, k, n) \
    \ 
{                                                    \
        \ 
    int f = postflag;                                     \
        \ 
   setflag(cond, postflag);                               \
        \ 
    if (f == 0 && postflag == 1) {                        \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "res",                                                   \
                res, "k", k, "n", n);                     \
            assert(0);                                    \
        \ 
}                                                \
    }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG
    long long int res = 1;
    long long int k = 1;
    long long int n;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(res, k, n)) {
        fprintf(fptr, "True\n");
    } else {
        fprintf(fptr, "False\n");
    }
    assert(0);
#endif

    for (;;) {
        // Initialize HonggFuzz
        size_t len;
        const int16_t* honggBuf;
        HF_ITER(&honggBuf, &len);
        counter++;

        // Populate with Inputs
        long long int choices = honggBuf[0];

#ifndef READ_FROM_FLAG
        long long int n = honggBuf[1];
        // long long int k = honggBuf[2];
#endif

        // HonggFuzz Specific
        // long long int range less
        assume((n > 0));
        assume((n < 25));

        // fprintf(fptr, "Seg : Pre\n");

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld\n", "res", res, "k", k, "n", n);
        // Translate()
        if (choices > 10000) {
            k = 1;
            res = 1;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, res, k, n);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(res, k, n));

            // Loop Condition
            if ((k != n)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((k != n) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_res = res;
                    long long int temp_k = k;
                    long long int temp_n = n;

                    // loop body
                    k = k + 1;
                    res = multiply(res, k);

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_res, temp_k, temp_n, res, k, n);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");
                // post-condition
                postcheck(fptr, vars, (res == factorial(n)), res, k, n)
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
