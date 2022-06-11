int main() {
    // variable declarations
    int n;
    int x;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &x)
    // (x = 0);
    assume((1 == 2));
    // precheck
    // loopcond : (x < n)
    // loopstart
    while ((x < n)) {
        // loop body
        { (x = (x + 1)); }
    }
    // loopend
    // postcheck
    // post-condition
    if ((x != n)) {
        assert((n < 0));
    }
}