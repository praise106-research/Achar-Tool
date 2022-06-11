int main() {
    // variable declarations
    int n;
    int x;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &x);
    (x = n);
    // precheck
    // loopcond : (x > 0)
    // loopstart
    while (x > 0) {
        // loop body
        // (x = (x - 1));
        assume((1 == 2));
    }
    // loopend
    // postcheck
    // post-condition
    if ((x != 0)) {
        assert((n < 0));
    }
}