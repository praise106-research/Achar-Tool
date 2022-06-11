
/*
 * P-Hat Transformation
 * for example_5.c file
 */

#include <assert.h>
#include <example_5.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

/*
 * Function to compute power modulo
 * https://cp-algorithms.com/algebra/binary-exp.html
 */

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(x, y, a, b, res, m) PHI

long long binpow(long long a, long long b) {
    long long res = 1;

    while (b > 0) {
        if (b & 1) res = (res * 1ll * a);
        a = (a * 1ll * a);
        b >>= 1;
    }

    return res;
}

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int x, long long int y, long long int a,
              long long int b, long long int res, long long int m) {
    int f = preflag;
    setflag(INV(x, y, a, b, res, m), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr,
                "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld\n",
                "x", x, "y", y, "a", a, "b", b, "res", res, "m", m);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_x, long long int temp_y,
               long long int temp_a, long long int temp_b, long long int temp_res,
               long long int temp_m, long long int x, long long int y, long long int a,
               long long int b, long long int res, long long int m) {
    int f = loopflag;
    setflag(INV(x, y, a, b, res, m), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld, %s : %lld\n",
                "x", temp_x, "y", temp_y, "a", temp_a, "b", temp_b, "res", temp_res, "m", temp_m);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, "
                "%s : %lld\n",
                "x", x, "y", y, "a", a, "b", b, "res", res, "m", m);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, x, y, a, b, res, m) \
    \ 
{                                                             \
        \ 
    int f = postflag;                                              \
        \ 
   setflag(cond, postflag);                                        \
        \ 
    if (f == 0 && postflag == 1) {                                 \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "x",                                                              \
                x, "y", y, "a", a, "b", b, "res", res, "m", m);    \
            assert(0);                                             \
        \ 
}                                                         \
    }

// https://godbolt.org/z/Y1rqWchvs

int main() {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int x;
    long long int y;
    long long int a;
    long long int b;
    long long int res = 1;
    long long int m;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(x, y, a, b, res, m)) {
        fprintf(fptr, "True\n");
    } else {
        fprintf(fptr, "False\n");
    }
    assert(0);
#endif

    for (;;) {
        int reach_flag = 0;
        // Initialize HonggFuzz
        size_t len;
        const int16_t* honggBuf;
        HF_ITER(&honggBuf, &len);
        counter++;

        // Populate with Inputs
        long long int choices = honggBuf[0];

#ifndef READ_FROM_FLAG
        long long int a = honggBuf[1];
        long long int b = honggBuf[2];
        long long int m = honggBuf[3];
#endif

        // HonggFuzz Specific
        assume((m > 0));
        assume((b > 0));
        assume((binpow(a, b) < 99999999999999));
        assume((binpow(a, b) > 0));

        // These are not pre-conditions.
        // Used to capture inital values
        x = a;
        y = b;

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "x", x, "y", y, "a", a, "b", b, "res", res, "m", m);

        // Translate()
        if (choices > 10000) {
            assume((m > 0));
            assume((b > 0));
            x = a;
            y = b;
            a = a % m;
            res = 1;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, x, y, a, b, res, m);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, y, a, b, res, m));

            // Loop Condition
            if (b > 0) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((b > 0) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_x = x;
                    long long int temp_y = y;
                    long long int temp_a = a;
                    long long int temp_b = b;
                    long long int temp_res = res;
                    long long int temp_m = m;

                    // loop body
                    if (b & 1) res = (res * 1ll * a) % m;
                    a = (a * 1ll * a) % m;
                    b >>= 1;

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_y, temp_a, temp_b, temp_res, temp_m, x, y, a,
                              b, res, m);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");
                // post-condition
                postcheck(fptr, vars, (res == binpow(x, y) % m), x, y, a, b, res, m)
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
