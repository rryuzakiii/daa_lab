// Aim of the program: Write a menu driven program to sort list of array elements using Merge
// Sort technique and calculate the execution time only to sort the elements. Count the number of
// comparisons.
// Note#
// ● To calculate execution time, assume that single program is under execution in the CPU.
// ● Number of elements in each input file should vary from 300 to 500 entries.
// ● For ascending order: Read data from a file “inAsce.dat” having content 10 20 30 40…..,
// Store the result in “outMergeAsce.dat”.
// ● For descending order: Read data from a file “inDesc.dat” having content 90 80 70 60….,
// Store the result in “outMergeDesc.dat”.
// ● For random data: Read data from a file “inRand.dat” having content 55 66 33 11 44 …,
// Store the result in “outMergeRand.dat”

// Sample Input from file:
// MAIN MENU (MERGE SORT)
// 1. Ascending Data
// 2. Descending Data
// 3. Random Data
// 4. ERROR (EXIT)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int comparisons = 0;


void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


int readFile(const char* filename, int arr[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return -1;
    }

    int n = 0;
    while (fscanf(file, "%d", &arr[n]) != EOF) {
        n++;
    }

    fclose(file);
    return n;
}


void writeFile(const char* filename, int arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}


void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int choice;
    int arr[500]; 
    int n = 0;
    char inputFile[20], outputFile[20];

    while (1) {
        printf("MAIN MENU (MERGE SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:

                strcpy(inputFile, "inAsce.dat");
                strcpy(outputFile, "outmergeAsce.dat");
                break;
            case 2:

                strcpy(inputFile, "inDesc.dat");
                strcpy(outputFile, "outMergeDesc.dat");
                break;
            case 3:

                strcpy(inputFile, "inRand.dat");
                strcpy(outputFile, "outMergeRand.dat");
                break;
            case 4:
        
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid option. Try again.\n");
                continue;
        }

        
        n = readFile(inputFile, arr);
        if (n == -1) {
            continue;
        }

        printf("Before Sorting:\n");
        printArray(arr, n);

        comparisons = 0;

        
        clock_t start, end;
        start = clock();
        
        mergeSort(arr, 0, n - 1);

        end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000000; // nanoseconds

        printf("After Sorting:\n");
        printArray(arr, n);

        writeFile(outputFile, arr, n);

        printf("Number of Comparisons: %d\n", comparisons);
        printf("Execution Time: %.0f nanoseconds\n", time_taken);
    }

    return 0;
}
