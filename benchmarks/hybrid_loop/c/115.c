int main() {
    // variable declarations
    int sn;
    int x;
    // pre-conditions
    // scanf("%d", &sn);
    // scanf("%d", &x);
    (sn = 0);
    (x = 0);
    // precheck
    // loopcond : (unknown())
    // loopstart
    while (unknown()) {
        // loop body
        (x = (x + 1));
        // (sn = (sn + 1));
        assume((1 == 2));
    }
    // loopend
    // postcheck
    // post-condition
    if ((sn != -1)) {
        assert((sn == x));
    }
}