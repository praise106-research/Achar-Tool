#include <82.h>
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

#define INV(i, x, y, z1, z2, z3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* file_descp, char* buff, long long int i, long long int x, long long int y,
              long long int z1, long long int z2, long long int z3) {
    int f = preflag;
    aflcrash(INV(i, x, y, z1, z2, z3), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(file_descp,
                "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld\n",
                "i", i, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* file_descp, char* buff, long long int temp_i, long long int temp_x,
               long long int temp_y, long long int i, long long int x, long long int y,
               long long int z1, long long int z2, long long int z3) {
    int f = loopflag;
    aflcrash(INV(i, x, y, z1, z2, z3), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(file_descp,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld, %s : %lld\n",
                "i", temp_i, "x", temp_x, "y", temp_y, "z1", z1, "z2", z2, "z3", z3);
        fprintf(file_descp,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, "
                "%s : %lld\n",
                "i", i, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, i, x, y, z1, z2, z3)             \
    \ 
{                                                                     \
        \ 
    int f = postflag;                                                      \
        \ 
   aflcrash(cond, postflag);                                               \
        \ 
    if (f == 0 && postflag == 1) {                                         \
            \ 
        fprintf(file_descp,                                                \
                "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : " \
                "%lld, %s : %lld\n",                                       \
                "i", i, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);     \
            /* all models */ /* assert(0); */                              \
        }                                                                  \
    }

int main() {
    // variable declarations
    long long int i;
    long long int x;
    long long int y;
    long long int z1 = 0;
    long long int z2 = 0;
    long long int z3 = 0;

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
        y = buf[1];
        i = buf[2];
        x = buf[3];

        char vars[256];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 256, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld", "i",
                 i, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);

        // pre-conditions
        // assume((-10000 <= y && y <= 10000));
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
            precheck(fptr, vars, i, x, y, z1, z2, z3);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(i, x, y, z1, z2, z3));

            // Loop Condition
            if ((choices > 2500)) {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((choices > 2500) && k--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_i = i;
                    long long int temp_x = x;
                    long long int temp_y = y;
                    {
                        if ((i < y)) {
                            (i = (i + 1));
                        }
                    }
                    loopcount++;
                    loopcheck(fptr, vars, temp_i, temp_x, temp_y, i, x, y, z1, z2, z3);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                if ((i >= x)) {
                    if ((0 > i)) {
                        postcount++;
                        postcheck(fptr, vars, (i >= y), i, x, y, z1, z2, z3)
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