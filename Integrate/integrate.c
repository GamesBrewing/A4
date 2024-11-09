#include <stdio.h>
#include <omp.h>

#define N 1000000000 // intervals


double f(double x) {
    return 4.0 / (1.0 + x * x); // Function to integrate
}

double trapezoidalRule() {
    double h = 1.0 / N; 
    double sum = 0.5 * (f(0) + f(1)); 

    //Sum all threads at the end
    #pragma omp parallel for reduction(+:sum)

    for (int i = 1; i < N; ++i) {
        sum += f(i * h);
    }
    sum *= h; 
    return sum;
}

int main() {

    // Set the number of threads
  //omp_set_num_threads(1);
  //omp_set_num_threads(2);
  //omp_set_num_threads(5);
  //omp_set_num_threads(7);
  omp_set_num_threads(9);


    double pi = trapezoidalRule();
    printf("Estimated value of π: %f\n", pi);
    return 0;
}
