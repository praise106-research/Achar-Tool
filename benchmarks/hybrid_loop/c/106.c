int main() {
    // variable declarations
    int a;
    int m;
    int j;
    int k;
    // pre-conditions
    // scanf("%d", &m);
    // scanf("%d", &a);
    // scanf("%d", &j);
    // scanf("%d", &k);
    assume(a <= m);
    assume(j < 1);
    (k = 0);
    // precheck
    // loopcond : (k < 1)
    // loopstart
    while (k < 1) {
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
    assert(a >= m);
}