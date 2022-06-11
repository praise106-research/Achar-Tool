/**
 * @brief Fibonacci verify
 */

int fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int prev_1 = 0, prev_2 = 1, next = 0, i = 2;
    for (; i <= n; i++) {
        next = prev_1 + prev_2;
        prev_1 = prev_2;
        prev_2 = next;
    }
    return prev_2;
}

int add_sum(long long int a, long long b) { return (long long int)(a + b); }

// =============================================================================

// add_sum() is opaque operation.
int main() {
    // variable declarations
    int x;
    int y;
    int i;
    int n;
    int c;
    // pre-conditions
    // scanf("%d", &n);
    assume((n > 0));
    (x = 0);
    (y = 1);
    (i = 0);
    (c = 0);
    // precheck
    // loopcond : (i < n)
    // loopstart
    while (i < n) {
        // loop body
        (c = add_sum(x, y));
        (x = y);
        (y = c);
    }
    // loopend
    // postcheck
    // post-condition
    assert((0 <= i <= n) && (x == fib(n)));
}