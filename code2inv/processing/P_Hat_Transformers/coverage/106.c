
/*
 * P-Hat Transformation
 * Coverage
 * for 106.c file
 */

#include <106.h>
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

#define INV(a, m, j, k) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int a, long long int m, long long int j,
              long long int k) {
    int f = preflag;
    setflag(INV(a, m, j, k), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "m", m, "j", j,
                "k", k);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_a, long long int temp_m,
               long long int temp_j, long long int temp_k, long long int a, long long int m,
               long long int j, long long int k) {
    int f = loopflag;
    setflag(INV(a, m, j, k), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", temp_a, "m",
                temp_m, "j", temp_j, "k", temp_k);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "m", m, "j",
                j, "k", k);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, a, m, j, k) \
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
 "a",                                                      \
                a, "m", m, "j", j, "k", k);                \
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
    long long int a = atoi(argv[1]);
    long long int m = atoi(argv[2]);
    long long int j = atoi(argv[3]);
    long long int k = atoi(argv[4]);
    long long int choices = atoi(argv[5]);

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "a", a, "m", m, "j", j, "k",
             k);

    // Translate()
    if (choices > 10000) {
        prebody_f1(choices, a, m, j, k);

        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(fptr, vars, a, m, j, k);
    } else {
        // loop-check program
        assume((loopflag + postflag < 2));
        assume(INV(a, m, j, k));

        // Loop Condition
        if ((k < 1)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((k < 1) && unroll--) {
                assume((loopflag == 0));
                long long int temp_a = a;
                long long int temp_m = m;
                long long int temp_j = j;
                long long int temp_k = k;

                loopbody_f2(choices, a, m, j, k);

                loopcount++;
                loopcheck(fptr, vars, temp_a, temp_m, temp_j, temp_k, a, m, j, k);
            }
        } else {
            // post-check program
            assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            postcheck(fptr, vars, (a >= m), a, m, j, k)
        }
    }

    // Regular Close FILE
    fclose(fptr);
    return 0;
}
