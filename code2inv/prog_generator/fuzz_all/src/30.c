#include <30.h>
#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

#define UNROLL_LIMIT 2

#define aflcrash(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(x) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* file_descp, char* buff, long long int x) {
    int f = preflag;
    aflcrash(INV(x), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(file_descp, "Pre : %s : %lld\n", "x", x);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* file_descp, char* buff, long long int temp_x, long long int x) {
    int f = loopflag;
    aflcrash(INV(x), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(file_descp, "LoopStart : %s : %lld\n", "x", temp_x);
        fprintf(file_descp, "LoopEnd : %s : %lld\n", "x", x);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, x)               \
    \ 
{                                                     \
        \ 
    int f = postflag;                                      \
        \ 
   aflcrash(cond, postflag);                               \
        \ 
    if (f == 0 && postflag == 1) {                         \
            \ 
        fprintf(file_descp, "Post : %s : %lld\n", "x", x); \
            /* all models */ /* assert(0); */              \
        \ 
}                                                 \
    }

int main() {
    // variable declarations
    long long int x;

    char buff[256];
    memset(buff, '\0', sizeof(buff));

    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 256);

    for (;;) {
        size_t len;
        const int16_t* buf;

        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[0];
        x = buf[1];

        char vars[32];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 32, "%s : %lld\n", "x", x);

        // pre-conditions
        // precheck
        // loopcond : (x > 0)

        if (choices > 10000) {
            // pre-conditions
            assume((preflag == 0));
            (x = 100);
            precount++;
            precheck(fptr, vars, x);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x));

            // Loop Condition
            if ((x > 0)) {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((x > 0) && k--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_x = x;
                    {
                        { (x = (x - 1)); }
                    }
                    loopcount++;
                    loopcheck(fptr, vars, temp_x, x);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                {
                    postcount++;
                    postcheck(fptr, vars, (x == 0), x)
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