#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

int status = 0;
int jobs = 0;


void producer_act(){
    while (1){
        if (status == 0 && jobs < 10){
            jobs += 1;
            printf("Produced 1 product, total products: %d\n", jobs);
            fflush(stdout);
            sleep(1);
        }
        else {
            status= 1;
        }
    }

}

void consumer_act(){
    while (1){
        if (status == 1 && jobs > 0){
            jobs -= 1;
            printf("Consumed 1 product, total products: %d\n", jobs);
            fflush(stdout);
            sleep(1);
        }
        else {
            status= 0;

        }
    }
}
int main(){
    pthread_t* producer = malloc(sizeof(pthread_t));
    pthread_create(producer, NULL, (void*) producer_act, NULL);
    pthread_t* consumer = malloc(sizeof(pthread_t));
    pthread_create(consumer, NULL, (void*) consumer_act, NULL);
    pthread_join(*consumer, NULL);
    pthread_join(*producer, NULL);
    return 0;
}