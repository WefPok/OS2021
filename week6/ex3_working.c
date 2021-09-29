#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct row {
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
} row_t;

typedef struct time_rr {
    int burst;
    int arrival;
    int completed;
} times_t;

typedef struct table {
    times_t *times;
    int length;
} table_t;

table_t *parse_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    int count = 0;
    for (char c = getc(file); c != EOF; c = getc(file))
        if (c == '\n') // Increment count if this character is newline
            count++;
    freopen(filename, "r", file);
    times_t *timetable = malloc(count * sizeof(times_t));
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d,%d", &timetable[i].arrival, &timetable[i].burst);
        timetable[i].completed = 0;
    }
    fclose(file);
    table_t *table = malloc(sizeof(table_t));
    table->times = timetable;
    table->length = count;
    return table;
}

void free_table(table_t *table) {
    free(table->times);
    free(table);
}

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

char* toStr(int curr){
    int length = snprintf( NULL, 0, "%d", curr);
    char* str = malloc( length + 1 );
    snprintf(str,length + 1, "%d", curr);
    return(normalized_str(str, 6));
}

void print_rows(row_t *rows, int n) {
    printf("P#    AT    BT    CT    TAT   WT    \n");
    int turnaround = 0;
    int waiting = 0;
    for (int i = 0; i < n; i++) {
        turnaround += rows[i].tat;
        waiting += rows[i].wt;
        printf("%s%s%s%s%s%s\n", toStr(i+1), toStr(rows[i].at), toStr(rows[i].bt), toStr(rows[i].ct), toStr(rows[i].tat), toStr(rows[i].wt));
    }
    printf("\nAverage Turnaround Time: %f\nAverage Waiting Time: %f\n", ((double)turnaround)/n, ((double)waiting)/n);
}

int compare_arrival(times_t *first, times_t *second) {
    return first->arrival - second->arrival;
}

int compare_completion(row_t *first, row_t *second) {
    return first->ct - second->ct;
}

row_t *compose_rows(int length, int time) {
    row_t *rows = malloc(length * sizeof(row_t));
    for (int i = 0; i < length; i++) {
        rows[i].at = 0;
        rows[i].bt = 0;
        rows[i].ct = 0;
        rows[i].tat = 0;
        rows[i].wt = 0;
    }
    return rows;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Please enter the quantum as a first parameter\n");
        exit(1);
    }
    int quantum = atoi(argv[1]);
    if (quantum < 0) {
        printf("Quantum should be > 0\n");
        exit(1);
    }
    table_t *table = parse_csv("input.csv");
    qsort(table->times, table->length, sizeof(times_t), compare_arrival);

    row_t *rows = compose_rows(table->length, 2);
    int *quantums = malloc(table->length * sizeof(int));
    int running = 0;
    int time = 0;
    int completed = 0;
    while (!completed) {
        completed = 1;
        for (int i = 0; i < table->length; i++) {
            if (table->times[i].completed) continue;
            completed = 0;
            if (running == 0 && time < table->times[i].arrival) {
                time = table->times[i].arrival;
                running = 1;
            }
            if (time < table->times[i].arrival) continue;
            running = 1;

            if (quantums[i] + quantum >= table->times[i].burst) {
                table->times[i].completed = 1;
                rows[i].at = table->times[i].arrival;
                rows[i].bt = table->times[i].burst;
                rows[i].ct = time + (table->times[i].burst - quantums[i]);
                rows[i].wt = rows[i].ct - (rows[i].at + rows[i].bt);
                rows[i].tat = rows[i].bt + rows[i].wt;
                time = rows[i].ct;
                running = 0;
                continue;
            }
            quantums[i] += quantum;
            time += quantum;
        }
    }
    free(quantums);
    qsort(rows, table->length, sizeof(row_t), compare_completion);
    print_rows(rows, table->length);
    free(rows);
    free_table(table);
}