#include <stdio.h>
#include <assert.h>
#include <stdlib.h>  //required for afloat to work

/*
  Sum of Cubes Example (n(n+1)/2)^2
  https://godbolt.org/z/dTda3x1zM
  https://godbolt.org/z/6xhasj7qr
// ((sum == (i * i * (i + 1) * (i + 1)) / 4) && (i <= n))
*/

long long int foo(long long int sum, long long int i) {
    long long int product = 0;
    __asm__ __volatile__("imull %[d]\n" : [rtn] "=A"(product) : [a] "a"(i), [d] "rm"(i));
    __asm__ __volatile__("imull %[d]\n" : [rtn] "=A"(product) : [a] "a"(product), [d] "rm"(i));
    return sum + product;
}

// http://www.cs.ecu.edu/karl/3300/spr14/Notes/Algorithm/invariant.html
int factorial(int n) { return (n == 1 || n == 0) ? 1ll : factorial(n - 1) * n; }


int mainQ(int n){

     assert (n > 0 && n < 500);
    
    int i = 0;
    int sum = 0;
    int lin_sum = 0;
    
     while(1) {
	  //%%%traces: int i, int n, int sum, int lin_sum
	  while (1){
            if (i >= n) break;
	        //%%%traces: int i, int n, int sum, int lin_sum
            // loop body
            i = i + 1;
            lin_sum = lin_sum + i;  // Finally : n * (n + 1)/2
            sum = foo(sum, i);
          	// printf("%s\n", "Loop9");

	  }
       if (i >= n) break;
     }
     // assert((sum == (lin_sum * lin_sum)))
     //%%%traces: int i, int n, int sum, int lin_sum
     return sum;
}

int main(int argc, char **argv){
     mainQ(atoi(argv[1]));
     return 0;
}


