#include <16.h>
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

#define INV(x, m, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* file_descp, char* buff, long long int x, long long int m, long long int n) {
    int f = preflag;
    aflcrash(INV(x, m, n), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(file_descp, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "x", x, "m", m, "n", n);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* file_descp, char* buff, long long int temp_x, long long int temp_m,
               long long int temp_n, long long int x, long long int m, long long int n) {
    int f = loopflag;
    aflcrash(INV(x, m, n), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "x", temp_x, "m",
                temp_m, "n", temp_n);
        fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "x", x, "m", m, "n", n);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, x, m, n)                                               \
    \ 
{                                                                                           \
        \ 
    int f = postflag;                                                                            \
        \ 
   aflcrash(cond, postflag);                                                                     \
        \ 
    if (f == 0 && postflag == 1) {                                                               \
            \ 
        fprintf(file_descp, "Post : %s : %lld, %s : %lld, %s : %lld\n", "x", x, "m", m, "n", n); \
            /* all models */ /* assert(0); */                                                    \
        }                                                                                        \
    }

int main() {
    long long int x;
    long long int m;
    long long int n;

    char buff[2048];
    memset(buff, '\0', sizeof(buff));

    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 2048);

    for (;;) {
        size_t len;
        const int16_t* buf;

        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[0];
        x = buf[1];
        n = buf[2];
        m = buf[4];

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld", "x", x, "m", m, "n", n);

        // pre-conditions
        // assume((-10000 <= n && n < 10000));
        // precheck
        // loopcond : (x < n)

        if (choices > 10000) {
            // pre-conditions
            assume((preflag == 0));
            (x = 0);
            (m = 0);
            precount++;
            precheck(fptr, vars, x, m, n);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, m, n));

            // Loop Condition
            if ((x < n)) {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((x < n) && k--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_x = x;
                    long long int temp_m = m;
                    long long int temp_n = n;
                    {
                        if (choices > 5000) {
                            m = x;
                        }
                        x = x + 1;
                    }
                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_m, temp_n, x, m, n);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                if (n > 0) {
                    {
                        postcount++;
                        postcheck(fptr, vars, (m >= 0), x, m, n)
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