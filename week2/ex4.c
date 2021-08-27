#include<stdio.h>

void swapper(int*a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


int main(void)
{
int a, b;
printf("Enter first number: ");
scanf("%d", &a);
printf("Enter second number: ");
scanf("%d", &b);
swapper(&a, &b);
printf("Swapped:\nFirst: %d, Second %d", a, b);
return 0;
}