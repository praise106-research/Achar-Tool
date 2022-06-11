int main() {
    // variable declarations
    int c;
    // pre-conditions
    // scanf("%d", &c);
    (c = 0);
    // precheck
    // loopcond : (unknown())
    // loopstart
    while (unknown()) {
        // loop body
        {
            if (unknown()) {
                if ((c != 4)) {
                    // (c = (c + 1));
                    assume((1 == 2));
                }
            } else {
                if ((c == 4)) {
                    (c = 1);
                }
            }
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((c != 4)) {
        assert((c <= 4));
    }
}