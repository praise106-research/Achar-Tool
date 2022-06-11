
/*
 * P-Hat Transformation
 * Coverage
 * for 67.c file
 */

#include <67.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

#include <cstring>

extern void prebody_f1(long long int, long long int&, long long int&, long long int&);

extern void loopbody_f2(long long int, long long int&, long long int&, long long int&);

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!(cond)) flag = 1;

#define assume(cond) \
    if (!(cond)) exit(0);

#define INV(x, y, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int x, long long int y,
              long long int n) {
    int f = preflag;
    setflag(INV(x, y, n), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "n", n);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_x, long long int temp_y,
               long long int temp_n, long long int x, long long int y, long long int n) {
    int f = loopflag;
    setflag(INV(x, y, n), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "x", temp_x, "y", temp_y,
                "n", temp_n);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "n", n);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, x, y, n) \
    \ 
{                                                  \
        \ 
    int f = postflag;                                   \
        \ 
   setflag(cond, postflag);                             \
        \ 
    if (f == 0 && postflag == 1) {                      \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "x",                                                   \
                x, "y", y, "n", n);                     \
            assert(0);                                  \
        \ 
}                                              \
    }

int main(int argc, char** argv) {
    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    // variable declarations
    long long int x = atoi(argv[1]);
    long long int y = atoi(argv[2]);
    long long int n = atoi(argv[3]);
    long long int choices = atoi(argv[4]);

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld\n", "x", x, "y", y, "n", n);

    // Translate()
    if (choices > 10000) {
        prebody_f1(choices, x, y, n);

        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(fptr, vars, x, y, n);
    } else {
        // loop-check program
        assume((loopflag + postflag < 2));
        assume(INV(x, y, n));

        // Loop Condition
        if ((x <= n)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x <= n) && unroll--) {
                assume((loopflag == 0));
                long long int temp_x = x;
                long long int temp_y = y;
                long long int temp_n = n;

                loopbody_f2(choices, x, y, n);

                loopcount++;
                loopcheck(fptr, vars, temp_x, temp_y, temp_n, x, y, n);
            }
        } else {
            // post-check program
            assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if (n > 0) {
                postcheck(fptr, vars, (y >= 0), x, y, n)
            }
        }
    }

    // Regular Close FILE
    fclose(fptr);
    return 0;
}
