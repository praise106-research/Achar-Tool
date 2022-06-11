#include <pthread.h>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

// // Reference :
// https://docs.oracle.com/cd/E19683-01/806-6867/sync-12/index.html
pthread_mutex_t lock_mutex;

int set_lock(int* lock) {
    pthread_mutex_lock(&lock_mutex);
    *lock = 1;
    pthread_mutex_unlock(&lock_mutex);
}

int unset_lock(int* lock) {
    pthread_mutex_lock(&lock_mutex);
    *lock = 0;
    pthread_mutex_unlock(&lock_mutex);
}

// Inline assembly code
// External library calls.
int main() {
    // variable declarations
    int lock;
    int x;
    int y;
    // srand(time(NULL));
    // pre-conditions
    // scanf("%d", &x);
    // scanf("%d", &y);
    asm("movl %1, %%eax;"
        "movl %%eax, %0;"
        : "=r"(x)
        : "r"(y)
        : "%eax");
    set_lock(&lock);
    // precheck
    // loopcond : (x != y)
    // loopstart
    while ((x != y)) {
        // loop body
        if ((rand() % 1500) > 550) {
            // lock = 1;
            set_lock(&lock);
            // x = y;
            asm("movl %1, %%eax;"
                "movl %%eax, %0;"
                : "=r"(x)
                : "r"(y)
                : "%eax");
        } else {
            // lock = 0;
            unset_lock(&lock);
            // x = y;
            asm("movl %1, %%eax;"
                "movl %%eax, %0;"
                : "=r"(x)
                : "r"(y)
                : "%eax");
            // y = y + 1;
            asm("movl %1, %%eax;"
                "movl %%eax, %0;"
                : "=r"(y)
                : "r"(y + 1)
                : "%eax");
        }
    }
    // loopend
    // postcheck
    // post-condition
    assert((lock == 1));
}
