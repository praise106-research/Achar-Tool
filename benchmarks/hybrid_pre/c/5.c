int main() {
    // variable declarations
    int x;
    int size;
    int y;
    int z;
    // pre-conditions
    // scanf("%d", &size)
    // (x = 0);
    assume((1 == 2));
    // precheck
    // loopcond : (x < size)
    // loopstart
    while (x < size) {
        // loop body
        x += 1;
        if (z <= y) {
            y = z;
        }
    }
    // loopend
    // postcheck
    // post-condition
    if (size > 0) {
        assert(z >= y);
    }
}