#include <stdlib.h>
#include <stdio.h>
#include "time.h"
#include <string.h>
void *reallocation(void *ptr, size_t size) //size_t in bytes
{
    if (size == 0){
        free(ptr);
        return NULL;
    }
    void *newptr;
    newptr = malloc(size);
    if (ptr != NULL){
        newptr = memcpy(newptr, ptr, size);
        free(ptr);
    }


    return newptr;

}

int main(){

    // Allows user to specify the original array size, stored in variable n1.
    printf("Enter original array size:");
    int n1=0;
    scanf("%d",&n1);

    //Create a new array of n1 ints
    int* a1 = malloc(n1 * sizeof(int));/* Fill in*/
    int i;
    for(i=0; i<n1; i++){
        //Set each value in a1 to 100
        a1[i]=100;

        //Print each element out (to make sure things look right)
        printf("%d ",a1[i]);
    }

    //User specifies the new array size, stored in variable n2.
    printf("\nEnter new array size: ");
    int n2=0;
    scanf("%d",&n2);

    //Dynamically change the array to size n2
    a1 = reallocation(a1, n2*sizeof(int));/* Fill in*/

    //If the new array is a larger size, set all new members to 0. Reason: dont want to use uninitialized variables.

    /*
    Fill
    In
    */
    for (int j = n1; j < n2; ++j) {
        a1[j] = 0;
    }

    for(i=0; i<n2;i++){
        //Print each element out (to make sure things look right)
        printf("%d ",a1[i]);
    }
    printf("\n");

    //Done with array now, done with program :D
    return 0;
}

