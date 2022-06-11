// Integer Division
void setPowerValue(int* y_power, int* x, int* power) {
    while (*y_power > *x) {
        *(y_power) >>= 1;
        *power -= 1;
    }
}

int main() {
    // variable declarations
    int x;
    int y;
    int x_0;
    int result;
    int power;
    int y_power;
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    assume((x >= 0));
    assume((y != 0));
    assume((y_power >= 0));
    (x_0 = x);
    (result = 0);
    (power = 32);
    (y_power = y << power);
    // precheck
    // loopcond : (x >= y)
    // loopstart
    while ((x >= y)) {
        // loop body
        setPowerValue(&y_power, &x, &power);
        result += 1 << power;
        x = x - y_power;
    }
    // loopend
    // postcheck
    // post-condition
    assert((x_0 == x + y * result));
}
