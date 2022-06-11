
/*
 * P-Hat Transformation
 * for example_15.c file
 */

#include <assert.h>
#include <example_15.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

/*
  Sum of Cubes Example (n(n+1)/2)^2
  https://godbolt.org/z/dTda3x1zM
  https://godbolt.org/z/6xhasj7qr
// ((sum == (i * i * (i + 1) * (i + 1)) / 4) && (i <= n))
*/

long long int foo(long long int sum, long long int i) {
    long long int product = 0;
    __asm__ __volatile__("imull %[d]\n" : [rtn] "=A"(product) : [a] "a"(i), [d] "rm"(i));
    __asm__ __volatile__("imull %[d]\n" : [rtn] "=A"(product) : [a] "a"(product), [d] "rm"(i));
    return sum + product;
}

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(i, n, sum, lin_sum) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int i, long long int n,
              long long int sum, long long int lin_sum) {
    int f = preflag;
    setflag(INV(i, n, sum, lin_sum), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n", n, "sum",
                sum, "lin_sum", lin_sum);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_i, long long int temp_n,
               long long int temp_sum, long long int temp_lin_sum, long long int i, long long int n,
               long long int sum, long long int lin_sum) {
    int f = loopflag;
    setflag(INV(i, n, sum, lin_sum), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", temp_i, "n",
                temp_n, "sum", temp_sum, "lin_sum", temp_lin_sum);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n", n,
                "sum", sum, "lin_sum", lin_sum);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, i, n, sum, lin_sum) \
    \ 
{                                                             \
        \ 
    int f = postflag;                                              \
        \ 
   setflag(cond, postflag);                                        \
        \ 
    if (f == 0 && postflag == 1) {                                 \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                                              \
                i, "n", n, "sum", sum, "lin_sum", lin_sum);        \
            assert(0);                                             \
        \ 
}                                                         \
    }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG
    long long int i = 0;
    long long int n = 0;
    long long int sum = 0;
    long long int lin_sum = 0;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(i, n, sum, lin_sum)) {
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
        long long int n = honggBuf[2];
#endif

        // HonggFuzz Specific
        // Limits to avoid overflow conditions
        assume((n >= 0));
        assume((n <= 2000));

        // assume((i >= 0));
        // assume((i <= n));

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n", n, "sum",
                 sum, "lin_sum", lin_sum);

        // Translate()
        if (choices > 10000) {
            assume((n >= 0));
            i = 0;
            sum = 0;
            lin_sum = 0;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, i, n, sum, lin_sum);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, n, sum, lin_sum));

            // Loop Condition
            if ((i < n)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((i < n) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_i = i;
                    long long int temp_n = n;
                    long long int temp_sum = sum;
                    long long int temp_lin_sum = lin_sum;

                    // loop body
                    i = i + 1;
                    lin_sum = lin_sum + i;  // Finally : n * (n + 1)/2
                    sum = foo(sum, i);

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_i, temp_n, temp_sum, temp_lin_sum, i, n, sum,
                              lin_sum);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                postcheck(fptr, vars, ((sum == (lin_sum * lin_sum))), i, n, sum, lin_sum)
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
