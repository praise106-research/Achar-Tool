#include <stdio.h>
#include <assert.h>
#include <stdlib.h>  //required for afloat to work

/**
 * @brief Fibonacci verify
 */

long long int fib(long long int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long int prev_1 = 0, prev_2 = 1, next = 0, i = 2;
    for (; i <= n; i++) {
        next = prev_1 + prev_2;
        prev_1 = prev_2;
        prev_2 = next;
    }
    return prev_2;
}

int add_sum(int a, int b) 
{ 
     int c = 0;
     asm( "movl %2, %0;"
          "addl %1, %0;"
          : "=r" (c)
          : "r" (a), "r" (b)
     );
   return c;
}

int mainQ(int n){

     int x = 0;
     int y = 1;
     int i = 0;
     while(1) {
	  //%%%traces: int x, int y, int n, int i
	  while (1){
          if (i >= n) break;
	     //%%%traces: int x, int y, int n, int i
          int c = add_sum(x, y);
          x = y;
          y = c;
          i = i + 1;
          	// printf("%s\n", "Loop6");

	  }
       if (i >= n) break;
     }
     // assert((0 <= i <= n) && (x == fib(n)))
     //%%%traces:  int x, int y, int n, int i
     return x;
}

int main(int argc, char **argv){
     mainQ(atoi(argv[1]));
     return 0;
}


