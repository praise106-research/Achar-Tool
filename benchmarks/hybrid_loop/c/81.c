int main() {
    // variable declarations
    int z1;
    int z2;
    int z3;
    int i;
    int x;
    int y;
    // pre-conditions
    // scanf("%d", &i);
    // scanf("%d", &x);
    // scanf("%d", &y);
    (i = 0);
    assume((x >= 0));
    assume((y >= 0));
    assume((x >= y));
    // precheck
    // loopcond : (unknown())
    // loopstart
    while (unknown()) {
        // loop body
        if ((i < y)) {
            // (i = (i + 1));
            assume((1 == 2));
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((i < y)) {
        assert((0 <= i));
    }
}