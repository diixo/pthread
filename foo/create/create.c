#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#define MAX_NUM_WORKER 10

#define ERR_MSG(prefix, ...) {\
    fprintf(stderr, prefix " %lu out of %lu threads", __VA_ARGS__);\
}

typedef struct {
    unsigned long id;
} workerId_t;

void *worker(void *arg) {
    workerId_t* self = (workerId_t*)arg;
    char hello[100];
    int err = snprintf(hello, sizeof(hello), "[%lu]\t hello, world!\n", self->id);
    if(err < 0) {
        perror("snprintf");
        exit(errno);
    }
    puts(hello);
    return arg;
}

int main() {
    pthread_t worker_threads[MAX_NUM_WORKER];
    workerId_t worker_ids[MAX_NUM_WORKER];
    printf("[%s] creating worker threads...\n", __func__);
    for(unsigned long i=0; i<MAX_NUM_WORKER; ++i) {
        worker_ids[i].id = i;
        if( 0 != pthread_create(&worker_threads[i], NULL, worker, &worker_ids[i]) ) {
            ERR_MSG("couldn't create thread", i, MAX_NUM_WORKER);
            exit(errno);
        }
    }
    printf("[%s] joining worker threads...\n", __func__);
    for(unsigned long i=0; i<MAX_NUM_WORKER; ++i) {
        workerId_t *ret_val ;
        if(0 != pthread_join(worker_threads[i], (void**)&ret_val)) {
            ERR_MSG("couldn't join thread", i, MAX_NUM_WORKER);
        }
        else {
            printf("[%s]\tworker N.%lu has returned!\n", __func__, ret_val->id);
        }
    }
    return 0;
}
