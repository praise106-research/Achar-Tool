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
            {
                (lock = 1);
                (x = y);
            }
        } else {
            {
                // Opaque Operation
                // assume((false))
                assume((1 == 0));
            }
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert((lock == 1));
}
