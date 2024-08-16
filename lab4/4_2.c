#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int comparisons = 0;
int partitionScenario = 0; // 1 for best-case, -1 for worst-case

// Function to swap two elements
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Determine the partitioning scenario (best or worst case)
        int leftSize = pi - low;
        int rightSize = high - pi;
        if (leftSize == 0 || rightSize == 0) {
            partitionScenario = -1; // Worst-case scenario
        } else if (abs(leftSize - rightSize) <= (high - low) / 2) {
            partitionScenario = 1;  // Best-case scenario
        }

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to read data from file and return the number of elements
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

// Function to write sorted data to file
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

// Function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int choice;
    int arr[500]; // Array to hold input elements
    int n = 0;
    char inputFile[20], outputFile[20];

    while (1) {
        printf("MAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Ascending data
                strcpy(inputFile, "inAsce.dat");
                strcpy(outputFile, "outQuickAsce.dat");
                break;
            case 2:
                // Descending data
                strcpy(inputFile, "inDesc.dat");
                strcpy(outputFile, "outQuickDesc.dat");
                break;
            case 3:
                // Random data
                strcpy(inputFile, "inRand.dat");
                strcpy(outputFile, "outQuickRand.dat");
                break;
            case 4:
                // Exit
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid option. Try again.\n");
                continue;
        }

        // Read data from the selected file
        n = readFile(inputFile, arr);
        if (n == -1) {
            continue;
        }

        printf("Before Sorting:\n");
        printArray(arr, n);

        comparisons = 0;
        partitionScenario = 0;

        // Quick Sort
        quickSort(arr, 0, n - 1);

        printf("After Sorting:\n");
        printArray(arr, n);

        // Write the sorted data to the output file
        writeFile(outputFile, arr, n);

        printf("Number of Comparisons: %d\n", comparisons);

        // Output the partitioning scenario
        if (partitionScenario == 1) {
            printf("Partitioning Scenario: Best-case partitioning.\n");
        } else if (partitionScenario == -1) {
            printf("Partitioning Scenario: Worst-case partitioning.\n");
        } else {
            printf("Partitioning Scenario: Mixed partitioning.\n");
        }
    }

    return 0;
}
