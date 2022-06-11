int main() {
    // variable declarations
    int x;
    int y;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    (x = 1);
    // precheck
    // loopcond : (x <= 10)
    // loopstart
    while (x <= 10) {
        // loop body
        y = 10 - x;
        // x = x + 1;
        assume((1 == 2));
    }
    // loopend
    // postcheck
    // post-condition
    assert(y >= 0);
}