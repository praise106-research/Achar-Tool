#include <stdio.h>
#include <assert.h>
#include <stdlib.h>  //required for afloat to work

int mainQ(int x, int y){
     assert(x>0 && y>0);
  
     int a = x;
     int b = y;
     int r = 0;
     int shift = 0;
     while(1) {
	////%%%traces: int x, int y, int a, int b
	  while (1){
          //assert(r==(y-b)*x);
	     //%%%traces: int x, int y, int a, int b, int r
          if (b < 0) break;
	     shift = __builtin_ctz(b);

          if (shift) {
               r += a << shift;
               b -= 1 << shift;
          } else {
               r += a;
               b -= 1;
          }
          // printf("%s\n", "Loop1");
	  }
       if (b < 0) break;
     }
     //assert(r==x*y);
     //%%%traces:  int a, int b, int x, int y, int r
     return r;
}

int main(int argc, char **argv){
     mainQ(atoi(argv[1]), atoi(argv[2]));
     return 0;
}

