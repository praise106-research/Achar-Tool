
/*
 * P-Hat Transformation
 * Coverage
 * for 103.c file
 */

#include <103.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

#include <cstring>

extern void prebody_f1(long long int, long long int&);

extern void loopbody_f2(long long int, long long int&);

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!(cond)) flag = 1;

#define assume(cond) \
    if (!(cond)) exit(0);

#define INV(x) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int x) {
    int f = preflag;
    setflag(INV(x), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld\n", "x", x);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_x, long long int x) {
    int f = loopflag;
    setflag(INV(x), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld\n", "x", temp_x);
        fprintf(fptr, "LoopEnd : %s : %lld\n", "x", x);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, x) \
    \ 
{                                            \
        \ 
    int f = postflag;                             \
        \ 
   setflag(cond, postflag);                       \
        \ 
    if (f == 0 && postflag == 1) {                \
            \ 
        fprintf(fptr, "Post : %s : %lld\n", \ 
 "x",                                             \
                x);                               \
            assert(0);                            \
        \ 
}                                        \
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
    long long int choices = atoi(argv[2]);

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld\n", "x", x);

    // Translate()
    if (choices > 10000) {
        prebody_f1(choices, x);

        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(fptr, vars, x);
    } else {
        // loop-check program
        assume((loopflag + postflag < 2));
        assume(INV(x));

        // Loop Condition
        if ((x < 100)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x < 100) && unroll--) {
                assume((loopflag == 0));
                long long int temp_x = x;

                loopbody_f2(choices, x);

                loopcount++;
                loopcheck(fptr, vars, temp_x, x);
            }
        } else {
            // post-check program
            assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            postcheck(fptr, vars, ((x == 100)), x)
        }
    }

    // Regular Close FILE
    fclose(fptr);
    return 0;
}
