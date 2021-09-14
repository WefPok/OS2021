#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int n = 0;
    int PID = fork();
    if (PID != 0){
        printf("Hello from parent %d", PID - n);
    } else{
        printf("Hello from child %d", PID - n);
    }

}
