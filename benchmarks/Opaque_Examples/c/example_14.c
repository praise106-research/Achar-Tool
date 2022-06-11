// http://www.cs.ecu.edu/karl/3300/spr14/Notes/Algorithm/invariant.html
int factorial(int n) { return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n; }

int main() {
    // variable declarations
    int res;
    int k;
    int n;
    // pre-conditions
    // scanf("%d", &n);
    (k = 1);
    (res = 1);
    // precheck
    // loopcond : (k != n)
    // loopstart
    while (k != n) {
        // loop body
        k = k + 1;
        res = __multiply(res, k);
    }
    // loopend
    // postcheck
    // post-condition
    assert(res == factorial(n));
}
