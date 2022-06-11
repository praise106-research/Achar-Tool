#include <79.h>
#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define UNROLL_LIMIT 2

#define aflcrash(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(i, x, y) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* buff, long long int i, long long int x, long long int y) {
    int f = preflag;
    aflcrash(INV(i, x, y), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "i", i, "x", x, "y", y);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* buff, long long int temp_i, long long int temp_x,
               long long int temp_y, long long int i, long long int x, long long int y) {
    int f = loopflag;
    aflcrash(INV(i, x, y), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "i", temp_i, "x", temp_x,
                "y", temp_y);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "i", i, "x", x, "y", y);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, i, x, y)  \
    \ 
{                                        \
        \ 
    int f = postflag;                         \
        \ 
   aflcrash(cond, postflag);                  \
        \ 
    if (f == 0 && postflag == 1) {            \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                         \
                i, "x", x, "y", y);           \
            /* all models */ /* assert(0); */ \
        \ 
}                                    \
    }

int main() {
    // variable declarations
    long long int i;
    long long int x;
    long long int y;

    char buff[2048];
    memset(buff, '\0', sizeof(buff));

    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 2048);

    // freopen("models.txt", "w", stderr);

    for (;;) {
        size_t len;
        const int16_t* buf;

        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[0];
        i = buf[1];
        x = buf[2];
        y = buf[3];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld\n", "i", i, "x", x, "y", y);

        // pre-conditions
        // precheck
        // loopcond : unknown()

        if (choices > 10000) {
            // pre-conditions
            assume((preflag == 0));
            (i = 0);
            assume((x >= 0));
            assume((y >= 0));
            assume((x >= y));
            precount++;
            precheck(fptr, vars, i, x, y);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, x, y));

            // Loop Condition
            if ((choices > 1500)) {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((choices > 1500) && unroll--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_i = i;
                    long long int temp_x = x;
                    long long int temp_y = y;

                    if (i < y) {
                        i = i + 1;
                    }

                    loopcount++;
                    loopcheck(fptr, vars, temp_i, temp_x, temp_y, i, x, y);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                if ((i >= x)) {
                    if ((0 > i)) {
                        postcount++;
                        postcheck(fptr, vars, ((i >= y)), i, x, y)
                    }
                }
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