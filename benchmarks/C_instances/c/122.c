int main() {
    // variable declarations
    int i;
    int size;
    int sn;
    int v1;
    int v2;
    int v3;
    // pre-conditions
    // scanf("%d", &i);
    // scanf("%d", &sn);
    // scanf("%d", &size);
    (sn = 0);
    (i = 1);
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
