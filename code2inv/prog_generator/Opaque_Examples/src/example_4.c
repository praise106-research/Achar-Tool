
/*
 * P-Hat Transformation
 * for example_4.c file
 */

#include <assert.h>
#include <example_4.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/file.h>

/**
 * @brief Fibonacci verify
 */

long long int fib(long long int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long int prev_1 = 0, prev_2 = 1, next = 0, i = 2;
    for (; i <= n; i++) {
        next = prev_1 + prev_2;
        prev_1 = prev_2;
        prev_2 = next;
    }
    return prev_2;
}

// =============================================================================

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(x, y, i, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int x, long long int y, long long int i,
              long long int n) {
    int f = preflag;
    setflag(INV(x, y, i, n), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "i", i,
                "n", n);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_x, long long int temp_y,
               long long int temp_i, long long int temp_n, long long int x, long long int y,
               long long int i, long long int n) {
    int f = loopflag;
    setflag(INV(x, y, i, n), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", temp_x, "y",
                temp_y, "i", temp_i, "n", temp_n);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "i",
                i, "n", n);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, x, y, i, n) \
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
 "x",                                                      \
                x, "y", y, "i", i, "n", n);                \
            assert(0);                                     \
        \ 
}                                                 \
    }

long long int add_sum(long long int a, long long b) { return (long long int)(a + b); }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG
    long long int x = 0;
    long long int y = 1;
    long long int i = 0;
    long long int n = 0;
#endif

    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(x, y, i, n)) {
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
        long long int choices = honggBuf[5];

#ifndef READ_FROM_FLAG
        long long int n = honggBuf[1];
#endif

        // HonggFuzz Specific
        // Limit on "n" to avoid overflow.
        assume((n > 0));
        assume((n < 104));

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "i", i,
                 "n", n);

        // Translate()
        if (choices > 10000) {
            x = 0;
            y = 1;
            i = 0;
            precount++;
            // fprintf(fptr, "Pre : %lld, %lld\n", fib(i), fib(i + 1));
            // precheck
            precheck(fptr, vars, x, y, i, n);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, y, i, n));

            // Loop Condition
            if (i < n) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((i < n) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_x = x;
                    long long int temp_y = y;
                    long long int temp_i = i;
                    long long int temp_n = n;

                    // loop body
                    long long int c = add_sum(x, y);
                    x = y;
                    y = c;
                    i = i + 1;

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_y, temp_i, temp_n, x, y, i, n);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");
                // post-condition
                postcheck(fptr, vars, ((0 <= i <= n) && (x == fib(n))), x, y, i, n)
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
