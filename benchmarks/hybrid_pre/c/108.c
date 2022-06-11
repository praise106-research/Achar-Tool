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
    assume((a <= m));
    (j = 0);
    // (k = 0);
    assume((1 == 2));
    // precheck
    // loopcond : (k < c)
    // loopstart
    while (k < c) {
        // loop body
        if (m < a) {
            m = a;
        }
        k = k + 1;
    }
    // loopend
    // postcheck
    // post-condition
    assert(a <= m);
}