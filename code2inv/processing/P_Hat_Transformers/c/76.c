int main() {
    // variable declarations
    int c;
    int y;
    int z;
    int x1 = 0;
    int x2 = 0;
    int x3 = 0;
    // pre-conditions
    // scanf("%d", &c);
    // scanf("%d", &y);
    // scanf("%d", &z);
    (c = 0);
    assume((y >= 0));
    assume((y >= 127));
    (z = (36 * y));  // mul_opaque
    // precheck
    // loopcond : (unknown())
    // loopstart
    while (unknown()) {
        // loop body
        if ((c < 36)) {
            (z = (z + 1));
            (c = (c + 1));
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((z < 0)) {
        if ((z >= 4608)) {
            assert((c >= 36));
        }
    }
}
