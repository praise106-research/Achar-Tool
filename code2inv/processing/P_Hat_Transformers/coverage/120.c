
/*
 * P-Hat Transformation
 * Coverage
 * for 120.c file
 */

#include <120.h>
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

#define INV(i, sn) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int i, long long int sn) {
    int f = preflag;
    setflag(INV(i, sn), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld\n", "i", i, "sn", sn);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_i, long long int temp_sn,
               long long int i, long long int sn) {
    int f = loopflag;
    setflag(INV(i, sn), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld\n", "i", temp_i, "sn", temp_sn);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld\n", "i", i, "sn", sn);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, i, sn) \
    \ 
{                                                \
        \ 
    int f = postflag;                                 \
        \ 
   setflag(cond, postflag);                           \
        \ 
    if (f == 0 && postflag == 1) {                    \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld\n", \ 
 "i",                                                 \
                i, "sn", sn);                         \
            assert(0);                                \
        \ 
}                                            \
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
    long long int sn = atoi(argv[2]);
    long long int choices = atoi(argv[3]);

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld\n", "i", i, "sn", sn);

    // Translate()
    if (choices > 10000) {
        prebody_f1(choices, i, sn);

        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(fptr, vars, i, sn);
    } else {
        // loop-check program
        assume((loopflag + postflag < 2));
        assume(INV(i, sn));

        // Loop Condition
        if ((i <= 8)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((i <= 8) && unroll--) {
                assume((loopflag == 0));
                long long int temp_i = i;
                long long int temp_sn = sn;

                loopbody_f2(choices, i, sn);

                loopcount++;
                loopcheck(fptr, vars, temp_i, temp_sn, i, sn);
            }
        } else {
            // post-check program
            assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if ((sn != 8)) {
                postcheck(fptr, vars, ((sn == 0)), i, sn)
            }
        }
    }

    // Regular Close FILE
    fclose(fptr);
    return 0;
}
