#include <130.h>
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

#define INV(d1, d2, d3, x1, x2, x3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* buff, long long int d1, long long int d2, long long int d3,
              long long int x1, long long int x2, long long int x3) {
    int f = preflag;
    aflcrash(INV(d1, d2, d3, x1, x2, x3), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr,
                "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld\n",
                "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* buff, long long int temp_x1, long long int temp_x2,
               long long int temp_x3, long long int d1, long long int d2, long long int d3,
               long long int x1, long long int x2, long long int x3) {
    int f = loopflag;
    aflcrash(INV(d1, d2, d3, x1, x2, x3), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld, %s : %lld\n",
                "d1", d1, "d2", d2, "d3", d3, "x1", temp_x1, "x2", temp_x2, "x3", temp_x3);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, "
                "%s : %lld\n",
                "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, d1, d2, d3, x1, x2, x3)            \
    \ 
{                                                                 \
        \ 
    int f = postflag;                                                  \
        \ 
   aflcrash(cond, postflag);                                           \
        \ 
    if (f == 0 && postflag == 1) {                                     \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "d1",                                                                 \
                d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3); \
            /* all models */ /* assert(0); */                          \
        \ 
}                                                             \
    }

int main() {
    // variable declarations
    long long int d1 = 1;
    long long int d2 = 1;
    long long int d3 = 1;
    long long int x1;
    long long int x2;
    long long int x3;

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
        x2 = buf[1];
        x3 = buf[2];
        x1 = buf[3];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);

        // pre-conditions
        // assume((-10000 <= x2 && x1 <= 10000));
        // assume((-10000 <= x3 && x3 <= 10000));
        // precheck
        // loopcond : (x1 > 0)

        if (choices > 10000) {
            // pre-conditions
            assume((preflag == 0));
            (d1 = 1);
            (d2 = 1);
            (d3 = 1);
            (x1 = 1);
            precount++;
            precheck(fptr, vars, d1, d2, d3, x1, x2, x3);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(d1, d2, d3, x1, x2, x3));

            // Loop Condition
            if ((x1 > 0)) {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((x1 > 0) && k--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_x1 = x1;
                    long long int temp_x2 = x2;
                    long long int temp_x3 = x3;
                    {
                        if (x2 > 0) {
                            if (x3 > 0) {
                                x1 = x1 - d1;
                                x2 = x2 - d2;
                                x3 = x3 - d3;
                            }
                        }
                    }

                    loopcount++;
                    loopcheck(fptr, vars, temp_x1, temp_x2, temp_x3, d1, d2, d3, x1, x2, x3);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcount++;
                postcheck(fptr, vars, (x2 >= 0), d1, d2, d3, x1, x2, x3)
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