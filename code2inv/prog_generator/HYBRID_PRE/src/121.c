
/*
 *   P_Hat_ro Transforation for
 *   Pre Header Opaque Transformation
 */
#include <121.h>
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

#define INV(i, sn) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int i, long long int sn) {
    int f = preflag;
    setflag(INV(i, sn), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld\n", "i", i, "sn", sn);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_i, long long int temp_sn,
               long long int i, long long int sn) {
    int f = loopflag;
    setflag(INV(i, sn), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld\n", "i", temp_i, "sn", temp_sn);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld\n", "i", i, "sn", sn);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, i, sn) \
    \ 
{                                                \
        \ 
    int f = postflag;                                 \
        \ 
   setflag(cond, postflag);                           \
        \ 
    if (f == 0 && postflag == 1) {                    \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld\n", \ 
 "i",                                                 \
                i, "sn", sn);                         \
            assert(0);                                \
        \ 
}                                            \
    }

int main() {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int i;
    long long int sn;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld\n", "i", i, "sn", sn);

    if (INV(i, sn)) {
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
        long long int i = honggBuf[1];
        long long int sn = honggBuf[2];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld\n", "i", i, "sn", sn);

        // Translate()
        if (choices > 10000) {
#ifdef EXECUTE_PRE

            i = 1;
            // (sn = 0);
            setValue(&sn, 0);
            reach_flag = 1;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            if (reach_flag == 1) precheck(fptr, vars, i, sn);
#endif
        } else {
#ifdef EXECUTE_LOOP
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, sn));
            // Loop Condition
            if ((i <= 8)) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((i <= 8) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_i = i;
                    long long int temp_sn = sn;

                    {
                        // loop body
                        (i = (i + 1));
                        (sn = (sn + 1));
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    loopcheck(fptr, vars, temp_i, temp_sn, i, sn);
                }
            } else {
#ifdef EXECUTE_POST
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");

                // post-condition
                if ((sn != 0)) {
                    postcheck(fptr, vars, ((sn == 8)), i, sn)
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
