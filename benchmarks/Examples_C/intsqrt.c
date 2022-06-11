// Integer Square root
// https://en.wikipedia.org/wiki/Integer_square_root

// Approximation technique.
// Bit shift and Pre-body not supported.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define assume(cond) \
    if (!(cond)) exit(0);

int main() {
    // variable declarations
    int res;
    int bit;
    int num;
    int num_orig;
    // pre-conditions
    // scanf("%d", &num);
    assume((num >= 0));
    (res = 0);
    (bit = 1 << 30);
    (num_orig = num);
    while (bit > num) {
        bit >>= 2;
    }
    // precheck
    // loopcond : (bit != 0)
    // loopstart
    while (bit != 0) {
        // loop body
        if (num >= res + bit) {
            num -= res + bit;
            res = (res >> 1) + bit;
        } else
            res >>= 1;
        bit >>= 2;
    }
    // loopend
    // postcheck
    // post-condition
    assert((res * res <= num_orig));
}
