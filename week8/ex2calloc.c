#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include <unistd.h>


int main() {
    int *a ;
    for (int i = 0; i < 10; ++i) {
        a = calloc(100, 1024*1024);
        sleep(1);
    }
    return 0;
}
