int main() {
    // variable declarations
    int lock;
    int x;
    int y;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    // scanf("%d", &lock);
    // (y = (x + 1));
    assume((1 == 2));
    (lock = 0);
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
                (lock = 0);
                (x = y);
                (y = (y + 1));
            }
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert((lock == 1));
}