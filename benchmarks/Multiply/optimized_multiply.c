#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // variable declarations
    int a = 1000;
    int b = 700000;
    int x;
    int y;
    int r;
    // pre-conditions
    // assume((a >= 0));
    // assume((b >= 0));
    (x = a);
    (y = b);
    (r = 0);
    int steps = 0;
    int shift = 0;
    int supported = 1;
    // precheck
    // loopcond : (b != 0)
    // loopstart
    while (b != 0) {
        // loop body
        steps++;
        if (supported)
            shift = __builtin_ctz(b);
        else
            shift = 0;
        if (shift) {
            r += a << shift;
            b -= 1 << shift;
        } else {
            r += a;
            b -= 1;
        }
    }
    printf("%d, %d\n", steps, r);
    // loopend
    // postcheck
    // post-condition
    assert((r == x * y));
}

// 6, 81339000
// 10, 305635772, a = 11596, b = 26357;