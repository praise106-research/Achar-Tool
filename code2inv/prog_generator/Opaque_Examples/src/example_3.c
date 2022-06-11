
#include <assert.h>
#include <example_3.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

// https://godbolt.org/z/j9hh1hjEE
void swap(int* term1, int* term2) {
    int temp = *term1;
    *term1 = *term2;
    *term2 = temp;
}

// https://cp-algorithms.com/algebra/euclid-algorithm.html
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(&a, &b);
    }
    return a;
}

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(result, a, b, x, y) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int result, long long int a,
              long long int b, long long int x, long long int y) {
    int f = preflag;
    setflag(INV(result, a, b, x, y), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "result",
                result, "a", a, "b", b, "x", x, "y", y);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_result, long long int temp_a,
               long long int temp_b, long long int temp_x, long long int temp_y,
               long long int result, long long int a, long long int b, long long int x,
               long long int y) {
    int f = loopflag;
    setflag(INV(result, a, b, x, y), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "result", temp_result, "a", temp_a, "b", temp_b, "x", temp_x, "y", temp_y);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "result",
                result, "a", a, "b", b, "x", x, "y", y);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, result, a, b, x, y) \
    \ 
{                                                             \
        \ 
    int f = postflag;                                              \
        \ 
   setflag(cond, postflag);                                        \
        \ 
    if (f == 0 && postflag == 1) {                                 \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "result",                                                         \
                result, "a", a, "b", b, "x", x, "y", y);           \
            assert(0);                                             \
        \ 
}                                                         \
    }

long long int retmod(long long int a, long long int b) { return (long long int)(a % b); }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG
    long long unsigned int a;
    long long unsigned int b;
    long long unsigned int x;
    long long unsigned int y;
    long long unsigned int result;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(result, a, b, x, y)) {
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
        const uint16_t* buf;
        HF_ITER(&buf, &len);
        counter++;

        // Populate with Inputs
        long long int choices = buf[0];

#ifndef READ_FROM_FLAG
        long long unsigned int a = buf[1];
        long long unsigned int b = buf[2];
#endif

        assume((b != 0));

        fprintf(fptr, "%d, %d, %d\n", gcd(x, y), a, b);

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "result",
                 result, "a", a, "b", b, "x", x, "y", y);

        // Translate()
        if (choices > 10000) {
            assume((b != 0));
            x = a;
            y = b;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, result, a, b, x, y);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(result, a, b, x, y));

            // Loop Condition
            if ((a % b != 0)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((a % b != 0) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_result = result;
                    long long int temp_a = a;
                    long long int temp_b = b;
                    long long int temp_x = x;
                    long long int temp_y = y;

                    // loop body
                    result = retmod(a, b);
                    a = b;
                    b = result;

                    loopcount++;
                    loopcheck(fptr, vars, temp_result, temp_a, temp_b, temp_x, temp_y, result, a, b,
                              x, y);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // fprintf(fptr, "Post\n");
                // post-condition
                postcount++;
                postcheck(fptr, vars, (b == gcd(x, y)), result, a, b, x, y)
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
