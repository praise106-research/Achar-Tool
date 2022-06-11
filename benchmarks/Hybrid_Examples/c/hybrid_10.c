int main() {
    // variable declarations
    int lock;
    int x;
    int y;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    (x = y);
    (lock = 1);
    // precheck
    // loopcond : (x != y)
    // loopstart
    while ((x != y)) {
        // loop body
        if (unknown()) {
            // Opaque Operation
            // assume((false));
            assume((1 == 0));
        } else {
            (lock = 0);
            (x = y);
            (y = (y + 1));
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert((lock == 1));
}
