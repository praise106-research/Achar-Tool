#include <93.h>
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

#define INV(i, n, x, y) PHI

long long int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* buff, long long int i, long long int n, long long int x,
              long long int y) {
    int f = preflag;
    aflcrash(INV(i, n, x, y), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n", n, "x", x,
                "y", y);

        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* buff, long long int temp_i, long long int temp_n,
               long long int temp_x, long long int temp_y, long long int i, long long int n,
               long long int x, long long int y) {
    int f = loopflag;
    aflcrash(INV(i, n, x, y), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", temp_i, "n",
                temp_n, "x", temp_x, "y", temp_y);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n", n, "x",
                x, "y", y);

        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, i, n, x, y) \
    \ 
{                                          \
        \ 
    int f = postflag;                           \
        \ 
   aflcrash(cond, postflag);                    \
        \ 
    if (f == 0 && postflag == 1) {              \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                           \
                i, "n", n, "x", x, "y", y);     \
            /* all models */ /* assert(0); */   \
        \ 
}                                      \
    }

int main() {
    // variable declarations
    int i;
    int n;
    int x;
    int y;

    char buff[1024];
    memset(buff, '\0', sizeof(buff));

    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 1024);

    // freopen("models.txt", "w", stderr);

    for (;;) {
        size_t len;
        const int16_t* buf;

        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[0];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "n", n, "x", x,
                 "y", y);

        // pre-conditions
        i = buf[1];
        n = buf[2];
        x = buf[3];
        y = buf[4];
        // precheck
        // loopcond : (i < n)

        if (choices > 15000) {
            // pre-conditions
            assume((n >= 0));
            (i = 0);
            (x = 0);
            (y = 0);
            assume((preflag == 0));
            precount++;
            precheck(fptr, vars, i, n, x, y);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, n, x, y));

            // Loop Condition
            if ((i < n)) {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((i < n) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_i = i;
                    long long int temp_n = n;
                    long long int temp_x = x;
                    long long int temp_y = y;
                    // loop body
                    i = (i + 1);
                    if (choices > 5500) {
                        {
                            x = (x + 1);
                            y = (y + 2);
                        }
                    } else {
                        {
                            x = (x + 2);
                            y = (y + 1);
                        }
                    }
                    loopcount++;
                    loopcheck(fptr, vars, temp_i, temp_n, temp_x, temp_y, i, n, x, y);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcount++;
                postcheck(fptr, vars, (((3 * n) == (x + y))), i, n, x, y)
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