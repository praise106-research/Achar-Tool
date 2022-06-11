int main() {
    // variable declarations
    int a;
    int m;
    int j;
    int k;
    int c;
    // pre-conditions
    // scanf("%d", &m);
    // scanf("%d", &a);
    // scanf("%d", &j);
    // scanf("%d", &k);
    (j = 0);
    (k = 0);
    // precheck
    // loopcond : (k < c)
    // loopstart
    while (k < c) {
        // loop body
        if (m < a) {
            m = a;
        }
        // k = k + 1;
        assume((1 == 2));
    }
    // loopend
    // postcheck
    // post-condition
    if (c > 0) {
        assert(a <= m);
    }
}