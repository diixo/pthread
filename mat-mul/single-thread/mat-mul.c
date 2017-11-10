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

int main(int argc, const char* argv[]) {
    freopen("result.txt", "w", stdout);

    data_gen();

    struct timeval start,end;
    gettimeofday(&start,NULL);
    single_thread();
    gettimeofday(&end,NULL);
    double diff = (1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec)/1000.0;
    printf("single thread time consuming: %lf ms\n", diff);

    result_dump();

    fclose(stdout);
    return 0;
}
