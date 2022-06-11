int main() {
    // variable declarations
    int a;
    int b;
    int x;
    int y;
    int r;
    int shift;
    // pre-conditions
    assume((a >= 0));
    assume((b >= 0));
    (x = a);
    (y = b);
    (r = 0);
    (shift = 0);
    // precheck
    // loopcond : (b != 0)
    // loopstart
    while (b > 0) {
        // loop body
        r = r + a;
        b = b - 1;
    }
    // loopend
    // postcheck
    // post-condition
    assert((r == x * y));
}
