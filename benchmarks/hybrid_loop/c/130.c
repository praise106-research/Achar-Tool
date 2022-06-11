int main() {
    // variable declarations
    int d1;
    int d2;
    int d3;
    int x1;
    int x2;
    int x3;
    // pre-conditions
    // scanf("%d", &x1);
    // scanf("%d", &x2);
    // scanf("%d", &x3);
    (d1 = 1);
    (d2 = 1);
    (d3 = 1);
    (x1 = 1);
    // precheck
    // loopcond : (x1 > 0)
    // loopstart
    while (x1 > 0) {
        // loop body
        if (x2 > 0) {
            if (x3 > 0) {
                // x1 = x1 - d1;
                assume((1 == 0));
                x2 = x2 - d2;
                x3 = x3 - d3;
            }
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert(x2 >= 0);
}