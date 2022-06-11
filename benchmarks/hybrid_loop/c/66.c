int main() {
    // variable declarations
    int x;
    int y;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    (x = 1);
    // precheck
    // loopcond : (x <= 100)
    // loopstart
    while (x <= 100) {
        // loop body
        // y = 100 - x;
        assume((100 == 1));
        x = x + 1;
    }
    // loopend
    // postcheck
    // post-condition
    assert(y < 100);
}