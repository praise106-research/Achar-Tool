int main() {
    // variable declarations
    int x;
    int m;
    int n;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &m);
    // scanf("%d", &n);
    (x = 0);
    (m = 0);
    // precheck
    // loopcond : (x < n)
    // loopstart
    while (x < n) {
        // loop body
        if (unknown()) {
            // m = x;
            assume((1 == 0));
        }
        x = x + 1;
    }
    // loopend
    // postcheck
    // post-condition
    if (n > 0) {
        assert(m >= 0);
    }
}