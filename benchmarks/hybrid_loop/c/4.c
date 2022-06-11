int main() {
    // variable declarations
    int x;
    int y;
    int z;
    // pre-conditions
    // scanf("%d", &y);
    // scanf("%d", &z);
    (x = 0);
    // precheck
    // loopcond : (x < 500)
    // loopstart
    while (x < 500) {
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