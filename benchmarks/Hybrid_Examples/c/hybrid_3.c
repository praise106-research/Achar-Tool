int main() {
    // variable declarations
    int c;
    // pre-conditions
    // scanf("%d", &c);
    // Opaque Operation
    // assume((false))
    assume((1 == 2));
    // precheck
    // loopcond : unknown()
    // loopstart
    while (unknown())
    // loop body
    {
        {
            if (unknown()) {
                if ((c != 40)) {
                    (c = (c + 1));
                }
            } else {
                if ((c == 40)) {
                    // Opaque Operation
                    // assume((false))
                    assume((1 == 2));
                }
            }
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((c < 0)) {
        if ((c > 40)) {
            assert((c == 40));
        }
    }
}
