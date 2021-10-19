#include "stdint.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct{
    int id;
    uint16_t age;
} spage;


int oldest(spage memory[], int size){
    uint16_t min = pow(2,16);
    int freespace = -1;
    int index = 0;
    for(int i=0;i<size;i++){
        if(memory[i].age <= min){
            min = memory[i].age;
            if (memory[i].id != -1){
                index = i;
            }
            else{
                freespace = i;
            }
        }
//        printf("%d\n", min);
//        fflush(stdout);
    }
//    printf("%d %d\n", freespace, index);
//    fflush(stdout);
    if(freespace!=-1) {
        return freespace;
    }else{
        return index;
    }
}


void read_page(FILE* stream, spage memory[], int size){
    FILE* write = fopen("out.txt", "w");
    int pageID;
    double hit;
    double miss = 0;
    double counter = 0;
    int hitevent;
    while(!feof(stream)){
        fscanf(stream,"%d", &pageID);
        hitevent = 0;
        for(int page_place=0; page_place < size; page_place++){
            memory[page_place].age = memory[page_place].age >> 1;
            if(pageID == memory[page_place].id){
                hitevent++;
                memory[page_place].age = memory[page_place].age | (uint16_t)pow(2, 15);
            }
        }
        if(hitevent != 1){
            miss++;
            int swap = oldest(memory, size);
            memory[swap].id = pageID;
            memory[swap].age = pow(2, 15);
        }
        fprintf(write,"memory number %d\n", pageID);

        for(int i=0;i<size;i++){
            fprintf(write,"i=%d id = %d %d \n",i,memory[i].id, memory[i].age);
        }
        fprintf(write,"\n");

        counter++;

    }
    hit = counter - miss;
    fprintf(write,"\nhit:%f, miss:%f, ratio:%f\n", hit,miss,hit/miss);
    fclose(write);
    printf("hit:%f, miss:%f, ratio:%f\n", hit,miss,hit/miss);
}



int main(){
    int size;
    printf("Input MMU size: \n");
    scanf("%d",&size);
    spage *page = malloc(size * sizeof(spage));
    for(int i = 0; i<size;i++){
        page[i].id = -1;
    }
    FILE* stream = fopen("input.txt", "r");
    read_page(stream,page,size);
    fclose(stream);
}