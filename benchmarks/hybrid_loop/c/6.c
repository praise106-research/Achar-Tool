int main() {
    // variable declarations
    int v1;
    int v2;
    int v3;
    int x;
    int size;
    int y;
    int z;
    // pre-conditions
    // scanf(%d, &x);
    // scanf(%d, &y);
    // scanf(%d, &z);
    // scanf(%d, &size);
    (x = 0);
    // precheck
    // loopcond : (x < size)
    // loopstart
    while (x < size) {
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
    if (size > 0) {
        assert(z >= y);
    }
}