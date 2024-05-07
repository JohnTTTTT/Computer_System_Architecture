//John Turnbull
//20235355

#include <stdio.h>
#include <omp.h>

// We will be changing these variables frequently to evaluate the functionality
#define N 128000000
#define NUM_THREADS 32

double A[N], B[N];
double dot_product = 0;

// Sequential dot product function
double sequential_dot_product() {
    double sum = 0;
    int i;
    for (i = 0; i < N; i++) {
        sum += A[i] * B[i];
    }
    return sum;
}

int main() {
    int i;
    double start, end;

    // Initialize input vectors
    for (i = 0; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
    }

    // Start execution time
    start = omp_get_wtime();

    // Compute dot product using parallel for with a reduction, also set number of threads
    #pragma omp parallel for reduction(+:dot_product) num_threads(NUM_THREADS)
    for (i = 0; i < N; i++) {
        dot_product += A[i] * B[i];
    }

    // End execution time
    end = omp_get_wtime();

    // Output execution time excluding sequential
    printf("Parallel execution time: %f seconds\n", end - start);

    // Compute dot product sequentially
    double sequential_result;
    sequential_result = sequential_dot_product();

    // Output the results of the dot product
    printf("Parallel DP: %f\n", dot_product);
    printf("Sequential DP: %f\n", sequential_result);

    // Check if results match, output to the console accordingly
    if (dot_product == sequential_result) 
        printf("Correct results\n");
    else 
        printf("Incorrect results\n");

    return 0;
}
