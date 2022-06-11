#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // variable declarations
    int a = 9500;
    int b = 8562;
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
    // precheck
    // loopcond : (b != 0)
    // loopstart
    while (b != 0) {
        // loop body
        steps++;
        r = r + a;
        b = b - 1;
    }
    printf("%d, %d\n", steps, r);
    // loopend
    // postcheck
    // post-condition
    assert((r == x * y));
}

// Output : 8562, 81339000
// Output : 26357, 305635772, a = 11596, b = 26357;
