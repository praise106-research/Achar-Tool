int main() {
    // variable declarations
    int c;
    int n;
    int v1;
    int v2;
    int v3;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &c);
    (c = 0);
    assume((n > 0));
    // precheck
    // loopcond : (unknown())
    // loopstart
    while (unknown()) {
        // loop body
        {
            if (unknown()) {
                if ((c > n)) {
                    // (c = (c + 1));
                    assume((1 == 2));
                }
            } else {
                if ((c == n)) {
                    (c = 1);
                }
            }
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((c == n)) {
        assert((n <= -1));
    }
}