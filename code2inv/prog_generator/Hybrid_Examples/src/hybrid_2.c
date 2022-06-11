// P-Hat RO Transformation
/*
  mod2check() paper example
*/
#include <assert.h>
#include <hybrid_2.h>
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

#define INV(i, out, n, supported) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// Opaque Operation
int add_asm(int c, int a) {
    int ret = 0;
    __asm__ __volatile__("addl %%ebx, %%eax;" : "=a"(ret) : "a"(c), "b"(a));
    return ret;
}

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int i, long long int out,
              long long int n, long long int supported) {
    int f = preflag;
    setflag(INV(i, out, n, supported), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "out", out, "n",
                n, "supported", supported);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_i, long long int temp_out,
               long long int temp_n, long long int temp_supported, long long int i,
               long long int out, long long int n, long long int supported) {
    int f = loopflag;
    setflag(INV(i, out, n, supported), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", temp_i,
                "out", temp_out, "n", temp_n, "supported", temp_supported);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "out", out,
                "n", n, "supported", supported);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, i, out, n, supported) \
    \ 
{                                                               \
        \ 
    int f = postflag;                                                \
        \ 
   setflag(cond, postflag);                                          \
        \ 
    if (f == 0 && postflag == 1) {                                   \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                                                \
                i, "out", out, "n", n, "supported", supported);      \
            assert(0);                                               \
        \ 
}                                                           \
    }

// In the back-slice
// we only got loop section.
#define LOOP 1

int main() {
// variable declarations
#ifndef READ_FROM_FLAG
    long long int i;
    long long int out;
    long long int n;
    long long int supported = 1;
#endif

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    fprintf(fptr, "Checker : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "out", out, "n",
            n, "supported", supported);
    if (INV(i, out, n, supported)) {
        fprintf(fptr, "True");
    } else {
        fprintf(fptr, "False");
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
        long long int i = 0;
        long long int out = 0;
        long long int n = buf[3];
        int supported = 1;
#endif

        assume((n > 0));

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "out", out, "n",
                 n, "supported", supported);

        // Translate()
        if (choices > 10000) {
#ifdef PRE
            assume((n > 0));
            (out = 0);
            (i = 0);
            precount++;
            // fprintf(fptr, "Pre\n");
            // precheck
            precheck(fptr, vars, i, out, n, supported);
#endif
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, out, n, supported));

            // Loop Condition
            if ((i < n)) {
#ifdef LOOP
                // K-Bounded Exploration
                int unroll = UNROLL_LIMIT;
                while ((i < n) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_i = i;
                    long long int temp_out = out;
                    long long int temp_n = n;
                    long long int temp_supported = supported;

                    // loop body
                    i = i + 1;
                    if ((n % 2) == 0) {
                        // Opaque operation
                        // Z3 Gets stuck here
                        // Keeps producing CEs.
                        // assume((false))
                        out = add_asm(out, 1);
                        reach_flag = 1;
                    } else {
                        out = out + 2;
                    }

                    // fprintf(fptr, "Loop\n");
                    // fprintf(fptr, "Flag : %d\n", reach_flag);
                    // assume(reach_flag);

                    loopcount++;
                    if (reach_flag == 1)
                        loopcheck(fptr, vars, temp_i, temp_out, temp_n, temp_supported, i, out, n,
                                  supported);
                }
#endif
            } else {
#ifdef POST
                // post-check program
                assume((postflag == 0));
                // fprintf(fptr, "Post\n");

                // post-condition
                if ((i == n) && (n % 2 != 0)) {
                    postcount++;
                    postcheck(fptr, vars, ((out == 2 * n)), i, out, n, supported)
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

// ( i <= n ) && ( n > 0 ) && ( ( ( n % 2 == 0 ) && ( out == i ) && ( supported
// == 1 ) ) "||" ( ( n % 2 == 1 ) && ( out == 2 * i ) && ( supported == 0 ) ) )