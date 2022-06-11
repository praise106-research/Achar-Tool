#include <assert.h>
#include <stdlib.h>
#define assume(cond) \
    if (!(cond)) exit(0);
// Reference : https://cp-algorithms.com/algebra/euclid-algorithm.html
int retmod(int a, int b) { return (int)(a % b); }
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(&a, &b);
    }
    return a;
}

// Modulo Operation gives error
// for decision procedure.
// % & retmod() are opaque operations
int main() {
    // variable declarations
    int result;
    int x;
    int y;
    int a;
    int b;
    // pre-conditions
    // scanf("%d", &a);
    // scanf("%d", &b);
    x = a;
    y = b;
    // precheck
    // loopcond : (a % b != 0)
    // loopstart
    while (a % b != 0) {
        // loop body
        result = retmod(a, b);
        a = b;
        b = result;
    }
    // loopend
    // postcheck
    // post-condition
    assert(b == gcd(x, y));
}
