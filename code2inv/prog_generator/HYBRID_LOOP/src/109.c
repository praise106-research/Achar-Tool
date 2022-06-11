
/*
 *   P_Hat_ro Transforation for
 *   Loop Body Opaque Transformation
 */
#include <109.h>
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

#define INV(a, m, j, k, c) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int a, long long int m, long long int j,
              long long int k, long long int c) {
    int f = preflag;
    setflag(INV(a, m, j, k, c), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "m",
                m, "j", j, "k", k, "c", c);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_a, long long int temp_m,
               long long int temp_j, long long int temp_k, long long int temp_c, long long int a,
               long long int m, long long int j, long long int k, long long int c) {
    int f = loopflag;
    setflag(INV(a, m, j, k, c), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a",
                temp_a, "m", temp_m, "j", temp_j, "k", temp_k, "c", temp_c);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a,
                "m", m, "j", j, "k", k, "c", c);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, a, m, j, k, c) \
    \ 
{                                                        \
        \ 
    int f = postflag;                                         \
        \ 
   setflag(cond, postflag);                                   \
        \ 
    if (f == 0 && postflag == 1) {                            \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "a",                                                         \
                a, "m", m, "j", j, "k", k, "c", c);           \
            assert(0);                                        \
        \ 
}                                                    \
    }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int a;
    long long int m;
    long long int j;
    long long int k;
    long long int c;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "m",
            m, "j", j, "k", k, "c", c);

    if (INV(a, m, j, k, c)) {
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
        long long int m = honggBuf[1];
        long long int a = honggBuf[2];
        long long int j = honggBuf[3];
        long long int k = honggBuf[4];
        long long int c = honggBuf[5];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "m",
                 m, "j", j, "k", k, "c", c);

        // Translate()
        if (choices > 10000) {
#ifdef EXECUTE_PRE

            (j = 0);
            (k = 0);
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, a, m, j, k, c);
#endif
        } else {
#ifdef EXECUTE_LOOP
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(a, m, j, k, c));
            // Loop Condition
            if ((k < c)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((k < c) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_a = a;
                    long long int temp_m = m;
                    long long int temp_j = j;
                    long long int temp_k = k;
                    long long int temp_c = c;

                    {
                        // loop body
                        if (m < a) {
                            m = a;
                        }
                        // k = k + 1;
                        k = sum(k, 1);
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_a, temp_m, temp_j, temp_k, temp_c, a, m, j, k, c);
                }
            } else {
#ifdef EXECUTE_POST
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                if (c > 0) {
                    postcheck(fptr, vars, (a <= m), a, m, j, k, c)
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
