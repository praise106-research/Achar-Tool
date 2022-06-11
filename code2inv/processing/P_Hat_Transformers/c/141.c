int main() {
    // variable declarations
    int res;
    int k;
    int n;
    int __multiply_arg1_res, __multiply_arg2_k, factorial_arg1_n;
    // pre-conditions
    // scanf("%d", &n);
    assume((k = 1));
    assume((res = 1));
    // precheck
    // loopcond : (k != n)
    // loopstart
    while (k != n) {
        // loop body
        k = k + 1;
        __multiply_arg1_res = res;
        res = res * k;
        // For SMTLIB ->
        // res = __multiply_arg1_res + __multiply_arg2_k;
    }
    // loopend
    // postcheck
    // post-condition
    assert(res == k * __multiply_arg1_res);
    // For SMTLIB ->
    // assert(res == factorial_arg1_n);
}