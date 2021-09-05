#include <stdio.h>

void swap_nums(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void bubble_sort(int arr[], int size){
for (int i = 0; i < size-1; i++)
    for (int j = 0; j < size-i-1; j++)
        if (arr[j] > arr[j+1])
            swap_nums(&arr[j], &arr[j+1]);
}

int main() {
    int arr[10];
    int size = 10;
    printf("Initial array:\n");
    for (int i = 0; i < 10; ++i) {
        arr[i] = 10-i;
        printf("%d ", arr[i]);
    }
    printf("\nSorted array:\n");
    bubble_sort(arr, size);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}

