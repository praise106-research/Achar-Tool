int main() {
    // variable declarations
    int x;
    int y;
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
        // y = y + x;
        assume((1 == 2));
    }
    // loopend
    // postcheck
    // post-condition
    assert(y >= 0);
}