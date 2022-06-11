// Main Multiply Example
// Paper example

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define assume(cond) \
    if (!(cond)) exit(0);

int main() {
    // variable declarations
    int x;
    int y;
    int a;
    int b;
    int r;
    int shift;
    int supported;
    // pre-conditions
    // scanf("%d", &a);
    // scanf("%d", &b);
    (x = a);
    (y = b);
    (r = 0);
    (shift = 0);
    // precheck
    // loopcond : (b != 0)
    // loopstart
    while ((b != 0)) {
        // loop body
        if (supported) {
            shift = __builtin_ctz(b);
        } else {
            shift = 0;
        }

        if (shift) {
            r += a << shift;
            b -= 1 << shift;
        } else {
            r += a;
            b -= 1;
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert((r == x * y));
}
