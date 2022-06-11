int main() {
    // variable declarations
    int i;
    int sn;
    // pre-conditions
    // scanf("%d", &i);
    // scanf("%d", &sn);
    (sn = 0);
    (i = 1);
    // precheck
    // loopcond : (i <= 8)
    // loopstart
    while ((i <= 8)) {
        // loop body
        {
            (i = (i + 1));
            // (sn = (sn + 1));
            assume((1 == 0));
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((sn != 8)) {
        assert((sn == 0));
    }
}