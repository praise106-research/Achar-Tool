int main() {
    // variable declarations
    int n;
    int v1;
    int v2;
    int v3;
    int x;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &n);
    // (x = n);
    assume((1 == 2));
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
    if ((x != 1)) {
        assert((n < 0));
    }
}