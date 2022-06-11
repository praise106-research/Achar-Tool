#include <109.h>
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

#define INV(a, c, m, j, k) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* buff, long long int a, long long int c, long long int m,
              long long int j, long long int k) {
    int f = preflag;
    aflcrash(INV(a, c, m, j, k), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "c",
                c, "m", m, "j", j, "k", k);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* buff, long long int temp_a, long long int temp_c,
               long long int temp_m, long long int temp_j, long long int temp_k, long long int a,
               long long int c, long long int m, long long int j, long long int k) {
    int f = loopflag;
    aflcrash(INV(a, c, m, j, k), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a",
                temp_a, "c", temp_c, "m", temp_m, "j", temp_j, "k", temp_k);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a,
                "c", c, "m", m, "j", j, "k", k);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, a, c, m, j, k)  \
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
                a, "c", c, "m", m, "j", j, "k", k); \
            /* all models */ /* assert(0); */       \
        \ 
}                                          \
    }

int main() {
    // variable declarations
    long long int a;
    long long int c;
    long long int m;
    long long int j;
    long long int k;

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
        a = buf[1];
        c = buf[2];
        m = buf[3];
        j = buf[4];
        k = buf[5];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "c",
                 c, "m", m, "j", j, "k", k);

        // pre-conditions
        // precheck
        // loopcond : (k < c)

        if (choices > 10000) {
            // pre-conditions
            assume((preflag == 0));
            (j = 0);
            (k = 0);
            precount++;
            precheck(fptr, vars, a, c, m, j, k);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(a, c, m, j, k));

            // Loop Condition
            if ((k < c)) {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((k < c) && unroll--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_a = a;
                    long long int temp_c = c;
                    long long int temp_m = m;
                    long long int temp_j = j;
                    long long int temp_k = k;
                    {
                        if (m < a) {
                            m = a;
                        }
                        k = k + 1;
                    }

                    loopcount++;
                    loopcheck(fptr, vars, temp_a, temp_c, temp_m, temp_j, temp_k, a, c, m, j, k);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                if (c > 0) {
                    postcount++;
                    postcheck(fptr, vars, (a <= m), a, c, m, j, k)
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