// 8.1 Aim of the program: Write a program to implement the matrix chain multiplication problem
// using M-table &amp; S-table to find optimal parenthesization of a matrix-chain product. Print the
// number of scalar multiplications required for the given input.
// Note# Dimensions of the matrices can be inputted as row and column values. Validate the
// dimension compatibility.
// Input:
// Enter number of matrices: 4
// Enter row and col size of A1: 30 35
// Enter row and col size of A2: 35 15
// Enter row and col size of A3: 15 5
// Enter row and col size of A4: 5 10
// Output:
// M Table:
// 0 15750 7875 9375
// 0 0 2625 4375
// 0 0 0 750
// 0 0 0 0
// S Table:
// 0 1 1 3
// 0 0 2 3
// 0 0 0 3
// 0 0 0 0
// Optimal parenthesization: ( ( A1 (A2 A3)) A4)
// The optimal ordering of the given matrices requires 9375 scalar multiplications.

#include <stdio.h>
#include <limits.h>

#define MAX_MATRICES 100  // Define a maximum number of matrices

// Function to take input dimensions of the matrices and validate them
int inputDimensions(int num_matrices, int dimensions[MAX_MATRICES + 1]) {
    int rows, cols;
    
    for (int i = 0; i < num_matrices; i++) {
        printf("Enter row and col size of A%d: ", i + 1);
        scanf("%d %d", &rows, &cols);
        
        if (i == 0) {
            // For the first matrix, set the first row and column
            dimensions[i] = rows;       // Set row of A1
        } else {
            // Check if previous matrix's columns match current matrix's rows
            if (dimensions[i] != rows) {
                printf("Dimension mismatch: Column of matrix A%d does not match row of matrix A%d.\n", i, i + 1);
                return 0;  // Return 0 if there's an incompatibility
            }
        }
        
        dimensions[i + 1] = cols;  // Set the column of each matrix
    }
    
    return 1;  // Return 1 if all dimensions are compatible
}

// Function to calculate the M and S tables for matrix chain multiplication
void matrix_chain_order(int p[], int n, int M[MAX_MATRICES][MAX_MATRICES], int S[MAX_MATRICES][MAX_MATRICES]) {
    for (int i = 0; i < n; i++) {
        M[i][i] = 0;
    }
    for (int l = 2; l <= n; l++) {  // l is the chain length
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            M[i][j] = INT_MAX;  // Initialize to a large number
            for (int k = i; k < j; k++) {
                int q = M[i][k] + M[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < M[i][j]) {
                    M[i][j] = q;
                    S[i][j] = k;  // Record the split point
                }
            }
        }
    }
}

// Function to print the M or S table
void printTable(int n, int table[MAX_MATRICES][MAX_MATRICES], const char *tableName) {
    printf("%s Table:\n", tableName);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (table[i][j] == INT_MAX) {
                printf("  INF  ");
            } else {
                printf("%7d ", table[i][j]);
            }
        }
        printf("\n");
    }
}

// Recursive function to print the optimal parenthesization
void printOptimalParenthesization(int S[MAX_MATRICES][MAX_MATRICES], int i, int j) {
    if (i == j) {
        printf("A%d", i + 1);
    } else {
        printf("(");
        printOptimalParenthesization(S, i, S[i][j]);
        printOptimalParenthesization(S, S[i][j] + 1, j);
        printf(")");
    }
}

// Function to display the optimal number of scalar multiplications and parenthesization
void displayResults(int num_matrices, int M[MAX_MATRICES][MAX_MATRICES], int S[MAX_MATRICES][MAX_MATRICES]) {
    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", M[0][num_matrices - 1]);
    printf("Optimal parenthesization: ");
    printOptimalParenthesization(S, 0, num_matrices - 1);
    printf("\n");
}

// Main function
int main() {
    int num_matrices;
    printf("Enter number of matrices (max %d): ", MAX_MATRICES);
    scanf("%d", &num_matrices);

    if (num_matrices < 1 || num_matrices > MAX_MATRICES) {
        printf("Error: Number of matrices must be between 1 and %d.\n", MAX_MATRICES);
        return 1;
    }

    int dimensions[MAX_MATRICES + 1];
    if (!inputDimensions(num_matrices, dimensions)) {
        return 1;
    }

    int M[MAX_MATRICES][MAX_MATRICES] = {0};  // M-table for scalar multiplications
    int S[MAX_MATRICES][MAX_MATRICES] = {0};  // S-table for optimal splits

    // Calculate M and S tables
    matrix_chain_order(dimensions, num_matrices, M, S);

    // Print M and S tables
    printTable(num_matrices, M, "M");
    printTable(num_matrices, S, "S");

    // Display results
    displayResults(num_matrices, M, S);

    return 0;
}

