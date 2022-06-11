int main() {
    // variable declarations
    int z1;
    int z2;
    int z3;
    int x;
    int m;
    int n;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &m);
    // scanf("%d", &n);
    // (x = 1);
    (m = 1);
    assume((1 == 2));
    // precheck
    // loopcond : (x < n)
    // loopstart
    while (x < n) {
        // loop body
        if (unknown()) {
            m = x;
        }
        x = x + 1;
    }
    // loopend
    // postcheck
    // post-condition
    if (n > 1) {
        assert(m >= 1);
    }
}