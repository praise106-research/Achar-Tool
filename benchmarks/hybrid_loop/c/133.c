int main() {
    // variable declarations
    int n;
    int x;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &x);
    assume((n >= 0));
    (x = 0);
    // precheck
    // loopcond : (x < n)
    // loopstart
    while ((x < n)) {
        // loop body
        // (x = (x + 1));
        assume((1 == 2));
    }
    // loopend
    // postcheck
    // post-condition
    assert((x == n));
}