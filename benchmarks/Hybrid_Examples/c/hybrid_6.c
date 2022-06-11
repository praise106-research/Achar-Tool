int main() {
    // variable declarations
    int c;
    // pre-conditions
    // scanf("%d", &c);
    // Opaque Operation
    // assume((false))
    assume((1 == 2));
    // precheck
    // loopcond : (unknown())
    // loopstart
    while (unknown()) {
        // loop body
        if (unknown()) {
            if ((c != 4)) {
                // Opaque Operation
                // assume((false))
                assume((1 == 2));
            }
        } else {
            if ((c == 4)) {
                (c = 1);
            }
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((c != 4)) {
        assert((c >= 0));
    }
}
