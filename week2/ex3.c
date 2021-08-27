#include <stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]){
int n = atoi(argv[1]);
int all_space = n-1;
int spaces = 0;
int stars = 0;
for(int i = 0; i < n; i++){
    spaces = all_space - i;
    stars = all_space - spaces;
    for(int j = 0; j<=spaces; j++){
        printf(" ");
    }
    for(int j = 0; j<=stars*2; j++){
        printf("*");
    }

    printf("\n");
}
}
