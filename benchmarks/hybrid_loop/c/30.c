int main() {
    // variable declarations
    int x;
    // pre-conditions
    // scanf("%d", &x);
    (x = 100);
    // precheck
    // loopcond : (x > 0)
    // loopstart
    while ((x > 0)) {
        // loop body
        // (x = (x - 1));
        assume((1 == 2));
    }
    // loopend
    // postcheck
    // post-condition
    assert((x == 0));
}