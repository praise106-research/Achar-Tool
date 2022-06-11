// P-Hat RO Transformation
/*
  example_87() paper example
*/
#include <assert.h>
#include <hybrid_9.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(lock, x, y) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int lock, long long int x,
              long long int y) {
    int f = preflag;
    setflag(INV(lock, x, y), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "lock", lock, "x", x, "y", y);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_lock, long long int temp_x,
               long long int temp_y, long long int lock, long long int x, long long int y) {
    int f = loopflag;
    setflag(INV(lock, x, y), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "lock", temp_lock, "x",
                temp_x, "y", temp_y);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "lock", lock, "x", x, "y", y);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, lock, x, y) \
    \ 
{                                                     \
        \ 
    int f = postflag;                                      \
        \ 
   setflag(cond, postflag);                                \
        \ 
    if (f == 0 && postflag == 1) {                         \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "lock",                                                   \
                lock, "x", x, "y", y);                     \
            assert(0);                                     \
        \ 
}                                                 \
    }

// In the back-slice
// we only got loop section.
#define LOOP 1

int main() {
// variable declarations
#ifndef READ_FROM_FLAG

    int lock;
    int x;
    int y;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld, %s : %lld\n", "lock", lock, "x", x, "y", y);

    if (INV(lock, x, y)) {
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
        int x = buf[1];
        int y = buf[2];
        int lock = buf[3];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld\n", "lock", lock, "x", x, "y", y);

        // Translate()
        if (choices > 10000) {
#ifdef PRE
            (x = y);
            (lock = 1);
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, lock, x, y);
#endif
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(lock, x, y));

            // Loop Condition
            if ((x != y)) {
#ifdef LOOP
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((x != y) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_lock = lock;
                    long long int temp_x = x;
                    long long int temp_y = y;

                    // loop body
                    if (choices > 2500) {
                        {
                            (lock = 1);
                            (x = y);
                        }
                    } else {
                        {
                            // assume((false))
                            // unset_lock(lock)
                            // lock = 0;
                            asm("movl %1, %%eax;"
                                "movl %%eax, %0;"
                                : "=r"(lock)
                                : "r"(0)
                                : "%eax");
                            // x = y;
                            asm("movl %1, %%eax;"
                                "movl %%eax, %0;"
                                : "=r"(x)
                                : "r"(y)
                                : "%eax");
                            // y = y + 1;
                            asm("incl %0" : "+r"(y));
                            reach_flag = 1;
                        }
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    if (reach_flag == 1)
                        loopcheck(fptr, vars, temp_lock, temp_x, temp_y, lock, x, y);
                }
#endif
            } else {
#ifdef POST
                // post-check program
                assume((postflag == 0));
                // fprintf(fptr, "Post\n");

                // post-condition
                postcount++;
                postcheck(fptr, vars, ((lock == 1)), lock, x, y)
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
