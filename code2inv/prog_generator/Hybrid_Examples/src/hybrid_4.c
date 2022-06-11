
#include <assert.h>
#include <hybrid_4.h>
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

#define INV(n, c) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int n, long long int c) {
    int f = preflag;
    setflag(INV(n, c), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld\n", "n", n, "c", c);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_n, long long int temp_c,
               long long int n, long long int c) {
    int f = loopflag;
    setflag(INV(n, c), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld\n", "n", temp_n, "c", temp_c);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld\n", "n", n, "c", c);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, n, c) \
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
                n, "c", c);                          \
            assert(0);                               \
        \ 
}                                           \
    }

#define LOOP 1

int increment(int c, int a) {
    int ret = 0;
    __asm__ __volatile__("addl %%ebx, %%eax;" : "=a"(ret) : "a"(c), "b"(a));
    return ret;
}

int main() {
// variable declarations
#ifndef READ_FROM_FLAG

    long long int n;
    long long int c;
    unsigned char supported = 1;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld\n", "n", n, "c", c);

    if (INV(n, c)) {
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
        long long int n = buf[1];
        long long int c = buf[2];
#endif

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld\n", "n", n, "c", c);

        // Translate()
        if (choices > 10000) {
#ifdef PRE
            assume(n > 0);
            (c = 0);
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, n, c);
#endif
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(n, c));

            // Loop Condition
            if ((choices > 2500)) {
#ifdef LOOP
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((choices > 2500) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_n = n;
                    long long int temp_c = c;

                    // loop body
                    {
                        if (c == n && (supported == 0)) {
                            c = 1;
                        } else {
                            // Opaque Operation
                            // assume((false))
                            c = increment(c, 1);
                            reach_flag = 1;
                        }
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    if (reach_flag == 1) loopcheck(fptr, vars, temp_n, temp_c, n, c);
                }
#endif
            } else {
#ifdef POST
                // post-check program
                assume((postflag == 0));
                // fprintf(fptr, "Post\n");

                // post-condition
                if (c == n) {
                    postcount++;
                    postcheck(fptr, vars, (c >= 0), n, c)
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
