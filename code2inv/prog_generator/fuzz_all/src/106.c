#include <106.h>
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

#define INV(a, m, j, k) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* file_descp, char* buff, long long int a, long long int m, long long int j,
              long long int k) {
    int f = preflag;
    aflcrash(INV(a, m, j, k), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(file_descp, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "m", m,
                "j", j, "k", k);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* file_descp, char* buff, long long int temp_a, long long int temp_m,
               long long int temp_j, long long int temp_k, long long int a, long long int m,
               long long int j, long long int k) {
    int f = loopflag;
    aflcrash(INV(a, m, j, k), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", temp_a,
                "m", temp_m, "j", temp_j, "k", temp_k);
        fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "m",
                m, "j", j, "k", k);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, a, m, j, k) \
    \ 
{                                                \
        \ 
    int f = postflag;                                 \
        \ 
   aflcrash(cond, postflag);                          \
        \ 
    if (f == 0 && postflag == 1) {                    \
            \ 
        fprintf(file_descp, "Post :%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
                 "a",                                 \
                a, "m", m, "j", j, "k", k);           \
            /* all models */ /* assert(0); */         \
        \ 
}                                            \
    }

int main() {
    // variable declarations
    long long int a, m, j, k;

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
        m = buf[1];
        a = buf[2];
        j = buf[4];
        k = buf[3];

        char vars[256];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 256, "%s : %lld, %s : %lld, %s : %lld, %s : %lld", "a", a, "m", m, "j", j,
                 "k", k);

        // pre-conditions
        // assume((-10000 <= m && m <= 10000));
        // assume((-10000 <= a && a <= 10000));
        // precheck
        // loopcond : (k < 1)

        if (choices > 10000) {
            // pre-conditions
            assume((preflag == 0));
            assume(a <= m);
            assume(j < 1);
            (k = 0);
            precount++;
            precheck(fptr, vars, a, m, j, k);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(a, m, j, k));

            // Loop Condition
            if ((k < 1)) {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((k < 1) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_a = a;
                    long long int temp_m = m;
                    long long int temp_j = j;
                    long long int temp_k = k;
                    // loop body
                    {
                        if (m < a) {
                            m = a;
                        }
                        k = k + 1;
                    }
                    loopcount++;
                    loopcheck(fptr, vars, temp_a, temp_m, temp_j, temp_k, a, m, j, k);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                {
                    postcount++;
                    postcheck(fptr, vars, (a >= m), a, m, j, k)
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