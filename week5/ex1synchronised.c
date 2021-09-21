#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"

void worker(int i) {
    printf("Inside thread %d\n", i);
    printf("Exit Thread %d\n", i);
}

int main() {
    printf("Enter # of threads to generate: ");
    int n;
    scanf("%d", &n);
    pthread_t* threads = malloc(n * sizeof(pthread_t));
    for (int i = 0; i < n; i++) {
        printf("Created Thread %d\n", i);
        pthread_create(threads + i, NULL, (void *) worker, i);
        pthread_join(threads[i], NULL);
    }
    free(threads);
    return 0;
}