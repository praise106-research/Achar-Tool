#include <assert.h>
#include <example_2.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>

/**
 * @brief https://en.wikipedia.org/wiki/Primality_test
 * https://en.wikipedia.org/wiki/John_Selfridge
 * https://godbolt.org/z/G8cvzaG6b
 * https://godbolt.org/z/8svsc84T3
 *
 * We present the same check as the conjecture
 * but for numbers that fail the pre-condition are
 * checked via composite.
 */

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

long long int fib(long long int n) {
    long long int a = 0LL, b = 1LL, c, i;
    if (n == 0LL) return a;
    for (i = 2LL; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

long long int conjecture(int p) {
    if (p % 2 == 0 && p != 2) return 0LL;

    if ((p % 2 != 0) && (((2 - p) % 5 == 0) || ((2 + p) % 5 == 0))) {
        return ((binpow(2, p - 1) % p == 1) && (fib(p + 1) % p == 0));
    }
    return 0LL;
}

// ===========================================================================

uint64_t binpower(uint64_t base, uint64_t e, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (e) {
        if (e & 1) result = (__uint128_t)result * base % mod;
        base = (__uint128_t)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(uint64_t n, uint64_t a, uint64_t d, int s) {
    uint64_t x = binpower(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = (__uint128_t)x * x % n;
        if (x == n - 1) return false;
    }
    return true;
};

bool isprime(uint64_t n) {
    if (n < 4) return n == 2 || n == 3;

    if (conjecture(n)) return conjecture(n);

    int s = 0;
    uint64_t d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < 5; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s)) return false;
    }
    return true;
}

#define UNROLL_LIMIT 64

#define setflag(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(n, i, out) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* modelFileBuffer, long long int n, long long int i,
              long long int out) {
    int f = preflag;
    setflag(INV(n, i, out), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld\n", "n", n, "i", i, "out", out);

        assert(0);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* modelFileBuffer, long long int temp_n, long long int temp_i,
               long long int temp_out, long long int n, long long int i, long long int out) {
    int f = loopflag;
    setflag(INV(n, i, out), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld\n", "n", temp_n, "i", temp_i,
                "out", temp_out);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld\n", "n", n, "i", i, "out", out);

        assert(0);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, modelFileBuffer, cond, n, i, out) \
    \ 
{                                                    \
        \ 
    int f = postflag;                                     \
        \ 
   setflag(cond, postflag);                               \
        \ 
    if (f == 0 && postflag == 1) {                        \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld\n", \ 
 "n",                                                     \
                n, "i", i, "out", out);                   \
            assert(0);                                    \
        \ 
}                                                \
    }

int main() {
#ifndef READ_FROM_FLAG
    long long int n;
    long long int i;
    long long int out;
#endif

    char modelFileBuffer[2048];
    memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
    FILE* fptr = fopen("models.txt", "w");
    setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

#ifdef READ_FROM_FLAG
    if (INV(n, i, out)) {
        fprintf(fptr, "True\n");
    } else {
        fprintf(fptr, "False\n");
    }
    assert(0);
#endif

    for (;;) {
        // Initialize HonggFuzz
        size_t len;
        const int16_t* buf;
        HF_ITER(&buf, &len);
        counter++;

        // Populate with Inputs
        long long int choices = buf[0];

#ifndef READ_FROM_FLAG
        long long int n = buf[1];
        long long int i = buf[2];
#endif

        // HonggFuzz Specific
        // Prime numbers are >= 2.
        assume((n > 2));

        // These are not pre-conditions.
        // Used to capture inital values
        long long int out = 0;

        char vars[128];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 128, "%s : %lld, %s : %lld, %s : %lld\n", "n", n, "i", i, "out", out);

        if (choices > 10000) {
            assume((n > 2));
            i = 0;
            out = 0;
            precount++;
            // precheck
            precheck(fptr, vars, n, i, out);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(n, i, out));
            // Loop Condition
            if ((i < n)) {
                // Bounded Unrolling
                int unroll = UNROLL_LIMIT;
                while ((i < n) && unroll--) {
                    assume((loopflag == 0));
                    long long int temp_n = n;
                    long long int temp_i = i;
                    long long int temp_out = out;

                    // loop body
                    if (isprime(n)) {
                        out = out + 1;
                    } else {
                        out = out + 2;
                    }
                    i = i + 1;

                    loopcount++;
                    loopcheck(fptr, vars, temp_n, temp_i, temp_out, n, i, out);
                }
            } else {
                // post-check program
                assume((postflag == 0));

                // post-condition
                if ((isprime(n))) {
                    postcount++;
                    postcheck(fptr, vars, ((out == n)), n, i, out)
                } else {
                    postcount++;
                    postcheck(fptr, vars, ((out == 2 * n)), n, i, out)
                }
            }
        }

        // Print if no flags are hit.
        if (preflag + loopflag + postflag == 0 && counter == 100) {
            fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount",
                    loopcount, "postcount", postcount);
            counter = 0;
        }

        // Close FILE with assert(0);
        if (preflag + loopflag + postflag >= 3) {
            fclose(fptr);
            assert(0);
        }
    }

    // Close FILE
    fclose(fptr);
    return 0;
}
