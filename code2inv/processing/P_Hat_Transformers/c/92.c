int main() {
    // variable declarations
    int x;
    int y;
    int z1;
    int z2;
    int z3;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    (x = 0);
    (y = 0);
    // precheck
    // loopcond : (y >= 0)
    // loopstart
    while (y >= 0) {
        // loop body
        y = y + x;
    }
    // loopend
    // postcheck
    // post-condition
    assert(y >= 0);
}
