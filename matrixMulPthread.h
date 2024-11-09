#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Size of the matrices
//#define N 10 
//#define N 20 
//#define N 30 
#define N 1000 

//Create custom ThreadData object
typedef struct {
    int start_row;
    int end_row;
    int **A;
    int **B;
    int **C;
} ThreadData;

void displayMatrix(int** matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void* matrixMultiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int start_row = data->start_row;
    int end_row = data->end_row;
    int **A = data->A;
    int **B = data->B;
    int **C = data->C;

   
   for (int x = start_row; x < end_row; ++x){ //iterate through row x in A and C
    for (int i = 0; i < N; ++i) { 
         int tempC = 0; //temp variable to hold value for C
        for (int j = 0; j < N; ++j) { 
            tempC += A[j][x] * B [i][j]; // iterate through row x column j of A and column i row j of B.
        }
        C [i][x] = tempC; // fill in element in matrix C  
        tempC = 0;
        }
    }
    pthread_exit(NULL);
   
}