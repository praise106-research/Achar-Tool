
/*
 * P-Hat Transformation
 * for 89.c file
 */

#include <89.h>
#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!(cond)) flag = 1;

#define assume(cond) \
    if (!(cond)) continue;

#define INV(lock, x, y, v1, v2, v3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int lock, long long int x,
              long long int y, long long int v1, long long int v2, long long int v3) {
    int f = preflag;
    setflag(INV(lock, x, y, v1, v2, v3), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "lock", lock, "x", x, "y", y, "v1", v1, "v2", v2, "v3", v3);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_lock, long long int temp_x,
               long long int temp_y, long long int temp_v1, long long int temp_v2,
               long long int temp_v3, long long int lock, long long int x, long long int y,
               long long int v1, long long int v2, long long int v3) {
    int f = loopflag;
    setflag(INV(lock, x, y, v1, v2, v3), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "lock", temp_lock, "x", temp_x, "y", temp_y, "v1", temp_v1, "v2", temp_v2, "v3",
                temp_v3);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "lock", lock, "x", x, "y", y, "v1", v1, "v2", v2, "v3", v3);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, lock, x, y, v1, v2, v3) \
    \ 
{                                                                 \
        \ 
    int f = postflag;                                                  \
        \ 
   setflag(cond, postflag);                                            \
        \ 
    if (f == 0 && postflag == 1) {                                     \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "lock",                                                               \
                lock, "x", x, "y", y, "v1", v1, "v2", v2, "v3", v3);   \
            assert(0);                                                 \
        \ 
}                                                             \
    }

int main(int argc, char** argv) {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int lock;
    long long int x;
    long long int y;
    long long int v1;
    long long int v2;
    long long int v3;
#endif

    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    FILE* inputs = fopen("inputs/inputs_89.txt", "a");
    setvbuf(inputs, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "lock", lock, "x", x, "y", y, "v1", v1, "v2", v2, "v3", v3);

    if (INV(lock, x, y, v1, v2, v3)) {
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
        long long int choices = honggBuf[10];

#ifndef READ_FROM_FLAG
        long long int lock = honggBuf[0];
        long long int x = honggBuf[1];
        long long int y = honggBuf[2];
        long long int v1 = honggBuf[3];
        long long int v2 = honggBuf[4];
        long long int v3 = honggBuf[5];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "lock", lock, "x", x, "y", y, "v1", v1, "v2", v2, "v3", v3);

        fprintf(inputs, "%lld, %lld, %lld, %lld, %lld, %lld, %lld\n", lock, x, y, v1, v2, v3,
                choices);

        // Translate()
        if (choices > 10000) {
            (x = y);
            (lock = 1);
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, lock, x, y, v1, v2, v3);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(lock, x, y, v1, v2, v3));

            // Loop Condition
            if ((x != y)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((x != y) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_lock = lock;
                    long long int temp_x = x;
                    long long int temp_y = y;
                    long long int temp_v1 = v1;
                    long long int temp_v2 = v2;
                    long long int temp_v3 = v3;

                    {
                        // loop body
                        // non-deterministic
                        if (choices > 3500) {
                            {
                                (lock = 1);
                                (x = y);
                            }
                        } else {
                            {
                                (lock = 0);
                                (x = y);
                                (y = (y + 1));
                            }
                        }
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_lock, temp_x, temp_y, temp_v1, temp_v2, temp_v3,
                              lock, x, y, v1, v2, v3);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                postcheck(fptr, vars, ((lock == 1)), lock, x, y, v1, v2, v3)
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
