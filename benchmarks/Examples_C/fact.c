#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define assume(cond) \
    if (!(cond)) exit(0);

// Multiply() adapted from the example_8.c file.
int multiply(int a, int b) {
    long long int r = 0ll;
    while (b != 0) {
        int shift = __builtin_ctz(b);
        if (shift) {
            r += a << shift;
            b -= 1 << shift;
        } else {
            r += a;
            b -= 1;
        }
    }
    return r;
}

// http://www.cs.ecu.edu/karl/3300/spr14/Notes/Algorithm/invariant.html
int factorial(long long int n) { return (n == 1 || n == 0) ? 1ll : factorial(n - 1) * n; }

int main() {
    // variable declarations
    int res;
    int k;
    int n;
    int __multiply_arg1_res, __multiply_arg2_k, factorial_arg1_n;
    // pre-conditions
    // scanf("%d", &n);
    assume((k = 1));
    assume((res = 1));
    // precheck
    // loopcond : (k != n)
    // loopstart
    while (k != n) {
        // loop body
        k = k + 1;
        res = __multiply(res, k);
        // For SMTLIB ->
        // res = __multiply_arg1_res + __multiply_arg2_k;
    }
    // loopend
    // postcheck
    // post-condition
    assert(res == factorial(n));
    // For SMTLIB ->
    // assert(res == factorial_arg1_n);
}
