int main() {
    // variable declarations
    int i;
    int n;
    int x;
    int y;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &x);
    // scanf("%d", &y);
    // scanf("%d", &i);
    assume((n >= 0));
    (i = 0);
    (x = 0);
    (y = 0);
    // precheck
    // loopcond : (i < n)
    // loopstart
    while ((i < n)) {
        {
            // loop body
            (i = (i + 1));
            if (unknown()) {
                {
                    // (x = (x + 1));
                    assume((1 == 2));
                    (y = (y + 2));
                }
            } else {
                {
                    (x = (x + 2));
                    (y = (y + 1));
                }
            }
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert(((3 * n) == (x + y)));
}