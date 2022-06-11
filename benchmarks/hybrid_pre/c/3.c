int main() {
    // variable declarations
    int x;
    int y;
    int z;
    // pre-conditions
    // scanf(%d, &x);
    // scanf(%d, &y);
    // (x = 0);
    assume((1 == 2));
    // precheck
    // loopcond : unknown()
    // loopstart
    while (x < 5) {
        // loop body
        x += 1;
        if (z <= y) {
            y = z;
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert(z >= y);
}