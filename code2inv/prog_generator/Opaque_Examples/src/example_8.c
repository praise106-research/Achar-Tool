
/*
 * P-Hat Transformation : Multiply Example
 * for example_8.c file
 * Invariant : ((y >= 0) && (b >= 0) && (r == (y - b) * a))
 */

// Main Multiply Example
// Paper example
// Wrong : ((-b <= 1) && ( -a + x <= 0) && ( b <= -1) && ( -b - y <= -1) && ( a - x <= 0) && ( b - x <= -4))
// Wrong : ((-y <= -2) && ( a - x <= 0) && ( -b <= 1) && ( -a + x <= 0) && ( -r <= 0) && ( -b - r <= -2) && ( b - y <= 0) && ( -a - x <= -6))

#include <assert.h>
#include <example_8.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/file.h>

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(x, y, a, b, r, shift) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int x, long long int y, long long int a,
              long long int b, long long int r, long long int shift) {
    int f = preflag;
    setflag(INV(x, y, a, b, r, shift), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr,
                "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld\n",
                "x", x, "y", y, "a", a, "b", b, "r", r, "shift", shift);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_x, long long int temp_y,
               long long int temp_a, long long int temp_b, long long int temp_r,
               long long int temp_shift, long long int x, long long int y, long long int a,
               long long int b, long long int r, long long int shift) {
    int f = loopflag;
    setflag(INV(x, y, a, b, r, shift), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld, %s : %lld\n",
                "x", temp_x, "y", temp_y, "a", temp_a, "b", temp_b, "r", temp_r, "shift",
                temp_shift);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, "
                "%s : %lld\n",
                "x", x, "y", y, "a", a, "b", b, "r", r, "shift", shift);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, x, y, a, b, r, shift) \
    \ 
{                                                               \
        \ 
    int f = postflag;                                                \
        \ 
   setflag(cond, postflag);                                          \
        \ 
    if (f == 0 && postflag == 1) {                                   \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "x",                                                                \
                x, "y", y, "a", a, "b", b, "r", r, "shift", shift);  \
            assert(0);                                               \
        \ 
}                                                           \
    }

int main() {
    unsigned char supported;

// variable declarations
#ifndef READ_FROM_FLAG
    long long int x;
    long long int y;
    long long int a;
    long long int b;
    long long int r;
    long long int shift;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(x, y, a, b, r, shift)) {
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
#endif

        // HonggFuzz Inits
        assume((b >= 0));

        // These are not pre-conditions.
        // Used to capture inital values
        x = a;
        y = b;

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "x", x, "y", y, "a", a, "b", b, "r", r, "shift", shift);

        // Translate()
        if (choices > 10000) {
            assume((b >= 0));
            x = a;
            y = b;
            r = 0;
            shift = 0;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, x, y, a, b, r, shift);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, y, a, b, r, shift));
            // Loop Condition
            if ((b != 0)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((b != 0) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_x = x;
                    long long int temp_y = y;
                    long long int temp_a = a;
                    long long int temp_b = b;
                    long long int temp_r = r;
                    long long int temp_shift = shift;

                    // loop body
                    if (supported)
                        shift = __builtin_ctz(b);
                    else
                        shift = 0;

                    if (shift) {
                        r += a << shift;
                        b -= 1 << shift;
                    } else {
                        r += a;
                        b -= 1;
                    }

                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_y, temp_a, temp_b, temp_r, temp_shift, x, y,
                              a, b, r, shift);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");
                // post-condition
                postcheck(fptr, vars, ((r == x * y)), x, y, a, b, r, shift)
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
