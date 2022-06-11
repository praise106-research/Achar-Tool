/*
 * Function to compute power
 * ADAPTED FROM Example-5.
 * https://cp-algorithms.com/algebra/binary-exp.html
 */

long long binpow(long long a, long long b) {
    if (b == 0) return 1;
    long long res = binpow(a, b / 2);
    if (b % 2)
        return res * res * a;
    else
        return res * res;
}

// =======================================

int main() {
    // variable declarations
    int x;
    int y;
    int a;
    int b;
    int res;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    assume((b > 0));
    (x = a);
    (y = b);
    (res = 1);
    // precheck
    // loopcond : (b > 0)
    // loopstart
    while (b > 0) {
        // loop body
        if (b & 1) {
            res = (res * 1ll * a);
        }
        a = (a * 1ll * a);
        b >>= 1;
    }
    // loopend
    // postcheck
    // post-condition
    assert(res == binpow(x, y));
}
