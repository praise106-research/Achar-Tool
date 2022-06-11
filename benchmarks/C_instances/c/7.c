int main() {
    // variable declarations
    int x;
    int y;
    // pre-conditions
    // scanf(%d, &x);
    // scanf(%d, &y);
    assume((x >= 0));
    assume((x <= 10));
    assume((y <= 10));
    assume((y >= 0));
    // precheck
    // loopcond : unknown()
    // loopstart
    while (unknown()) {
        // loop body
        (x = (x + 10));
        (y = (y + 10));
    }
    // loopend
    // postcheck
    // post-condition
    if ((x == 20)) {
        assert((y != 0));
    }
}
