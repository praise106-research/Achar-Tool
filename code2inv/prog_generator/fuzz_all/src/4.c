#include <4.h>
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

#define INV(x, y, z) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* file_descp, char* buff, long long int x, long long int y, long long int z) {
    int f = preflag;
    aflcrash(INV(x, y, z), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(file_descp, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "z", z);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* file_descp, char* buff, long long int temp_x, long long int temp_y,
               long long int temp_z, long long int x, long long int y, long long int z) {
    int f = loopflag;
    aflcrash(INV(x, y, z), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(file_descp, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "x", temp_x, "y",
                temp_y, "z", temp_z);
        fprintf(file_descp, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "z", z);
        /* all models */ /* assert(0); */
    }
}

// COMMENT : Postcheck template
#define postcheck(file_descp, buff, cond, x, y, z)                                              \
    \ 
{                                                                                          \
        \ 
    int f = postflag;                                                                           \
        \ 
   aflcrash(cond, postflag);                                                                    \
        \ 
    if (f == 0 && postflag == 1) {                                                              \
            \ 
        fprintf(file_descp, "Post :%s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "z", z); \
            /* all models */ /* assert(0); */                                                   \
        }                                                                                       \
    }

int main() {
    // variable declarations
    long long int x;
    long long int y;
    long long int z;

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
        x = buf[3];
        y = buf[1];
        z = buf[2];

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "z", z);

        // pre-conditions
        // assume((-10000 <= y && y <= 10000));
        // assume((-10000 <= z && z <= 10000));
        // precheck
        // loopcond : (x < 500)

        if (choices > 10000) {
            // pre-conditions
            assume((preflag == 0));
            (x = 0);
            precount++;
            precheck(fptr, vars, x, y, z);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, y, z));

            // Loop Condition
            if ((x < 500)) {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((x < 500) && k--) {
                    assume((loopflag == 0));
                    long long int temp_x = x;
                    long long int temp_y = y;
                    long long int temp_z = z;
                    // loop body
                    {
                        x += 1;
                        if (z <= y) {
                            y = z;
                        }
                    }
                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_y, temp_z, x, y, z);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                {
                    postcount++;
                    postcheck(fptr, vars, (z >= y), x, y, z)
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