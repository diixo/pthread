#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

#define N 4096
double A[N][N];
double B[N][N];
double C[N][N];
int thread_count;

void single_thread() {
    int i, j, k;
    for(i=0; i<N; ++i) {
        for(j=0; j<N; ++j) {
            for(k=0; k<N; ++k) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}

void data_gen() {
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            A[i][j] = B[i][j] = 1.0+(i+1)/(j+1);
            C[i][j] = 0.0;
        }
    }
}

void result_dump() {
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            printf("%lf ", C[i][j]);
        }
        printf("\n");
    }
}

void* multi_thread(void* arg) {
    int blocks = N/thread_count;
    int start_row = ((int)arg)*blocks;
    int end_row = ((int)arg + 1)*blocks - 1;
    if(end_row >= N) end_row = N-1;

    for(int i=start_row; i<=end_row; ++i) {
        for(int j=0; j<N; ++j) {
            for(int k=0; k<N; ++k) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}

int main(int argc, const char* argv[]) {
    if( argc != 2 ) {
        printf("[usage] ./mat-mul thread_num\n");
        return -1;
    }

    thread_count = atoi(argv[1]);
    char file_name[20] = "dump-";
    char suffix[4];
    sprintf(suffix, "%d", thread_count);
    strcat(file_name, suffix);
    freopen(file_name, "w", stdout);

    data_gen();

    struct timeval start,end;
    gettimeofday(&start,NULL);
    //single_thread();
    //gettimeofday(&end,NULL);
    //double diff = (1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec)/1000.0;
    //printf("single thread time consuming: %lf ms\n", diff);
    
    pthread_t workers[thread_count];
    for(int i=0; i<thread_count; ++i) {
        if( 0 != pthread_create(&workers[i], NULL, multi_thread, (void*)i) ) exit(errno);
    }
    for(int j=0; j<thread_count; ++j) {
        if( 0 != pthread_join(workers[j], NULL) ) exit(errno);
    }
    gettimeofday(&end,NULL);
    double diff = (1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec)/1000.0;
    printf("multi-thread time consuming: %lf ms\n", diff);

    result_dump();

    fclose(stdout);
    return 0;
}
