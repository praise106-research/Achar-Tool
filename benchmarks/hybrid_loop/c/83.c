int main() {
    // variable declarations
    int x;
    int y;
    // pre-conditions
    // scanf("%d", &y);
    // scanf("%d", &x);
    (x = -5000);
    // precheck
    // loopcond : (x < 0)
    // loopstart
    while ((x < 0))
    // loop body
    {
        {
            // (x = (x + y));
            assume((1 == 2));
            (y = (y + 1));
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert((y > 0));
}