
/*
 * P-Hat Transformation
 * for example_7.c file
 */

#include <assert.h>
#include <example_7.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

// Integer Square root
// https://en.wikipedia.org/wiki/Integer_square_root
// https://godbolt.org/z/naxz7K4sr

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(res, bit, num, num_orig) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int res, long long int bit,
              long long int num, long long int num_orig) {
    int f = preflag;
    setflag(INV(res, bit, num, num_orig), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "res", res, "bit", bit,
                "num", num, "num_orig", num_orig);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_res, long long int temp_bit,
               long long int temp_num, long long int temp_num_orig, long long int res,
               long long int bit, long long int num, long long int num_orig) {
    int f = loopflag;
    setflag(INV(res, bit, num, num_orig), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "res", temp_res,
                "bit", temp_bit, "num", temp_num, "num_orig", temp_num_orig);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "res", res, "bit",
                bit, "num", num, "num_orig", num_orig);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, res, bit, num, num_orig) \
    \ 
{                                                                  \
        \ 
    int f = postflag;                                                   \
        \ 
   setflag(cond, postflag);                                             \
        \ 
    if (f == 0 && postflag == 1) {                                      \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "res",                                                                 \
                res, "bit", bit, "num", num, "num_orig", num_orig);     \
            assert(0);                                                  \
        \ 
}                                                              \
    }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG
    long long int res = 0;
    long long int bit = 1 << 30;
    long long int num;
    long long int num_orig;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(res, bit, num, num_orig)) {
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
        long long int num = honggBuf[4];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "res", res, "bit", bit,
                 "num", num, "num_orig", num_orig);

        assume((num >= 0));
        // These are not pre-conditions.
        // Used to capture inital values
        num_orig = num;

        // Translate()
        if (choices > 10000) {
            res = 0;
            bit = 1 << 30;
            while (bit > num) {
                bit >>= 2;
            }
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, res, bit, num, num_orig);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(res, bit, num, num_orig));

            // Loop Condition
            if ((bit != 0)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((bit != 0) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_res = res;
                    long long int temp_bit = bit;
                    long long int temp_num = num;
                    long long int temp_num_orig = num_orig;

                    // loop body
                    if (num >= res + bit) {
                        num -= res + bit;
                        res = (res >> 1) + bit;
                    } else
                        res >>= 1;
                    bit >>= 2;

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);
                    // (((bit == 0) && (res * res <= num_orig)) || ((bit != 0)))

                    loopcount++;
                    loopcheck(fptr, vars, temp_res, temp_bit, temp_num, temp_num_orig, res, bit,
                              num, num_orig);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");
                // post-condition
                postcheck(fptr, vars, ((res * res <= num_orig)), res, bit, num, num_orig)
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
