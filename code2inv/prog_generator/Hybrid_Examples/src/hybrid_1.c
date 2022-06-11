// P-Hat-ro
/*
  Paper : multiply() example
*/
#include <assert.h>
#include <hybrid_1.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define UNROLL_LIMIT 64

#define aflcrash(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(a, b, x, y, r, supported, shift) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* buff, long long int a, long long int b, long long int x,
              long long int y, long long int r) {
    int f = preflag;
    aflcrash(INV(a, b, x, y, r, supported, shift), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "b",
                b, "x", x, "y", y, "r", r);

        assert(0);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* buff, long long int temp_a, long long int temp_b,
               long long int temp_x, long long int temp_y, long long int temp_r,
               long long int temp_supported, long long int temp_shift, long long int a,
               long long int b, long long int x, long long int y, long long int r,
               long long int supported, long long int shift) {
    int f = loopflag;
    aflcrash(INV(a, b, x, y, r, supported, shift), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a",
                temp_a, "b", temp_b, "x", temp_x, "y", temp_y, "r", temp_r);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a,
                "b", b, "x", x, "y", y, "r", r);

        assert(0);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, a, b, x, y, r)  \
    \ 
{                                              \
        \ 
    int f = postflag;                               \
        \ 
   aflcrash(cond, postflag);                        \
        \ 
    if (f == 0 && postflag == 1) {                  \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "a",                                               \
                a, "b", b, "x", x, "y", y, "r", r); \
            assert(0);                              \
        \ 
}                                          \
    }

// In the back-slice
// we only got loop section.
#define LOOP 1

int main() {
    // variable declarations
    long long int a;
    long long int b;
    long long int x;
    long long int y;
    long long int r;
    long long int shift;
    long long int supported;

    char buff[1024];
    memset(buff, '\0', sizeof(buff));

    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 1024);

    // freopen("models.txt", "w", stderr);

    for (;;) {
        int reach_flag = 0;
        size_t len;
        const int16_t* buf;

        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[0];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "b",
                 b, "x", x, "y", y, "r", r);

        // HonggFuzz Inputs
        a = buf[2];
        b = buf[4];

        // HonggFuzz Inits
        x = a;
        y = b;
        r = 0;
        assume((b >= 0));

        if (choices > 10000) {
            // pre-conditions
#ifdef PRE
            assume((a >= 0));
            assume((b >= 0));
            x = a;
            y = b;
            r = 0;
            assume((preflag == 0));
            precount++;
            precheck(fptr, vars, a, b, x, y, r);
#endif
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(a, b, x, y, r, supported, shift));
            // loopcond : (b != 0)
            if ((b != 0)) {
#ifdef LOOP
                // K-Bounded Unrolling [Hyperparameter]
                int unroll = UNROLL_LIMIT;
                while ((b != 0) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_a = a;
                    long long int temp_b = b;
                    long long int temp_x = x;
                    long long int temp_y = y;
                    long long int temp_r = r;

                    long long int temp_supported = supported;
                    long long int temp_shift = shift;

                    // loop-body
                    shift = 0;
                    if (supported) {
                        shift = __builtin_ctz(b);
                        reach_flag = 1;
                    } else {
                        shift = 0;
                    }
                    if (shift) {
                        r += a << shift;
                        b -= 1 << shift;
                    } else {
                        r += a;
                        b -= 1;
                    }

                    loopcount++;
                    if (reach_flag == 1)
                        loopcheck(fptr, vars, temp_a, temp_b, temp_x, temp_y, temp_r,
                                  temp_supported, temp_shift, a, b, x, y, r, supported, shift);
                }
#endif
            } else {
#ifdef POST
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcount++;
                postcheck(fptr, vars, ((r == x * y)), a, b, x, y, r)
#endif
            }
        }

        if (preflag + loopflag + postflag == 0 && counter == 100) {
            fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount",
                    loopcount, "postcount", postcount);
            counter = 0;
        }

        if (preflag + loopflag + postflag >= 3) {
            fclose(fptr);
            assert(0);
        }
    }

    fclose(fptr);
    return 0;
}
