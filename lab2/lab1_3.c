#include <stdio.h>
#include <stdlib.h>

void findDuplicatesAndMostRepeated(int arr[], int n) {
    int max_count = 0;
    int most_repeated_element = arr[0];
    int total_duplicates = 0;

    
    int *freq = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (freq[arr[i]] > 1) {
            total_duplicates++;
        }
        if (freq[arr[i]] > max_count) {
            max_count = freq[arr[i]];
            most_repeated_element = arr[i];
        }
    }
    printf("Total number of duplicate elements: %d\n", total_duplicates);
    printf("Most repeating element in the array: %d\n", most_repeated_element);

    free(freq);
}

int main() {
    FILE *fp;
    int n;
    
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fscanf(fp, "%d", &n);
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        return EXIT_FAILURE;
    }
    
    // Read the elements of the array
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    
    // Close the file
    fclose(fp);
    
    // Find duplicates and most repeating element
    findDuplicatesAndMostRepeated(arr, n);
    
    // Free dynamically allocated memory
    free(arr);
    
    return EXIT_SUCCESS;
}
