
/*
 *   P_Hat_ro Transforation for
 *   Loop Body Opaque Transformation
 */
#include <6.h>
#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

void setValue(long long int* a, int b) { *a = b; }

long long int sum(long long int a, long long int b) { return a + b; }

long long int substract(long long int a, long long int b) { return a - b; }

long long int multiply(long long int a, long long int b) { return a * b; }

#define UNROLL_LIMIT 64

#ifndef EXECUTE_LOOP
#define EXECUTE_LOOP 1
#endif

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(x, size, y, z) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int x, long long int size,
              long long int y, long long int z) {
    int f = preflag;
    setflag(INV(x, size, y, z), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", x, "size", size,
                "y", y, "z", z);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_x, long long int temp_size,
               long long int temp_y, long long int temp_z, long long int x, long long int size,
               long long int y, long long int z) {
    int f = loopflag;
    setflag(INV(x, size, y, z), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", temp_x,
                "size", temp_size, "y", temp_y, "z", temp_z);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", x, "size",
                size, "y", y, "z", z);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, x, size, y, z) \
    \ 
{                                                        \
        \ 
    int f = postflag;                                         \
        \ 
   setflag(cond, postflag);                                   \
        \ 
    if (f == 0 && postflag == 1) {                            \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "x",                                                         \
                x, "size", size, "y", y, "z", z);             \
            assert(0);                                        \
        \ 
}                                                    \
    }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int v1 = 0;
    long long int v2 = 0;
    long long int v3 = 0;
    long long int x;
    long long int size;
    long long int y;
    long long int z;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", x, "size", size,
            "y", y, "z", z);

    if (INV(x, size, y, z)) {
        fprintf(fptr, "True\n");
    } else {
        fprintf(fptr, "False\n");
    }
    assert(0);
#endif

    for (;;) {
        // Initialize HonggFuzz
        size_t len;
        const int16_t* honggBuf;
        HF_ITER(&honggBuf, &len);
        counter++;
        int reach_flag = 0;
        // Populate with Inputs
        long long int choices = honggBuf[0];

#ifndef READ_FROM_FLAG
        long long int x = honggBuf[1];
        long long int y = honggBuf[2];
        long long int z = honggBuf[3];
        long long int size = honggBuf[4];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "x", x, "size", size,
                 "y", y, "z", z);

        // Translate()
        if (choices > 10000) {
#ifdef EXECUTE_PRE

            (x = 0);
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, x, size, y, z);
#endif
        } else {
#ifdef EXECUTE_LOOP
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, size, y, z));
            // Loop Condition
            if ((x < size)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((x < size) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_x = x;
                    long long int temp_size = size;
                    long long int temp_y = y;
                    long long int temp_z = z;

                    // loop body
                    // (x = (x + 1));
                    x = sum(x, 1);
                    reach_flag = 1;
                    if (z <= y) {
                        y = z;
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    if (reach_flag = 1)
                        loopcheck(fptr, vars, temp_x, temp_size, temp_y, temp_z, x, size, y, z);
                }
            } else {
#ifdef EXECUTE_POST
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                if (size > 0) {
                    postcheck(fptr, vars, (z >= y), x, size, y, z)
                }
#endif
            }
#endif
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
