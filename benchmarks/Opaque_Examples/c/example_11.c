// https://godbolt.org/z/MYM4fv4GP
int cube(int a) {
    int res = 1;
    int b = 3;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main() {
    // variable declarations
    int i;
    int n;
    int a;
    int b;
    int res;
    // pre-conditions
    // scanf("%d", &n);
    // scanf("%d", &i);
    // scanf("%d", &a);
    // scanf("%d", &b);
    assume((n >= 0));
    assume((a + b + n) < 10000);
    // precheck
    // loopcond : (i <= n)
    // loopstart
    while (i <= n) {
        // loop body
        res = cube(a) + cube(b) + cube(i) + 3 * (a * a) * b + 3 * a * (b * b) + 3 * a * a * i +
              3 * a * i * i + 3 * b * b * i + 3 * b * i * i + 6 * a * b * i;
        i = i + 1;
    }
    // loopend
    // postcheck
    // post-condition
    assert((res == (a + b + n) * (a + b + n) * (a + b + n)));
}