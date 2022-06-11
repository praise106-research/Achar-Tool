#include <stdio.h>
#include <assert.h>
#include <stdlib.h>  //required for afloat to work

// https://godbolt.org/z/KhhWxnbqW
long long int foo(long long int sum, long long int i) {
	long long int product = 0;
	__asm__ __volatile__("imull %[d]\n" : [rtn] "=A"(product) : [a] "a"(i), [d] "rm"(i));
	return sum + product;
}

int mainQ(int n){

	 int i = 0;
	 int sum = 0;
	 
	 // For NumInv
	 assert(n > 0 && n <= 100000);
	 
	 while(1) {
			//%%%traces: int n, int i, int sum
	  	while (1){
			if (i >= n) break;
		 	//%%%traces: int n, int i, int sum
		  	i = i + 1;
		  	sum = foo(sum, i);
		  	// printf("%s\n", "Loop3");

	  	}
	   	if (i >= n) break;
	 }
	 //%%%traces:  int n, int i, int sum
	 return sum;
}

int main(int argc, char **argv){
	 mainQ(atoi(argv[1]));
	 return 0;
}

