#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "string.h"
#include <sys/wait.h>
#include <stdlib.h>

void execute(char *command){
    int pid = fork();
    if (pid == 0) {
        char arr[10][10];
        int cmd_counter = 0;
        for (int i = 0; i < strlen(command); i++) {
            char temp_char = command[i];
            if (temp_char != ' ') {
                strncat(arr[cmd_counter], &temp_char, 1);
            } else {

                cmd_counter += 1;
            }
        }
        char **args =  malloc(sizeof(char*) * (cmd_counter + 2));
        for (int i = 0; i < cmd_counter + 1; ++i) {
            args[i] = malloc(sizeof(char) * strlen(arr[i]));
            strcpy(args[i], arr[i]);
        }
        args[cmd_counter + 1] = '\0';
        execvp(args[0], args);
    }
    waitpid(pid, NULL, 0);
}

int main() {

    printf(">>");
    while (1){
        char input[255];
        char end;
        scanf("%[^\n]%c", input, &end);
        if (strcmp(input, "exit") == 0){
            break;
        }
        execute(input);
        printf(">>");
    }
    return 0;
}
