
/*
 * P-Hat Transformation
 * for example_12.c file
 */

#include <assert.h>
#include <example_12.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/file.h>

// Integer Division
// https://godbolt.org/z/rx5GGejGz
void setPowerValue(int* y_power, int* x, int* power) {
    while (*y_power > *x) {
        *(y_power) >>= 1;
        *power -= 1;
    }
}

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(x, y, x_0, result, power, y_power) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int x, long long int y,
              long long int x_0, long long int result, long long int power, long long int y_power) {
    int f = preflag;
    setflag(INV(x, y, x_0, result, power, y_power), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr,
                "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld\n",
                "x", x, "y", y, "x_0", x_0, "result", result, "power", power, "y_power", y_power);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_x, long long int temp_y,
               long long int temp_x_0, long long int temp_result, long long int temp_power,
               long long int temp_y_power, long long int x, long long int y, long long int x_0,
               long long int result, long long int power, long long int y_power) {
    int f = loopflag;
    setflag(INV(x, y, x_0, result, power, y_power), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld, %s : %lld\n",
                "x", temp_x, "y", temp_y, "x_0", temp_x_0, "result", temp_result, "power",
                temp_power, "y_power", temp_y_power);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, "
                "%s : %lld\n",
                "x", x, "y", y, "x_0", x_0, "result", result, "power", power, "y_power", y_power);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, x, y, x_0, result, power, y_power)             \
    \ 
{                                                                                        \
        \ 
    int f = postflag;                                                                         \
        \ 
   setflag(cond, postflag);                                                                   \
        \ 
    if (f == 0 && postflag == 1) {                                                            \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "x",                                                                                         \
                x, "y", y, "x_0", x_0, "result", result, "power", power, "y_power", y_power); \
            assert(0);                                                                        \
        \ 
}                                                                                    \
    }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int x = 0;
    long long int y = 1;
    long long int x_0 = 0;
    long long int result = 0;
    long long int power = 32;
    long long int y_power = 0;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(x, y, x_0, result, power, y_power)) {
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
        const uint8_t* honggBuf;
        HF_ITER(&honggBuf, &len);
        counter++;

        // Populate with Inputs
        long long int choices = honggBuf[0];

#ifndef READ_FROM_FLAG
        int x = honggBuf[45];
        int y = honggBuf[90];
#endif

        assume((x >= 0));
        assume((y != 0));
        assume((y_power >= 0));
        y_power = y << power;
        x_0 = x;

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "x", x, "y", y, "x_0", x_0, "result", result, "power", power, "y_power", y_power);

        // Translate()
        if (choices > 105) {
            x_0 = x;
            result = 0;
            power = 32;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, x, y, x_0, result, power, y_power);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, y, x_0, result, power, y_power));

            // Loop Condition
            if ((x >= y)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((x >= y) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_x = x;
                    long long int temp_y = y;
                    long long int temp_x_0 = x_0;
                    long long int temp_result = result;
                    long long int temp_power = power;
                    long long int temp_y_power = y_power;

                    // loop body
                    // printf("START : %d, %d, %d\n", x, y, result);
                    setPowerValue(&y_power, &x, &power);
                    result += 1 << power;
                    x = x - y_power;
                    // printf("END : %d, %d, %d\n", x, y, result);

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_y, temp_x_0, temp_result, temp_power,
                              temp_y_power, x, y, x_0, result, power, y_power);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");
                // post-condition
                postcheck(fptr, vars, ((x_0 == x + y * result)), x, y, x_0, result, power, y_power)
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

// (x_0 == x + y * result)