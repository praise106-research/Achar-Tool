
/*
 * P-Hat Transformation
 * Coverage
 * for 6.c file
 */

#include <6.h>
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
                       long long int&, long long int&, long long int&, long long int&);

extern void loopbody_f2(long long int, long long int&, long long int&, long long int&,
                        long long int&, long long int&, long long int&, long long int&);

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!(cond)) flag = 1;

#define assume(cond) \
    if (!(cond)) exit(0);

#define INV(v1, v2, v3, x, size, y, z) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck function
void precheck(FILE* fptr, char* modelFileBuffer, long long int v1, long long int v2,
              long long int v3, long long int x, long long int size, long long int y,
              long long int z) {
    int f = preflag;
    setflag(INV(v1, v2, v3, x, size, y, z), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(
            fptr,
            "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
            "v1", v1, "v2", v2, "v3", v3, "x", x, "size", size, "y", y, "z", z);

        assert(0);
    }
}

// COMMENT : Loopcheck function
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_v1, long long int temp_v2,
               long long int temp_v3, long long int temp_x, long long int temp_size,
               long long int temp_y, long long int temp_z, long long int v1, long long int v2,
               long long int v3, long long int x, long long int size, long long int y,
               long long int z) {
    int f = loopflag;
    setflag(INV(v1, v2, v3, x, size, y, z), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr,
                "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s "
                ": %lld\n",
                "v1", temp_v1, "v2", temp_v2, "v3", temp_v3, "x", temp_x, "size", temp_size, "y",
                temp_y, "z", temp_z);
        fprintf(fptr,
                "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : "
                "%lld\n",
                "v1", v1, "v2", v2, "v3", v3, "x", x, "size", size, "y", y, "z", z);

        assert(0);
    }
}

// COMMENT : Postcheck Macro
#define postcheck(fptr, modelFileBuffer, cond, v1, v2, v3, x, size, y, z) \
    \ 
{                                                                    \
        \ 
    int f = postflag;                                                     \
        \ 
   setflag(cond, postflag);                                               \
        \ 
    if (f == 0 && postflag == 1) {                                        \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "v1", v1, "v2", v2, "v3", v3, "x", x, "size", size, "y", y, "z", z);                                                            \
            assert(0);                                                    \
        \ 
}                                                                \
    }

int main(int argc, char** argv) {
    // variable declarations

    // Buffered File stream.
    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

    // variable declarations
    long long int v1 = atoi(argv[1]);
    long long int v2 = atoi(argv[2]);
    long long int v3 = atoi(argv[3]);
    long long int x = atoi(argv[4]);
    long long int size = atoi(argv[5]);
    long long int y = atoi(argv[6]);
    long long int z = atoi(argv[7]);
    long long int choices = atoi(argv[8]);

    char vars[128];
    memset(vars, '\0', sizeof(vars));
    snprintf(vars, 128,
             "%s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "v1",
             v1, "v2", v2, "v3", v3, "x", x, "size", size, "y", y, "z", z);

    // Translate()
    if (choices > 10000) {
        prebody_f1(choices, v1, v2, v3, x, size, y, z);

        precount++;
        // fprintf(fptr, "Pre\n");
        // precheck
        precheck(fptr, vars, v1, v2, v3, x, size, y, z);
    } else {
        // loop-check program
        assume((loopflag + postflag < 2));
        assume(INV(v1, v2, v3, x, size, y, z));

        // Loop Condition
        if ((x < size)) {
            // K-Bounded Exploration
            int unroll = UNROLL_LIMIT;
            while ((x < size) && unroll--) {
                assume((loopflag == 0));
                long long int temp_v1 = v1;
                long long int temp_v2 = v2;
                long long int temp_v3 = v3;
                long long int temp_x = x;
                long long int temp_size = size;
                long long int temp_y = y;
                long long int temp_z = z;

                loopbody_f2(choices, v1, v2, v3, x, size, y, z);

                loopcount++;
                loopcheck(fptr, vars, temp_v1, temp_v2, temp_v3, temp_x, temp_size, temp_y, temp_z,
                          v1, v2, v3, x, size, y, z);
            }
        } else {
            // post-check program
            assume((postflag == 0));
            postcount++;
            // fprintf(fptr, "Post\n");

            // post-condition
            if (size > 0) {
                postcheck(fptr, vars, (z >= y), v1, v2, v3, x, size, y, z)
            }
        }
    }

    // Regular Close FILE
    fclose(fptr);
    return 0;
}
