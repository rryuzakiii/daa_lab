// Aim of the program: Write a menu driven program to sort a list of elements in ascending
// order using Quick Sort technique. Each choice for the input data has its own disc file. A separate
// output file can be used for sorted elements. After sorting display the content of the output file
// along with number of comparisons. Based on the partitioning position for each recursive call,
// conclude the input scenario is either best-case partitioning or worst-case partitioning.
// Note#
// ● The worst-case behavior for quicksort occurs when the partitioning routine produces one
// subproblem with n-1 elements and one with 0 elements. The best-case behaviour
// occurred in most even possible split, PARTITION produces two subproblems, each of
// size no more than n/2.

// ● Number of elements in each input file should vary from 300 to 500 entries.
// ● For ascending order: Read data from a file “inAsce.dat” having content 10 20 30 40…..,
// Store the result in “outQuickAsce.dat”.
// ● For descending order: Read data from a file “inDesc.dat” having content 90 80 70 60….,
// Store the result in “outQuickDesc.dat”.
// ● For random data: Read data from a file “inRand.dat” having content 55 66 33 11 44 …,
// Store the result in “outQuickRand.dat”
// Sample Input from file:
// MAIN MENU (QUICK SORT)
// 1. Ascending Data
// 2. Descending Data
// 3. Random Data
// 4. ERROR (EXIT)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int comparisons = 0;
int partitionScenario = 0; 


void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1); 

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


void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        int leftSize = pi - low;
        int rightSize = high - pi;
        if (leftSize == 0 || rightSize == 0) {
            partitionScenario = -1; 
        } else if (abs(leftSize - rightSize) <= (high - low) / 2) {
            partitionScenario = 1;  
        }

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
        printf("MAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                
                strcpy(inputFile, "inAsce.dat");
                strcpy(outputFile, "outQuickAsce.dat");
                break;
            case 2:
                
                strcpy(inputFile, "inDesc.dat");
                strcpy(outputFile, "outQuickDesc.dat");
                break;
            case 3:
                
                strcpy(inputFile, "inRand.dat");
                strcpy(outputFile, "outQuickRand.dat");
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
        partitionScenario = 0;

        
        quickSort(arr, 0, n - 1);

        printf("After Sorting:\n");
        printArray(arr, n);

        
        writeFile(outputFile, arr, n);

        printf("Number of Comparisons: %d\n", comparisons);

        
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
