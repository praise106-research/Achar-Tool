
#include <assert.h>
#include <hybrid_6.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

void setValue(long long int* a, int b) { *a = b; }

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(c) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int c) {
    int f = preflag;
    setflag(INV(c), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld\n", "c", c);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_c, long long int c) {
    int f = loopflag;
    setflag(INV(c), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld\n", "c", temp_c);
        fprintf(fptr, "LoopEnd : %s : %lld\n", "c", c);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, c) \
    \ 
{                                            \
        \ 
    int f = postflag;                             \
        \ 
   setflag(cond, postflag);                       \
        \ 
    if (f == 0 && postflag == 1) {                \
            \ 
        fprintf(fptr, "Post : %s : %lld\n", \ 
 "c",                                             \
                c);                               \
            assert(0);                            \
        \ 
}                                        \
    }

#define LOOP 1
#define PRE 1

int main() {
// variable declarations
#ifndef READ_FROM_FLAG
    int c;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld\n", "c", c);

    if (INV(c)) {
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
        const int16_t* buf;
        HF_ITER(&buf, &len);
        counter++;

        // Populate with Inputs
        long long int choices = buf[0];

#ifndef READ_FROM_FLAG
        int c = buf[1] % 50000;
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld\n", "c", c);

        // Translate()
        if (choices > 10000) {
#ifdef PRE
            setValue(&c, 0);
            reach_flag = 1;
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            if (reach_flag == 1) precheck(fptr, vars, c);
#endif
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(c));

            // Loop Condition
            if ((choices > 2500)) {
#ifdef LOOP
                reach_flag = 0;
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((choices > 2500) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_c = c;

                    // loop body
                    if (choices > 3500) {
                        if ((c != 4)) {
                            // Opaque Operation
                            // assume((false))
                            asm("incl %0" : "+r"(c));
                            reach_flag = 1;
                        }
                    } else {
                        if ((c == 4)) {
                            (c = 1);
                        }
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    if (reach_flag == 1) loopcheck(fptr, vars, temp_c, c);
                }
#endif
            } else {
#ifdef POST
                // post-check program
                assume((postflag == 0));
                // fprintf(fptr, "Post\n");

                // post-condition
                if ((c != 4)) {
                    postcount++;
                    postcheck(fptr, vars, ((c >= 0)), c)
                }
#endif
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
