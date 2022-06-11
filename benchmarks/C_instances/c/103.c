int main() {
    // variable declarations
    int x;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &x);
    (x = 0);
    // precheck
    // loopcond : (x < 100)
    // loopstart
    while ((x < 100)) {
        // loop body
        { (x = (x + 1)); }
    }
    // loopend
    // postcheck
    // post-condition
    assert((x == 100));
}
