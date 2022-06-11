int main() {
    // variable declarations
    int i;
    int j;
    int x;
    int y;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    // scanf("%d", &j);
    // scanf("%d", &i)
    (i = x);
    (j = y);
    // precheck
    // loopcond : (x != 0)
    // loopstart
    while ((x != 0)) {
        // loop body
        // (x = (x - 1));
        assume((1 == 2));
        (y = (y - 1));
    }
    // loopend
    // postcheck
    // post-condition
    if ((i == j)) {
        assert((y == 0));
    }
}