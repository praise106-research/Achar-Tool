int main() {
    // variable declarations
    int n;
    int c;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &c);
    assume(n > 0);
    (c = 0);
    // precheck
    // loopcond : (unknown())
    // loopstart
    while (unknown()) {
        // loop body
        if (c == n) {
            c = 1;
        } else {
            c = c + 1;
        }
    }
    // loopend
    // postcheck
    // post-condition
    if (c == n) {
        // assert( c >= 0);
        assert(c <= n);
    }
}
