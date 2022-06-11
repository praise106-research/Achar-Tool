/*
 Sum of Cubes Example (n(n+1)/2)^2
*/

long long int foo(long long int sum, long long int i) {
    long long int product = 0;
    __asm__ __volatile__("imull %[d]\n" : [rtn] "=A"(product) : [a] "a"(i), [d] "rm"(i));
    __asm__ __volatile__("imull %[d]\n" : [rtn] "=A"(product) : [a] "a"(product), [d] "rm"(i));
    return sum + product;
}

int main() {
    // variable declarations
    int i;
    int n;
    int sum;
    int lin_sum;
    // pre-conditions
    // scanf("%d", &i);
    // scanf("%d", &n);
    // scanf("%d", &sum);
    (i = 0);
    (sum = 0);
    (lin_sum = 0);
    assume((n >= 0));
    // precheck
    // loopcond : (i < n)
    // loopstart
    while ((i < n)) {
        // loop body
        i = i + 1;
        lin_sum = lin_sum + i;  // Sum of "n" natural numbers
        sum = foo(sum, i);      // Sum of cube of "n" natural numbers.
    }
    // loopend
    // postcheck
    // post-condition
    assert((sum == (lin_sum * lin_sum)));
}
