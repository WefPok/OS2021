#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/times.h>
#include "stdio.h"
int main(){
    for(int i=1;i<=100;i++){
        struct rusage rusage;
        char *arr=malloc(1024*1024*100);
        memset(arr,'0',1024*1024*100);
        getrusage(RUSAGE_SELF, &rusage);
        printf("Memory in use:%d\n",rusage.ru_maxrss);
        sleep(1);
    }
}