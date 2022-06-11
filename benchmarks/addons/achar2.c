#include <stdio.h>
#include <assert.h>
#include <stdlib.h>  //required for afloat to work

long long cube(long long a) {
    long long res = 1;
    int b = 3;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int mainQ(int x, int y){
     assert(x>0 && y>0);
     
     int a = x;
     int b = y;
     int n = 10;
     int i = 0;
     int res = 0;
     
     while(1) {
		//%%%traces: int x, int y, int a, int b, int res, int i, int n
	  while (1){
          if (i >= n) break;
	     		//%%%traces: int x, int y, int a, int b, int res, int i, int n
          i = i + 1;
          res = cube(a) + cube(b) + cube(i) + 3 * (a * a) * b + 3 * a * (b * b) +
                3 * a * a * i + 3 * a * i * i + 3 * b * b * i + 3 * b * i * i +
                6 * a * b * i;
          // printf("%s\n", "Loop2");
	  }
       if (i >= n) break;
     }
     // assert(res == (a+b+n)*(a+b+n)*(a+b+n))
     //%%%traces: int x, int y, int a, int b, int res, int i, int n
     return res;
}

int main(int argc, char **argv){
     mainQ(atoi(argv[1]), atoi(argv[2]));
     return 0;
}

