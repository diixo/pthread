#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int count;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
void* thread_func(void *arg) {
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    int n, nMax;
    nMax = (int)arg;
    int i;
    for(i=0; i<nMax; ++i) {
        n = rand() % nMax;
        pthread_mutex_lock(&count_mutex);
        for(count=0; count<n; ++count) {
            printf("loop %d: xxxx\n", count);
        }
        pthread_mutex_unlock(&count_mutex);
    }
    return NULL;
}
int main() {
    pthread_t thread1;
    pthread_t thread2;
    printf("++++++++++++++++++++++++++++++++++\n");
    pthread_create(&thread1, NULL, thread_func, (void*)21);
    pthread_create(&thread2, NULL, thread_func, (void*)14);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
