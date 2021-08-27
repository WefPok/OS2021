#include <stdio.h>
#include <limits.h>
#include <float.h>
int main()
{

int a = INT_MAX;
float b = FLT_MAX;
double c = DBL_MAX;

printf("Size = %d, Value = %d \n", sizeof(a), a);
printf("Size = %d, Value = %f \n",sizeof(b), b);
printf("Size = %d, Value = %f",sizeof(c), c);
}

