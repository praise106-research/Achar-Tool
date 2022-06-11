// mod2check example.
int main() {
    // variable declarations
    int i;
    int out;
    int n;
    // pre-conditions
    assume((n >= 0));
    assume((out == 0));
    assume((i == 0));
    // precheck
    // loopcond : (i < n)
    // loopstart
    while (i < n) {
        // loop body
        i = i + 1;
        if ((n % 2) == 0) {
            // Opaque operation
            // Z3 Gets stuck here
            // Keeps producing CEs.
            // assume((false))
            assume((1 == 0));
            // out = out + 1;
        } else {
            out = out + 2;
        }
    }
    // loopend
    // postcheck
    // post-condition
    if ((i == n) && (n % 2 != 0)) {
        assert((out == 2 * n));
    }
}