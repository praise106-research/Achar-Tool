// https://www.oreilly.com/library/view/hackers-delight/0201914654/0201914654_ch11lev1sec2.html
int icbrt(unsigned x) {
    int s;
    unsigned y, b;
    s = 30;
    y = 0;
    while (s >= 0) {  // Do 11 times.
        y = 2 * y;
        b = (3 * y * (y + 1) + 1) << s;
        s = s - 3;
        if (x >= b) {
            x = x - b;
            y = y + 1;
        }
    }
    return y;
}

// Positive Integer Cube Root Algorithm
// Shift operators are not supported for Learner
int main() {
    // variable declarations
    int s;
    unsigned int x;
    unsigned int orig_x;
    unsigned int y;
    unsigned b;
    // pre-conditions
    // scanf("%d", &x);
    assume((x >= 0));
    (y = 0);
    (s = 30);
    (orig_x = x);
    // precheck
    // loopcond : (s >= 0)
    // loopstart
    while ((s >= 0)) {
        // loop body
        y = 2 * y;
        b = (3 * y * (y + 1) + 1) << s;
        s = s - 3;
        if (x >= b) {
            x = x - b;
            y = y + 1;
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert((orig_x >= (y * y * y)));
}