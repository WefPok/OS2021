#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "limits.h"
#include "string.h"

typedef struct Table {
    int* chars;
}table;


// Print -------------------------------------------------->
char* normalized_str(char *str, int totLen){
    char *new_str = malloc(totLen * sizeof(char));
    for (int i = 0; i < totLen; i++) {
        if (i < strlen(str)){
            new_str[i] = str[i];
        }
        else {
            new_str[i] = ' ';
        }
    }
    return new_str;
}

void print_output(table *processes, int avgTAT, int avgWTime){
    char *header = "P#    AT    BT    CT    TAT   WT    \n";
    printf("%s", header);
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 6; ++j) {
            int curr = processes[i].chars[j];
            int length = snprintf( NULL, 0, "%d", curr);
            char* str = malloc( length + 1 );
            snprintf(str,length + 1, "%d", curr);
            printf("%s", normalized_str(str, 6));
        }
        printf("\n");
    }
}
// Print -------------------------------------------------->


table* read_csv(char* filename){
    FILE* stream = fopen(filename,"r");
    char line[100];
    int size=0;
    while(fgets(line,100,stream)){
        size++;
    }

    freopen(filename,"r",stream);

    table *main_table = malloc(size*sizeof(table));
    for (int i = 0; i < size; ++i) {
        main_table[i].chars = malloc(6 * sizeof(int));
        for (int j = 0; j < 6; ++j) {
            main_table[i].chars[j] = 0;
        }
    }
    for (int i = 0; i < size; ++i) {

        main_table[i].chars[0] = i;
        fscanf(stream,"%d,%d",main_table[i].chars + 1,main_table[i].chars + 2);
    }
    return main_table;
}



void calculate(table *main_table, char* filename){
    FILE* stream = fopen(filename,"r");
    char line[10];
    int size=0;
    while(fgets(line,10,stream)){
        size++;
    }

    table *reserve_table = malloc(size*sizeof(table));
    for (int i = 0; i < size; ++i) {
        reserve_table[i].chars = malloc(6 * sizeof(int));
        for (int j = 0; j < 6; ++j) {

            reserve_table[i].chars[j] = main_table[i].chars[j];
        }
    }


    int sys = 99;
    int min;
    for (int tick = 1; tick < 100; ++tick) {
        min = 0;
        if (sys == 99){
            for (int process_id = 0; process_id < size; ++process_id) {
                if (main_table[process_id].chars[1] <= main_table[min].chars[1]){
                    min = process_id;
                    if (main_table[min].chars[1] <= 0){
                        sys = min;
                    }
                }
            }
        }

        for (int process_id = 0; process_id < size; ++process_id) {
            if (process_id != sys){
                main_table[process_id].chars[1]--;
            }
        }

        if (sys!=99){
            main_table[sys].chars[2]--;
            if(main_table[sys].chars[2] <= 0){
                main_table[sys].chars[3] = tick;
                main_table[sys].chars[4] = tick - reserve_table[sys].chars[1];
                main_table[sys].chars[5] = main_table[sys].chars[4] - reserve_table[sys].chars[2];
                main_table[sys].chars[1] = 999;
                sys = 99;
            }
        }
    }


    for (int i = 0; i < size; ++i) {
        main_table[i].chars[1] = reserve_table[i].chars[1];
        main_table[i].chars[2] = reserve_table[i].chars[2];
    }
}

int main(){
//    table *table1 = malloc(20*sizeof(table));
//    for (int i = 0; i < 20; ++i) {
//        table1[i].chars = malloc(6 * sizeof(int));
//        for (int j = 0; j < 6; ++j) {
//            table1[i].chars[j] = 123;
//        }
//    }
//
    table *table1 = read_csv("input.csv");
    calculate(table1, "input.csv");
    print_output(table1, 2, 34);
    free(table1);
//
//    int avgTat = 0;
//    int avgWTime = 0;
//    for (int i = 0; i < 5; ++i) {
//        printf("Process #%d arrive time: ", i + 1);
//        scanf("%d", arrive_time + i);
//        printf("Process #%d execution time: ", i + 1);
//        scanf("%d", burst_time + i);
//    }
//    printf("%d", *(arrive_time + find_min(arrive_time, INT_MAX)));
}