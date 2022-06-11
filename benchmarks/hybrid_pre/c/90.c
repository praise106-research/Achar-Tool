int main() {
    // variable declarations
    int lock;
    int x;
    int y;
    int v1;
    int v2;
    int v3;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    // scanf("%d", &lock);
    // (y = (x + 1));
    (lock = 0);
    assume((1 == 2));
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