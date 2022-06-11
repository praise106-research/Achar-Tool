
/*
 * P-Hat Transformation
 * for example_10.c file
 */

#include <assert.h>
#include <example_10.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <pthread.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> /* srand, rand */
#include <sys/file.h>
#include <time.h> /* time */

// Reference : https://docs.oracle.com/cd/E19683-01/806-6867/sync-12/index.html
pthread_mutex_t lock_mutex;

void set_lock(int* lock) {
    pthread_mutex_lock(&lock_mutex);
    *lock = 1;
    pthread_mutex_unlock(&lock_mutex);
}

void unset_lock(int* lock) {
    pthread_mutex_lock(&lock_mutex);
    *lock = 0;
    pthread_mutex_unlock(&lock_mutex);
}

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

// #define assume_exit(cond) if (!cond) exit(0);

#define INV(lock, x, y) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, int lock, int x, int y) {
    int f = preflag;
    setflag(INV(lock, x, y), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %d, %s : %d, %s : %d\n", "lock", lock, "x", x, "y", y);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, int temp_lock, int temp_x, int temp_y, int lock,
               int x, int y) {
    int f = loopflag;
    setflag(INV(lock, x, y), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %d, %s : %d, %s : %d\n", "lock", temp_lock, "x", temp_x,
                "y", temp_y);
        fprintf(fptr, "LoopEnd : %s : %d, %s : %d, %s : %d\n", "lock", lock, "x", x, "y", y);

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
        fprintf(fptr, "Post : %s : %d, %s : %d, %s : %d\n", \ 
 "lock",                                                   \
                lock, "x", x, "y", y);                     \
            assert(0);                                     \
        \ 
}                                                 \
    }

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
        const int8_t* honggBuf;
        HF_ITER(&honggBuf, &len);
        counter++;

        // Populate with Inputs
        int choices = honggBuf[0];

#ifndef READ_FROM_FLAG
        int x = honggBuf[1];
        int y = honggBuf[2];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %d, %s : %d, %s : %d\n", "lock", lock, "x", x, "y", y);

        // Translate()
        if (choices > 100) {
            asm("movl %1, %%eax;"
                "movl %%eax, %0;"
                : "=r"(x)
                : "r"(y)
                : "%eax");
            set_lock(&lock);
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, lock, x, y);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(lock, x, y));

            // Loop Condition
            if (x != y) {
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((x != y) && unroll--) {
                    assume((loopflag == 0));
                    int temp_lock = lock;
                    int temp_x = x;
                    int temp_y = y;

                    // loop body
                    if (choices > 5000) {
                        set_lock(&lock);
                        asm("movl %1, %%eax;"
                            "movl %%eax, %0;"
                            : "=r"(x)
                            : "r"(y)
                            : "%eax");
                    } else {
                        unset_lock(&lock);
                        asm("movl %1, %%eax;"
                            "movl %%eax, %0;"
                            : "=r"(x)
                            : "r"(y)
                            : "%eax");
                        // y = y + 1;
                        asm("movl %1, %%eax;"
                            "movl %%eax, %0;"
                            : "=r"(y)
                            : "r"(y + 1)
                            : "%eax");
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);
                    loopcount++;
                    loopcheck(fptr, vars, temp_lock, temp_x, temp_y, lock, x, y);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                postcount++;
                // fprintf(fptr, "Post\n");
                // post-condition
                postcheck(fptr, vars, ((lock == 1)), lock, x, y)
            }
        }

        // Print the counters if no flags are hit
        if (preflag + loopflag + postflag == 0 && counter == 100) {
            fprintf(fptr, "%s : %d, %s : %d, %s : %d\n", "precount", precount, "loopcount",
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

// ( y == ( 0 + y ) && x == ( 0 + y ) && lock == 1 )