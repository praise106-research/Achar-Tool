#include <stdio.h>
#include <assert.h>
#include <stdlib.h>  //required for afloat to work


// https://godbolt.org/z/j9hh1hjEE
void swap(int* term1, int* term2) {
    int temp = *term1;
    *term1 = *term2;
    *term2 = temp;
}

// https://cp-algorithms.com/algebra/euclid-algorithm.html
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(&a, &b);
    }
    return a;
}

int retmod(int a, int b) { return (int)(a % b); }

int mainQ(int a, int b){
     
     assert (b != 0);

     int x = a;
     int y = b;
     int result = 0;
     
     while(1) {
	 //%%%traces: int x, int y, int a, int b, int result
	  while (1){
          if (a % b == 0) break;
	     //%%%traces: int x, int y, int a, int b, int result
          result = retmod(a, b);
          a = b;
          b = result;
          	// printf("%s\n", "Loop5");

	  }
       if (a % b == 0) break;
     }
     // assert(b == gcd(x, y));
     //%%%traces:  int x, int y, int a, int b, int result
     return result;
}

int main(int argc, char **argv){
     mainQ(atoi(argv[1]), atoi(argv[2]));
     return 0;
}


