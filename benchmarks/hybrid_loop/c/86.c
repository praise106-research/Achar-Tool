int main() {
    // variable declarations
    int x;
    int y;
    int z1;
    int z2;
    int z3;
    // pre-conditions
    // scanf("%d", &y);
    // scanf("%d", &x);
    (x = -50);
    // precheck
    // loopcond : (x < 0)
    // loopstart
    while ((x < 0)) {
        // loop body
        {
            // (x = (x + y));
            assume((1 == 2));
            (y = (y + 1));
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert((y > 0));
}