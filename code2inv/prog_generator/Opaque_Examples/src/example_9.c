
/*
 * P-Hat Transformation
 * for example_9.c file
 */

#include <assert.h>
#include <example_9.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/file.h>

// https://www.oreilly.com/library/view/hackers-delight/0201914654/0201914654_ch11lev1sec2.html
// Original code:
int icbrt(unsigned x) {
    int s;
    unsigned y, b;
    s = 30;
    y = 0;
    while (s >= 0) {  // Do 11 times.
        y = 2 * y;
        b = (3 * y * (y + 1) + 1) << s;
        s = s - 3;
        if (x >= b) {
            x = x - b;
            y = y + 1;
        }
    }
    return y;
}

// Positive Integer Cube Root Algorithm
// https://godbolt.org/z/Yrd78eKTr

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(s, x, orig_x, y) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int s, long long int x,
              long long int orig_x, long long int y) {
    int f = preflag;
    setflag(INV(s, x, orig_x, y), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "s", s, "x", x,
                "orig_x", orig_x, "y", y);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_s, long long int temp_x,
               long long int temp_orig_x, long long int temp_y, long long int s, long long int x,
               long long int orig_x, long long int y) {
    int f = loopflag;
    setflag(INV(s, x, orig_x, y), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "s", temp_s, "x",
                temp_x, "orig_x", temp_orig_x, "y", temp_y);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "s", s, "x", x,
                "orig_x", orig_x, "y", y);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, s, x, orig_x, y) \
    \ 
{                                                          \
        \ 
    int f = postflag;                                           \
        \ 
   setflag(cond, postflag);                                     \
        \ 
    if (f == 0 && postflag == 1) {                              \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "s",                                                           \
                s, "x", x, "orig_x", orig_x, "y", y);           \
            assert(0);                                          \
        \ 
}                                                      \
    }

void getVal(long long int* x, long long unsigned int* y, long long unsigned* b) {
    if (*x >= *b) {
        *x = (*(x) - *(b));
        *y = (*(y) + 1);
    }
}

int main() {
    // variable declarations
    long long unsigned b;
#ifndef READ_FROM_FLAG
    long long int s;
    long long unsigned int x;
    long long unsigned int orig_x;
    long long unsigned int y;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(s, x, orig_x, y)) {
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
        const uint16_t* honggBuf;
        HF_ITER(&honggBuf, &len);
        counter++;

        // Populate with Inputs
        long long int choices = honggBuf[0];

#ifndef READ_FROM_FLAG
        long long int x = honggBuf[3];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "s", s, "x", x,
                 "orig_x", orig_x, "y", y);

        // HonggFuzz Init
        // No Negative number SQRT
        assume((x >= 0));

        // These are not pre-conditions.
        // Used to capture inital values
        orig_x = x;

        // Translate()
        if (choices > 10000) {
            assume((x >= 0));
            y = 0;
            s = 30;
            b = 0;
            orig_x = x;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, s, x, orig_x, y);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(s, x, orig_x, y));

            // Loop Condition
            if (s >= 0) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((s >= 0) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_s = s;
                    long long int temp_x = x;
                    long long int temp_orig_x = orig_x;
                    long long int temp_y = y;

                    // loop body
                    y = 2 * y;
                    b = (3 * y * (y + 1) + 1) << s;
                    s = s - 3;
                    getVal(&x, &y, &b);

                    // fprintf(fptr, "Loop\n");s
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_s, temp_x, temp_orig_x, temp_y, s, x, orig_x, y);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                postcheck(fptr, vars, (orig_x >= (y * y * y)), s, x, orig_x, y)
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
