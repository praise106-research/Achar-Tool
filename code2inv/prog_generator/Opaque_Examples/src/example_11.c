
/*
 * P-Hat Transformation
 * for example_11.c file
 */

#include <assert.h>
#include <example_11.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

// https://godbolt.org/z/MYM4fv4GP
long long cube(long long a) {
    long long res = 1;
    int b = 3;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(i, n, a, b, res) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int i, long long int n, long long int a,
              long long int b, long long int res) {
    int f = preflag;
    setflag(INV(i, n, a, b, res), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n",
                n, "a", a, "b", b, "res", res);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_i, long long int temp_n,
               long long int temp_a, long long int temp_b, long long int temp_res, long long int i,
               long long int n, long long int a, long long int b, long long int res) {
    int f = loopflag;
    setflag(INV(i, n, a, b, res), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i",
                temp_i, "n", temp_n, "a", temp_a, "b", temp_b, "res", temp_res);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i,
                "n", n, "a", a, "b", b, "res", res);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, i, n, a, b, res) \
    \ 
{                                                          \
        \ 
    int f = postflag;                                           \
        \ 
   setflag(cond, postflag);                                     \
        \ 
    if (f == 0 && postflag == 1) {                              \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                                           \
                i, "n", n, "a", a, "b", b, "res", res);         \
            assert(0);                                          \
        \ 
}                                                      \
    }

// Heavy Lifting Non Linear + Function calls
// https://godbolt.org/z/q99bnYW8K
int main() {
// variable declarations
#ifndef READ_FROM_FLAG
    long long int i;
    long long int n;
    long long int a;
    long long int b;
    long long int res;
#endif

    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(i, n, a, b, res)) {
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
        long long int choices = honggBuf[0];

#ifndef READ_FROM_FLAG
        long long int n = honggBuf[1];
        long long int a = honggBuf[3];
        long long int b = honggBuf[4];
        long long int i = honggBuf[10];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n",
                 n, "a", a, "b", b, "res", res);

        // HonggFuzz Specific
        assume((n > 0));
        // assume((i < n));

        // Translate()
        if (choices > 10000) {
            assume((n > 0));
            a = 0;
            b = 0;
            i = 0;
            res = 0;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, i, n, a, b, res);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, n, a, b, res));

            // Loop Condition
            if ((i < n)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((i < n) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_i = i;
                    long long int temp_n = n;
                    long long int temp_a = a;
                    long long int temp_b = b;
                    long long int temp_res = res;

                    // loop body
                    i = i + 1;
                    res = cube(a) + cube(b) + cube(i) + 3 * (a * a) * b + 3 * a * (b * b) +
                          3 * a * a * i + 3 * a * i * i + 3 * b * b * i + 3 * b * i * i +
                          6 * a * b * i;

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_i, temp_n, temp_a, temp_b, temp_res, i, n, a, b,
                              res);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                postcheck(fptr, vars, ((res == (a + b + n) * (a + b + n) * (a + b + n))), i, n, a,
                          b, res)
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
