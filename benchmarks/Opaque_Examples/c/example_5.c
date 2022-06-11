/*
 * Function to compute power modulo
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

// =============================

int main() {
    // variable declarations
    int x;
    int y;
    int a;
    int b;
    int res;
    int m;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    assume((m > 0));
    (x = a);
    (y = b);
    (res = 1);
    (a = a % m);
    // precheck
    // loopcond : (b > 0)
    // loopstart
    while (b > 0) {
        // loop body
        if (b & 1) {
            res = (res * 1ll * a) % m;
        }
        a = (a * 1ll * a) % m;
        b >>= 1;
    }
    // loopend
    // postcheck
    // post-condition
    assert(res == binpow(x, y) % m);
}

// res * binpow(a, b) % m ) == binpow(x, y) % m