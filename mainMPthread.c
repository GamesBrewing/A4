#include "matrixMulPthread.h"


// number of threads
//#define NUM_THREADS 1
//#define     NUM_THREADS 2
//#define     NUM_THREADS 5
//#define     NUM_THREADS 7
#define     NUM_THREADS 9





// Need to allocate the memory for the matrix when compiling, otherwise I get a segmentation fault. I think it is caused by stack overload.
int ** allocateMatrix ( int n){  
    int** matrix = (int**)malloc(n* sizeof(int*));
    for (int i =0; i < n; ++i){
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

//free the allocated memory.
void freeMatrix (int ** matrix, int n){
    for (int i =0; i < n; ++i){
        free(matrix[i]);
    }
    free(matrix);
}

int main() {


  // Allocation of matrices
    int** A = allocateMatrix(N);
    int** B = allocateMatrix(N);
    int** C = allocateMatrix(N);

    printf("Matrices allocated successfully.\n");

    // Initialize matrices A and B
    for (int i = 0; i < N; ++i) {  //column
        for (int j = 0; j < N; ++j) {  //row
            A[i][j] = 1; 
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    printf("Matrices initialized successfully.\n");

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int rows_per_thread = N / NUM_THREADS;

    //Create the threads
    for (int i=0; i< NUM_THREADS; ++i){
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i + 1) * rows_per_thread;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;

        //Have the last thread handle any extra work
        if (i == NUM_THREADS -1){ 
            thread_data[i].end_row = N;
        }
        pthread_create(&threads[i], NULL, matrixMultiply, (void*)&thread_data[i]);
    }

    // Wait for the threads to complete
    for (int i = 0; i < NUM_THREADS; ++i){
        pthread_join(threads[i], NULL);
    }
    
    printf("Matrix multiplication complete!\n");

    // Display the resulting matrix C
    printf("Resulting Matrix C:\n");
    displayMatrix(C);
    
    //Free these matrices from memory
    freeMatrix(A,N);
    freeMatrix(B,N);
    freeMatrix(C,N);

    return 0;
}
