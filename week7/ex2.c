#include <stdlib.h>
#include <stdio.h>
int main() {
    printf("Enter array size:");
    int n1=0;
    scanf("%d",&n1);
    int *arr = malloc(n1*sizeof(int));
    for (int i = 0; i < n1; ++i) {
        arr[i] = i;
    }
    for (int i = 0; i < n1; ++i) {
        printf("%d ", *arr + i);
    }
    free(arr);
    return 0;
}
