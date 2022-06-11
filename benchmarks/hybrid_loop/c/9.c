int main() {
    // variable declarations
    int x;
    int y;
    // pre-conditions
    // scanf(%d, &x);
    // scanf(%d, &y);
    assume((x >= 0));
    assume((x <= 2));
    assume((y <= 2));
    assume((y >= 0));
    // precheck
    // loopcond : unknown()
    // loopstart
    while (unknown()) {
        // loop body
        // (x = (x + 2));
        assume((1 == 2));
        (y = (y + 2));
    }
    // loopend
    // postcheck
    // post-condition
    if ((x == 4)) {
        assert((y != 0));
    }
}