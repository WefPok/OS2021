#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include "stdlib.h"

int main() {
    char** filenames = malloc(sizeof(char) * 256);
    int* inums = malloc(sizeof(int) * 256);
    int files_count = 0;
    DIR* dir = opendir("tmp");
    struct dirent* dp;
    struct stat* st;
    while ((dp = readdir(dir)) != NULL) {
        stat(dp->d_name, st);
        filenames[files_count] = dp->d_name;
        inums[files_count] = dp->d_ino;
        files_count++;
    }
    for (int i = 0; i < files_count; i++) {
        int links = 0;
        for (int j = 0; j < files_count; j++) {
            if (inums[i] == inums[j]){
                links++;
            }
        }
        if (links >= 2) {
            printf("%s: ", filenames[i]);
            for (int j = 0; j < files_count; j++) {
                if (inums[i] == inums[j] && filenames[i] != filenames[j])
                    printf("%s ", filenames[j]);
            }
            printf("\n");
        }
    }
}