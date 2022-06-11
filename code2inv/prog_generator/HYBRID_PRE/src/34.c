
/*
 *   P_Hat_ro Transforation for
 *   Pre Header Opaque Transformation
 */
#include <34.h>
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

#ifndef EXECUTE_PRE
#define EXECUTE_PRE 1
#endif

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(n, x) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int n, long long int x) {
    int f = preflag;
    setflag(INV(n, x), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld\n", "n", n, "x", x);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_n, long long int temp_x,
               long long int n, long long int x) {
    int f = loopflag;
    setflag(INV(n, x), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld\n", "n", temp_n, "x", temp_x);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld\n", "n", n, "x", x);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, n, x) \
    \ 
{                                               \
        \ 
    int f = postflag;                                \
        \ 
   setflag(cond, postflag);                          \
        \ 
    if (f == 0 && postflag == 1) {                   \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld\n", \ 
 "n",                                                \
                n, "x", x);                          \
            assert(0);                               \
        \ 
}                                           \
    }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int n;
    long long int v1 = 0;
    long long int v2 = 0;
    long long int v3 = 0;
    long long int x;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld\n", "n", n, "x", x);

    if (INV(n, x)) {
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
        long long int x = honggBuf[1];
        long long int n = honggBuf[2];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld\n", "n", n, "x", x);

        // Translate()
        if (choices > 10000) {
#ifdef EXECUTE_PRE

            // (x = n);
            setValue(&x, n);
            reach_flag = 1;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            if (reach_flag == 1) precheck(fptr, vars, n, x);
#endif
        } else {
#ifdef EXECUTE_LOOP
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(n, x));
            // Loop Condition
            if ((x > 0)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((x > 0) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_n = n;
                    long long int temp_x = x;

                    {
                        // loop body
                        (x = (x - 1));
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_n, temp_x, n, x);
                }
            } else {
#ifdef EXECUTE_POST
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                if ((n >= 0)) {
                    postcheck(fptr, vars, ((x == 0)), n, x)
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
