
#include <assert.h>
#include <example_1.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/file.h>

// https://godbolt.org/z/KhhWxnbqW
long long int foo(long long int sum, long long int i) {
    long long int product = 0;
    __asm__ __volatile__("imull %[d]\n" : [rtn] "=A"(product) : [a] "a"(i), [d] "rm"(i));
    return sum + product;
}

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(sum, i, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* modelFileBuffer, long long int sum, long long int i,
              long long int n) {
    int f = preflag;
    setflag(INV(sum, i, n), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "sum", sum, "i", i, "n", n);

        assert(0);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_sum, long long int temp_i,
               long long int temp_n, long long int sum, long long int i, long long int n) {
    int f = loopflag;
    setflag(INV(sum, i, n), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "sum", temp_sum, "i", temp_i,
                "n", temp_n);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "sum", sum, "i", i, "n", n);

        assert(0);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, modelFileBuffer, cond, sum, i, n) \
    \ 
{                                                    \
        \ 
    int f = postflag;                                     \
        \ 
   setflag(cond, postflag);                               \
        \ 
    if (f == 0 && postflag == 1) {                        \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "sum",                                                   \
                sum, "i", i, "n", n);                     \
            assert(0);                                    \
        \ 
}                                                \
    }

int main(int argc, char** argv) {
#ifndef READ_FROM_FLAG

    long long int sum;
    long long int i;
    long long int n;
#endif

    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(n, i, out)) {
        fprintf(fptr, "True\n");
    } else {
        fprintf(fptr, "False\n");
    }
    assert(0);
#endif

    for (;;) {
        // Initialize HonggFuzz
        size_t len;
        const int16_t* buf;
        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[0];

        // Populate with Inputs
#ifndef READ_FROM_FLAG
        long long int i = buf[34];
        long long int n = buf[45];
        long long int sum = buf[89];
#endif

        // Sum over natural numbers.
        assume((n >= 0));

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld\n", "sum", sum, "i", i, "n", n);

        if (choices > 10000) {
            assume((i == 0));
            assume((sum == 0));
            assume((n >= 0));

            precount++;
            // precheck
            precheck(fptr, vars, sum, i, n);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(sum, i, n));
            // Loop Condition
            if (i < n) {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((i < n) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_sum = sum;
                    long long int temp_i = i;
                    long long int temp_n = n;

                    // loop body
                    i = i + 1;
                    sum = foo(sum, i);

                    loopcount++;
                    loopcheck(fptr, vars, temp_sum, temp_i, temp_n, sum, i, n);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcount++;
                postcheck(fptr, vars, (sum == ((n * (n + 1) * (2 * n + 1)) / (6))), sum, i, n)
            }
        }

        // Print if no flags are hit.
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

    // Close FILE
    fclose(fptr);
    return 0;
}
