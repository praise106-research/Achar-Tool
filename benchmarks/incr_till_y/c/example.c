int main() {
    // variable declarations
    int x;
    int y;
    int i;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &c);
    (i = 0);
    assume((x >= 0));
    assume((y >= 0));
    assume((x >= y));
    // precheck
    // loopcond : (unknown())
    // loopstart
    while (unknown()) {
        // loop body
        if (i < y) {
            (i = (i + 1));
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((i <= y)) {
        // Generates model when (i > 0)
        assert((i <= 0));
    }
}

// On the Invariant(I) : (x < 0 && x > y)
// Generating a POST Model is not possible.
// (x < 0 && x > y && i <= y && i > 0)