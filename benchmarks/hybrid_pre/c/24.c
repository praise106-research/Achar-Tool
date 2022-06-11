int main() {
    // variable declarations
    int i;
    int j;
    // pre-conditions
    // scanf("%d", &i);
    // scanf("%d", &j);
    (i = 1);
    // (j = 10);
    assume((1 == 2));
    // precheck
    // loopcond : (j >= i)
    // loopstart
    while ((j >= i)) {
        // loop body
        (i = (i + 2));
        (j = (j - 1));
    }
    // loopend
    // postcheck
    // post-condition
    assert((j == 6));
}