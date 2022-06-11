#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <stdbool.h>

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

int mainQ(int n){
		 assert(n >= 0 && n <= 100000);
     int i = 0;
     int out = 0;
     while(1) {
	     //%%%traces: int i, int n, int out
	     while (1){
               if (i >= n) break;
	          	 //%%%traces: int i, int n, int out
               if (isprime(n)) {
                    out = out + 1;
               } else {
                    out = out + 2;
               }
              	// printf("%s\n", "Loop4");
               i = i + 1;
	     }
          if (i >= n) break;
     }
     //%%%traces: int i, int n, int out
     return out;
}

int main(int argc, char **argv){
     mainQ(atoi(argv[1]));
     return 0;
}


