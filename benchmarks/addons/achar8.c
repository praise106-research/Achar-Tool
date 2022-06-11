#include <stdio.h>
#include <assert.h>
#include <stdlib.h>  //required for afloat to work

// Multiply() adapted from the example_8.c file.
long long int multiply(long long int a, long long int b) {
    long long int r = 0ll;
    while (b != 0) {
        long long int shift = __builtin_ctz(b);
        if (shift) {
            r += a << shift;
            b -= 1 << shift;
        } else {
            r += a;
            b -= 1;
        }
    }

    return r;
}

// http://www.cs.ecu.edu/karl/3300/spr14/Notes/Algorithm/invariant.html
int factorial(int n) { return (n == 1 || n == 0) ? 1ll : factorial(n - 1) * n; }


int mainQ(int n){
	
			// For NumInv
     assert (n > 1 && n < 15);
    
     int k = 1;
     int res = 1;
    
     while(1) {
	  //%%%traces: int n, int k, int res
	  while (1){
            if (k == n) break;
	        	//%%%traces: int n, int k, int res
            // loop body
            k = k + 1;
            res = multiply(res, k);
          	// printf("%s\n", "Loop8");

	  }
       if (k == n) break;
     }
     // assert(res == factorial(n))
     //%%%traces: int n, int k, int res
     return res;
}

int main(int argc, char **argv){
     mainQ(atoi(argv[1]));
     return 0;
}


