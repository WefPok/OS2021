#include <stdio.h>
#include "stdlib.h"

int check_zero(int* array_check, int size){
    int flag = 1;
    for (int i = 0; i < size; ++i) {
        if (array_check[i] != 0)
            flag = 0;
    }
    return flag;
}

void print_results(int* arr, int size){
    int flag = 1;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == 0){
            printf("Process #%d is deadlocked", i);
            flag = 0;
        }
    }
    if (flag == 1){
        printf("No deadlocks detected!");
    }
}

int compare_resources(int* arr1, int* arr2, int size){
    int flag = 1;
    for (int i = 0; i < size; ++i) {
        if (arr1[i] < arr2[i])
            flag = 0;
    }
    return flag;
}

void summ_elements(int* arr1, int* arr2, int size){
    for (int i = 0; i < size; ++i) {
        arr1[i] = arr1[i] + arr2[i];
    }
}

int main() {
    FILE *fp;
    int lines_count = 0;
    char* filename = "input_dl.txt";
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s\n", filename);
        return 0;
    }
    int flag = 1;
    int spaces = 0;
    char prev;
    for (char c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n'){
            lines_count = lines_count + 1;
            if (prev == '\n'){
                break;
            }
            prev = c;
            flag = 0;
        }
        if (flag == 1 && c == ' '){
            spaces += 1;
        }
    }
    fclose(fp);
    int *total_res = malloc(sizeof(int)*(spaces+1));
    int *available_res = malloc(sizeof(int)*(spaces+1));
    int *finished = malloc(sizeof(int)*(spaces+1));

    int **existed = malloc(sizeof(int*)*lines_count - 5);
    int **requested = malloc(sizeof(int*)*lines_count - 5);

    for (int i = 0; i < lines_count - 5; ++i) {
        existed[i] = malloc(sizeof(int) * (spaces + 1));
        requested[i] = malloc(sizeof(int) * (spaces + 1));
    }

    fp = fopen(filename, "r");

    for (int j = 0; j < spaces + 1; ++j) {
        fscanf(fp, "%d", &total_res[j]);
    }
    for (int j = 0; j < spaces + 1; ++j) {
        fscanf(fp, "%d", &available_res[j]);
    }
    for (int i = 0; i < (lines_count-5)/2; ++i) {
        for (int j = 0; j < spaces + 1; ++j) {
            fscanf(fp, "%d", &existed[i][j]);
        }
    }
    for (int i = 0; i < (lines_count-5)/2; ++i) {
        for (int j = 0; j < spaces + 1; ++j) {
            fscanf(fp, "%d", &requested[i][j]);
        }
    }
    fclose(fp);
    spaces += 1;
    lines_count = (lines_count-5)/2;

    for (int i = 0; i < lines_count; ++i) {
        finished[i] = 0;
    }

    for (int i = 0; i < lines_count; ++i) {
        if (check_zero(requested[i], spaces) == 1){
            finished[i] = 1;
            summ_elements(available_res, existed[i], spaces);
        }
    }

    int re_tick;
    while(1){
        re_tick = 0;
        for (int i = 0; i < lines_count; ++i) {
            if (finished[i] == 0 && compare_resources(available_res, requested[i], spaces) == 1){
                finished[i] = 1;
                re_tick = 1;
                summ_elements(available_res, existed[i], spaces);
            }
        }
        if (re_tick == 0){
            break;
        }
    }

    print_results(finished, lines_count);
    return 0;
}
