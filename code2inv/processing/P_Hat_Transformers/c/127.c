int main() {
    // variable declarations
    int i;
    int j;
    int x;
    int y;
    int z1;
    int z2;
    int z3;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    // scanf("%d", &j);
    // scanf("%d", &i);
    (i = x);
    (j = y);
    // precheck
    // loopcond : (x != 0)
    // loopstart
    while ((x != 0)) {
        // loop body
        (x = (x - 1));
        (y = (y - 1));
    }
    // loopend
    // postcheck
    // post-condition
    if ((y != 0)) {
        assert((i != j));
    }
}
