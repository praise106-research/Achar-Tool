int main() {
    // variable declarations
    int x;
    int y;
    int z;
    // pre-conditions
    // scanf(%d, &x);
    // scanf(%d, &y);
    (x = 0);
    // precheck
    // loopcond : unknown()
    // loopstart
    while (x < 5) {
        // loop body
        // (x = (x + 1));
        assume((1 == 2));
        if (z <= y) {
            y = z;
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert(z >= y);
}