#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <nl-5.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define UNROLL_LIMIT 64

#define aflcrash(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(x, z, w) PHI

double counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* buff, long long int x, long long int z, long long int w) {
    int f = preflag;
    aflcrash(INV(x, z, w), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "x", x, "z", z, "w", w);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* buff, long long int temp_x, long long int temp_y,
               long long int temp_w, long long int x, long long int y, long long int w) {
    int f = loopflag;
    aflcrash(INV(x, y, z), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "x", temp_x, "y", temp_y,
                "z", temp_w);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "z", w);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, x, z, w) \
    \ 
{                                       \
        \ 
    int f = postflag;                        \
        \ 
   aflcrash(cond, postflag);                 \
        \ 
    if (f == 0 && postflag == 1) {           \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "x",                                        \
                x, "z", z, "w", w);          \
        \ 
}                                   \
    }

long long int func(long long int a, long long int b) { return a * b; }

int main() {
    long long int x, z, w;

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
        z = buf[1];
        x = buf[2];
        w = buf[3];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld\n", "x", x, "z", z, "w", w);

        // pre-conditions
        // precheck
        // loopcond : unknown()

        if (choices > 35000) {
            // pre-conditions
            assume((preflag == 0));
            (z = w * x);
            precount++;
            precheck(fptr, vars, x, z, w);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(x, z, w));

            // Loop Condition
            if ((choices > 1500)) {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((choices > 1500) && unroll--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_w = w;
                    long long int temp_x = x;
                    long long int temp_z = z;
                    {
                        w = func(w, x);
                        z = func(z, x);
                    }

                    loopcount++;
                    loopcheck(fptr, vars, temp_x, temp_z, temp_w, x, z, w);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcount++;
                postcheck(fptr, vars, (z == w * x), x, z, w)
            }
        }

        if (preflag + loopflag + postflag == 0 && counter == 100) {
            fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount",
                    loopcount, "postcount", postcount);
            counter = 0;
        }

        if (preflag + loopflag + postflag >= 3) {
            fclose(fptr);
            assert(0);
        }
    }

    fclose(fptr);
    return 0;
}