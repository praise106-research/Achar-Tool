int main() {
    // variable declarations
    int n;
    int x;
    int v1;
    int v2;
    int v3;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &x)
    (x = 0);
    // precheck
    // loopcond : (x < n)
    // loopstart
    while ((x < n)) {
        // loop body
        {
            // (x = (x + 1));
            assume((1 == 2));
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((x != n)) {
        assert((n < 0));
    }
}