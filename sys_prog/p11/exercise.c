#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 100

typedef struct {
    int *vector;
    int *matrix;
    int *result;
    int row;
    int n;
} thread_data_t;

void *matrix_vector_mult(void *arg) {
    thread_data_t *data = (thread_data_t *) arg;
    int *vector = data->vector;
    int *matrix = data->matrix;
    int *result = data->result;
    int row = data->row;
    int n = data->n;

    int dot_product = 0;
    for (int j = 0; j < n; j++) {
        dot_product += matrix[row * n + j] * vector[j];
    }
    result[row] = dot_product;

    pthread_exit(NULL);
}

int main(int argc, char **argv) {

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    int *vector = malloc(n * sizeof(int));
    int *matrix = malloc(m * n * sizeof(int));
    int *result = malloc(m * sizeof(int));

    srand(time(NULL));

    // Initialize vector and matrix with random values
    for (int i = 0; i < n; i++) {
        vector[i] = rand() % 10;
    }
    for (int i = 0; i < m * n; i++) {
        matrix[i] = rand() % 10;
    }

    // Create threads and assign each thread to a row of the matrix
    pthread_t threads[m];
    thread_data_t thread_data[m];
    for (int i = 0; i < m; i++) {
        thread_data[i].vector = vector;
        thread_data[i].matrix = matrix;
        thread_data[i].result = result;
        thread_data[i].row = i;
        thread_data[i].n = n;
        pthread_create(&threads[i], NULL, matrix_vector_mult, (void *) &thread_data[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < m; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result
    printf(" *** Matrix ***\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("[ %d ] ", matrix[i * n + j]);
        }
        printf("\n");
    }
    printf(" *** Vector ***\n");
    for (int i = 0; i < n; i++) {
        printf("[ %d ]\n", vector[i]);
    }
    printf("\n *** Result ***\n");
    for (int i = 0; i < m; i++){
        printf("[ %d ]\n", result[i]);
    }
}
