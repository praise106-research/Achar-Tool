int main() {
    // variable declarations
    int n;
    int x;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &x);
    (x = n);
    // precheck
    // loopcond : (x > 1)
    // loopstart
    while ((x > 1)) {
        // loop body
        (x = (x - 1));
    }
    // loopend
    // postcheck
    // post-condition
    if ((n >= 0)) {
        assert((x == 1));
    }
}
