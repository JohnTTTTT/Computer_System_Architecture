//John Turnbull
//20235355

#include <stdio.h>
#include <omp.h>

// We will be changing these variables frequently to evaluate the functionality
#define ROWS 400
#define COLS 400
#define NUM_THREADS 1

double A[ROWS][COLS], B[COLS], P_parallel[ROWS], P_sequential[ROWS];

// Initialization function for the input matrix and vector value
void initialize_input() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            A[i][j] = 1.0;
        }
        // I might change these variables as we go through and evaluate the functionality in part 2
        B[i] = 2.0;
    }
}

// Sequential matrix-vector multiplication function
void sequential_matrix_vector_mult() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        double dot_product = 0.0;
        for (j = 0; j < COLS; j++) {
            dot_product += A[i][j] * B[j];
        }
        P_sequential[i] = dot_product;
    }
}

void parallel_matrix_vector_mult(int start, int end) {
    int i, j;
    for (i = start; i < end; i++) {
        double dot_product = 0.0;
        for (j = 0; j < COLS; j++) {
            dot_product += A[i][j] * B[j];
        }
        P_parallel[i] = dot_product;
    }
}

int main() {
    int i, j;
    double start, end;

    initialize_input();

    // Start execution time
    start = omp_get_wtime();

    // Compute matrix-vector multiplication using parallel region, also set number of threads
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int thread_id = omp_get_thread_num();
        int chunk_size = ROWS / omp_get_num_threads();
        int start_thread = thread_id * chunk_size;
        int end_thread = (thread_id == omp_get_num_threads() - 1) ? ROWS : start_thread + chunk_size;
        parallel_matrix_vector_mult(start_thread, end_thread);
    }

    // End execution time
    end = omp_get_wtime();

    // Output execution time excluding sequential
    printf("Parallel execution time: %f seconds\n", end - start);

    // Compute matrix-vector multiplication sequentially
    sequential_matrix_vector_mult();

    // Compare results and output the mismatch index (if there are any)
    int mismatch_count = 0;
    for (i = 0; i < ROWS; i++) {
        if (P_parallel[i] != P_sequential[i]) {
            printf("Mismatch at index %d: parallel=%f, sequential=%f\n", i, P_parallel[i], P_sequential[i]);
            mismatch_count++;
        }
    }

    // Check if results match, output to the console accordingly
    if (mismatch_count == 0) 
        printf("Correct results\n");
      else 
        printf("Incorrect results. Total mismatches: %d\n", mismatch_count);

    return 0;
}


