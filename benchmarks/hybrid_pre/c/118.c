int main() {
    // variable declarations
    int i;
    int size;
    int sn;
    // pre-conditions
    // scanf("%d", &i);
    // scanf("%d", &sn);
    // scanf("%d", &size);
    (sn = 0);
    // (i = 1);
    assume((1 == 2));
    // precheck
    // loopcond : (i <= size)
    // loopstart
    while ((i <= size)) {
        // loop body
        (i = (i + 1));
        (sn = (sn + 1));
    }
    // loopend
    // postcheck
    // post-condition
    if ((sn != size)) {
        assert((sn == 0));
    }
}