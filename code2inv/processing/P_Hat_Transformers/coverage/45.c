
/*
 * P-Hat Transformation
 * Coverage
 * for 45.c file
 */

#include <45.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

#include <cstring>

extern void prebody_f1(long long int, long long int&, long long int&);

extern void loopbody_f2(long long int, long long int&, long long int&);

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!(cond)) flag = 1;

#define assume(cond) \
    if (!(cond)) exit(0);

#define INV(c, n) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int c, long long int n) {
    int f = preflag;
    setflag(INV(c, n), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld\n", "c", c, "n", n);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_c, long long int temp_n,
               long long int c, long long int n) {
    int f = loopflag;
    setflag(INV(c, n), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld\n", "c", temp_c, "n", temp_n);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld\n", "c", c, "n", n);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, c, n) \
    \ 
{                                               \
        \ 
    int f = postflag;                                \
        \ 
   setflag(cond, postflag);                          \
        \ 
    if (f == 0 && postflag == 1) {                   \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld\n", \ 
 "c",                                                \
                c, "n", n);                          \
            assert(0);                               \
        \ 
}                                           \
    }

int main(int argc, char** argv) {
    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    // variable declarations
    long long int c = atoi(argv[1]);
    long long int n = atoi(argv[2]);
    long long int choices = atoi(argv[3]);

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld\n", "c", c, "n", n);

    // Translate()
    if (choices > 10000) {
        prebody_f1(choices, c, n);

        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(fptr, vars, c, n);
    } else {
        // loop-check program
        assume((loopflag + postflag < 2));
        assume(INV(c, n));

        // Loop Condition
        if ((choices > 2500)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((choices > 2500) && unroll--) {
                assume((loopflag == 0));
                long long int temp_c = c;
                long long int temp_n = n;

                loopbody_f2(choices, c, n);

                loopcount++;
                loopcheck(fptr, vars, temp_c, temp_n, c, n);
            }
        } else {
            // post-check program
            assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((c != n)) {
                postcheck(fptr, vars, ((c >= 0)), c, n)
            }
        }
    }

    // Regular Close FILE
    fclose(fptr);
    return 0;
}
