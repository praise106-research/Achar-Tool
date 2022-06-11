#include <39.h>
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

#define INV(n, c) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* buff, long long int n, long long int c) {
    int f = preflag;
    aflcrash(INV(n, c), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld\n", "n", n, "c", c);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* buff, long long int temp_n, long long int temp_c, long long int n,
               long long int c) {
    int f = loopflag;
    aflcrash(INV(n, c), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld\n", "n", temp_n, "c", temp_c);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld\n", "n", n, "c", c);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, n, c)     \
    \ 
{                                        \
        \ 
    int f = postflag;                         \
        \ 
   aflcrash(cond, postflag);                  \
        \ 
    if (f == 0 && postflag == 1) {            \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld\n", \ 
 "n",                                         \
                n, "c", c);                   \
            /* all models */ /* assert(0); */ \
        \ 
}                                    \
    }

int main() {
    // variable declarations
    long long int n;
    long long int c;

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
        c = buf[1];
        n = buf[2];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld\n", "n", n, "c", c);

        // pre-conditions
        // precheck
        // loopcond : unknown()

        if (choices > 10000) {
            // pre-conditions
            assume((preflag == 0));
            (c = 0);
            assume((n > 0));
            precount++;
            precheck(fptr, vars, n, c);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(n, c));

            // Loop Condition
            if ((choices > 1500)) {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((choices > 1500) && unroll--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_c = c;
                    long long int temp_n = n;
                    if (c == n) {
                        c = 1;
                    } else {
                        c = c + 1;
                    }

                    loopcount++;
                    loopcheck(fptr, vars, temp_n, temp_c, n, c);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                if (c == n) {
                    // assert( c >= 0);
                    postcount++;
                    postcheck(fptr, vars, (c <= n), n, c)
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