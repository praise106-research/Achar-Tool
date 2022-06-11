
/*
 * P-Hat Transformation
 * Coverage
 * for 132.c file
 */

#include <132.h>
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
                       long long int&);

extern void loopbody_f2(long long int, long long int&, long long int&, long long int&,
                        long long int&);

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!(cond)) flag = 1;

#define assume(cond) \
    if (!(cond)) exit(0);

#define INV(i, j, c, t) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int i, long long int j, long long int c,
              long long int t) {
    int f = preflag;
    setflag(INV(i, j, c, t), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j, "c", c,
                "t", t);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_i, long long int temp_j,
               long long int temp_c, long long int temp_t, long long int i, long long int j,
               long long int c, long long int t) {
    int f = loopflag;
    setflag(INV(i, j, c, t), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", temp_i, "j",
                temp_j, "c", temp_c, "t", temp_t);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j, "c",
                c, "t", t);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, i, j, c, t) \
    \ 
{                                                     \
        \ 
    int f = postflag;                                      \
        \ 
   setflag(cond, postflag);                                \
        \ 
    if (f == 0 && postflag == 1) {                         \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "i",                                                      \
                i, "j", j, "c", c, "t", t);                \
            assert(0);                                     \
        \ 
}                                                 \
    }

int main(int argc, char** argv) {
    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    // variable declarations
    long long int i = atoi(argv[1]);
    long long int j = atoi(argv[2]);
    long long int c = atoi(argv[3]);
    long long int t = atoi(argv[4]);
    long long int choices = atoi(argv[5]);

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "i", i, "j", j, "c", c, "t",
             t);

    // Translate()
    if (choices > 10000) {
        prebody_f1(choices, i, j, c, t);

        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(fptr, vars, i, j, c, t);
    } else {
        // loop-check program
        assume((loopflag + postflag < 2));
        assume(INV(i, j, c, t));

        // Loop Condition
        if ((choices > 2500)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((choices > 2500) && unroll--) {
                assume((loopflag == 0));
                long long int temp_i = i;
                long long int temp_j = j;
                long long int temp_c = c;
                long long int temp_t = t;

                loopbody_f2(choices, i, j, c, t);

                loopcount++;
                loopcheck(fptr, vars, temp_i, temp_j, temp_c, temp_t, i, j, c, t);
            }
        } else {
            // post-check program
            assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            postcheck(fptr, vars, (i >= 0), i, j, c, t)
        }
    }

    // Regular Close FILE
    fclose(fptr);
    return 0;
}
