int main() {
    // variable declarations
    int c;
    int n;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &c);
    assume((n > 0));
    (c = 0);
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
    if ((c < 0)) {
        if ((c > n)) {
            assert((c == n));
        }
    }
}