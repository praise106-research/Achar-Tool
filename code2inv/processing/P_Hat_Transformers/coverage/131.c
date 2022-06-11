
/*
 * P-Hat Transformation
 * Coverage
 * for 131.c file
 */

#include <131.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

#include <cstring>

extern void prebody_f1(long long int, long long int&, long long int&, long long int&,
                       long long int&, long long int&, long long int&);

extern void loopbody_f2(long long int, long long int&, long long int&, long long int&,
                        long long int&, long long int&, long long int&);

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!(cond)) flag = 1;

#define assume(cond) \
    if (!(cond)) exit(0);

#define INV(d1, d2, d3, x1, x2, x3) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int d1, long long int d2,
              long long int d3, long long int x1, long long int x2, long long int x3) {
    int f = preflag;
    setflag(INV(d1, d2, d3, x1, x2, x3), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_d1, long long int temp_d2,
               long long int temp_d3, long long int temp_x1, long long int temp_x2,
               long long int temp_x3, long long int d1, long long int d2, long long int d3,
               long long int x1, long long int x2, long long int x3) {
    int f = loopflag;
    setflag(INV(d1, d2, d3, x1, x2, x3), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "d1", temp_d1, "d2", temp_d2, "d3", temp_d3, "x1", temp_x1, "x2", temp_x2, "x3",
                temp_x3);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "d1", d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, d1, d2, d3, x1, x2, x3) \
    \ 
{                                                                 \
        \ 
    int f = postflag;                                                  \
        \ 
   setflag(cond, postflag);                                            \
        \ 
    if (f == 0 && postflag == 1) {                                     \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "d1",                                                                 \
                d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3); \
            assert(0);                                                 \
        \ 
}                                                             \
    }

int main(int argc, char** argv) {
    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    // variable declarations
    long long int d1 = atoi(argv[1]);
    long long int d2 = atoi(argv[2]);
    long long int d3 = atoi(argv[3]);
    long long int x1 = atoi(argv[4]);
    long long int x2 = atoi(argv[5]);
    long long int x3 = atoi(argv[6]);
    long long int choices = atoi(argv[7]);

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "d1",
             d1, "d2", d2, "d3", d3, "x1", x1, "x2", x2, "x3", x3);

    // Translate()
    if (choices > 10000) {
        prebody_f1(choices, d1, d2, d3, x1, x2, x3);

        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(fptr, vars, d1, d2, d3, x1, x2, x3);
    } else {
        // loop-check program
        assume((loopflag + postflag < 2));
        assume(INV(d1, d2, d3, x1, x2, x3));

        // Loop Condition
        if ((x1 > 0)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x1 > 0) && unroll--) {
                assume((loopflag == 0));
                long long int temp_d1 = d1;
                long long int temp_d2 = d2;
                long long int temp_d3 = d3;
                long long int temp_x1 = x1;
                long long int temp_x2 = x2;
                long long int temp_x3 = x3;

                loopbody_f2(choices, d1, d2, d3, x1, x2, x3);

                loopcount++;
                loopcheck(fptr, vars, temp_d1, temp_d2, temp_d3, temp_x1, temp_x2, temp_x3, d1, d2,
                          d3, x1, x2, x3);
            }
        } else {
            // post-check program
            assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            postcheck(fptr, vars, (x3 >= 0), d1, d2, d3, x1, x2, x3)
        }
    }

    // Regular Close FILE
    fclose(fptr);
    return 0;
}
