#include <stdio.h>

#define N 50
#define NUM_THREADS 16

double A[N], B[N];
double dot_product = 0;

// Function to compute dot product sequentially
double sequential_dot_product() {
    double result = 0;
    int i;
    for (i = 0; i < N; i++) {
        result += A[i] * B[i];
    }
    return result;
}

int main() {
    int i;

    // Initialize input vectors
    for (i = 0; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
    }

    // Compute dot product using OpenMP parallelism
    #pragma omp parallel for reduction(+:dot_product) num_threads(NUM_THREADS)
    for (i = 0; i < N; i++) {
        dot_product += A[i] * B[i];
    }

    // Output result
    printf("Dot product (parallel): %f\n", dot_product);
    
    // Compute dot product sequentially
    double sequential_result = sequential_dot_product();

    // Output sequential result
    printf("Dot product (sequential): %f\n", sequential_result);

    // Compare results
    if (dot_product == sequential_result) {
        printf("Results match!\n");
    } else {
        printf("Results do not match!\n");
    }

    return 0;
}


