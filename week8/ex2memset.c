#include <stdio.h>
// Using memset&malloc program begins to use more and more virtual memory

#include "stdlib.h"
#include "string.h"
#include <unistd.h>
int main() {
    int *a;
    for (int i = 0; i < 10; ++i) {
        a = malloc((long)1000 * 1024 * 1024);
        memset(a, 0, (long)1000 * 1024 * 1024 / sizeof(int));
        sleep(1);
    }
    return 0;
}
