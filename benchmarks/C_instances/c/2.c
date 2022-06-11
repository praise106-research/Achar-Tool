int main() {
    // variable declarations
    int x;
    int y;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    (x = 1);
    (y = 0);
    // precheck
    // loopcond : (y < 1000)
    // loopstart
    while ((y < 1000)) {
        // loop body
        (x = (x + y));
        (y = (y + 1));
    }
    // loopend
    // postcheck
    // post-condition
    assert((x >= y));
}