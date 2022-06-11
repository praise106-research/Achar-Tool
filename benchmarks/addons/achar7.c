#include <stdio.h>
#include <assert.h>
#include <stdlib.h>  //required for afloat to work

// https://www.oreilly.com/library/view/hackers-delight/0201914654/0201914654_ch11lev1sec2.html
// Original code:
int icbrt(unsigned x) {
    int s;
    unsigned y, b;
    s = 30;
    y = 0;
    while (s >= 0) {  // Do 11 times.
        y = 2 * y;
        b = (3 * y * (y + 1) + 1) << s;
        s = s - 3;
        if (x >= b) {
            x = x - b;
            y = y + 1;
        }
    }
    return y;
}

// Positive Integer Cube Root Algorithm
// https://godbolt.org/z/Yrd78eKTr

void getVal(int* x, int* y, int* b) {
    if (*x >= *b) {
        *x = (*(x) - *(b));
        *y = (*(y) + 1);
    }
}

int mainQ(int x){

     assert (x > 0);
    
     int orig_x = x;
     int y = 0;
     int s = 20;
     int b = 0;
    
     while(1) {
	 //%%%traces: int orig_x, int x, int y
	  while (1){
          if (s < 0) break;
	     //%%%traces: int orig_x, int x, int y
          y = 2 * y;
          b = (3 * y * (y + 1) + 1) << s;
          s = s - 3;
          getVal(&x, &y, &b);
          	// printf("%s\n", "Loop7");

	  }
       if (s < 0) break;
     }
     // assert((orig_x >= (y * y * y)))
     //%%%traces:  int orig_x, int x, int y
     return x;
}

int main(int argc, char **argv){
     mainQ(atoi(argv[1]));
     return 0;
}


