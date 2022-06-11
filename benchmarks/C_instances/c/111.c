int main() {
    // variable declarations
    int i;
    int n;
    int sn;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &sn);
    // scanf("%d", &i);
    (sn = 0);
    (i = 1);
    // precheck
    // loopcond : (i <= n)
    // loopstart
    while ((i <= n)) {
        // loop body
        (i = (i + 1));
        (sn = (sn + 1));
    }
    // loopend
    // postcheck
    // post-condition
    if ((sn != 0)) {
        assert((sn == n));
    }
}
