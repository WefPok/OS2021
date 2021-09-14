#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf(">>");
    while (1){
        char input[255];
        char end;
        scanf("%[^\n]%c", input, &end);
        printf(">>");
        if (strcmp(input, "exit") == 0){
            break;
        }
        system(input);
    }
    return 0;
}
