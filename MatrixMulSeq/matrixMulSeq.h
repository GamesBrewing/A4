#include <stdio.h>
#include <stdlib.h>

// Size of the matrices
//#define N 10 
//#define N 20 
//#define N 30 
#define N 1000 


void displayMatrix(int** matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrixMultiply(int** A, int** B, int** C) {
   //int colC = 0; //colC = column number for matrix C
   for (int x = 0; x < N; ++x){ //iterate through row x in A and C
    for (int i = 0; i < N; ++i) { 
        int tempC=0;
        for (int j = 0; j < N; ++j) { 
            tempC += A[j][x] * B [i][j]; // iterate through row x column j of A and column i row j of B.
        }
        //C [colC++][x] = tempC; // fill in element in matrix C  
        C [i][x] = tempC; // fill in element in matrix C  
        tempC = 0;
        
    }
    //colC = 0;
   }
}