#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <nl-2.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define UNROLL_LIMIT 2

#define aflcrash(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(x, y) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* buff, long long int x, long long int y) {
    int f = preflag;
    aflcrash(INV(x, y), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld\n", "x", x, "y", y);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* buff, long long int temp_x, long long int temp_y, long long int x,
               long long int y) {
    int f = loopflag;
    aflcrash(INV(x, y), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld\n", "x", temp_x, "y", temp_y);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld\n", "x", x, "y", y);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, x, y) \
    \ 
{                                    \
        \ 
    int f = postflag;                     \
        \ 
   aflcrash(cond, postflag);              \
        \ 
    if (f == 0 && postflag == 1) {        \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld\n", \ 
 "x",                                     \
                x, "y", y);               \
        \ 
}                                \
    }

long long int func(long long int a, long long int b) {
    long long int c = 0;
    __asm__ __volatile__("imull %%ebx, %%eax;" : "=a"(c) : "a"(a), "b"(b));
    return c;
}

int main() {
    // variable declarations
    long long int x;
    long long int y;

    char buff[1024];
    memset(buff, '\0', sizeof(buff));

    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 1024);

    // freopen("models.txt", "w", stderr);

    for (;;) {
        size_t len;
        const int32_t* buf;

        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[0];
        x = buf[1];
        y = buf[2];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld\n", "x", x, "y", y);

        // pre-conditions
        // precheck
        // loopcond : unknown()

        if (choices > 35000) {
            // pre-conditions
            assume((preflag == 0));
            assume((x >= 0));
            (y = x * x);
            precount++;
            precheck(fptr, vars, x, y);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, y));

            // Loop Condition
            if ((choices > 1500)) {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((choices > 1500) && unroll--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_x = x;
                    long long int temp_y = y;
                    {
                        x = x + 1;
                        y = y + 1;
                    }

                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_y, x, y);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcount++;
                postcheck(fptr, vars, ((y <= func(x, x))), x, y)
            }
        }

        if (preflag + loopflag + postflag == 0 && counter == 100) {
            fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount",
                    loopcount, "postcount", postcount);
            counter = 0;
        }

        if (preflag + loopflag + postflag >= 3) {
            fclose(fptr);
            // All Models
            assert(0);
        }
    }

    fclose(fptr);
    return 0;
}