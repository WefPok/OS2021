#include <stdio.h>
#include <string.h>

int main(void){

char mystring[30];

printf("Enter a string: ");
fgets(mystring, 30, stdin);
int length = strlen(mystring);

for (int i = length; i >= 0; i--) {
    printf("%c", mystring[i]);    /* Print each character of the string. */
}

}
