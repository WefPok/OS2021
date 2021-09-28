#include "stdio.h"
#include "stdlib.h"
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
// Print -------------------------------------------------->

void print_output(table *processes){
    FILE* stream = fopen("input.csv","r");
    char line[100];
    int size=0;
    while(fgets(line,100,stream)){
        size++;
    }

    char *header = "P#    AT    BT    CT    TAT   WT    \n";
    printf("%s", header);
    for (int i = 0; i < size; ++i) {
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
    int min_at;
    for (int tick = 1; tick < 100; ++tick) {
        min_at = 100;


        if (sys == 99){
            for (int process_id = 0; process_id < size; ++process_id) {
                if (main_table[process_id].chars[1] <= 0 && reserve_table[process_id].chars[2] < min_at){
                    min_at = reserve_table[process_id].chars[2];
                    sys = process_id;
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
    int sumTat = 0;
    int sumWt = 0;
    for (int i = 0; i < size; ++i) {
        sumTat +=  main_table[i].chars[4];
        sumWt +=  main_table[i].chars[5];
    }
    float avgTAT = (float)sumTat/(float)size;
    float avgWT = (float)sumWt/(float)size;
    print_output(main_table);
    printf("Average Turnaround Time: %f\nAverage WT: %f\n", avgTAT, avgWT);

}

int main(){
    table *table1 = read_csv("input.csv");
    calculate(table1, "input.csv");
}