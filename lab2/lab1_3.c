#include <stdio.h>
#include <stdlib.h>

#define FILENAME "input.txt"

int findMostRepeatingElement(int arr[], int n) {
    int maxCount = 0;
    int mostRepeatingElement = arr[0];

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] == arr[i]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mostRepeatingElement = arr[i];
        }
    }
    return mostRepeatingElement;
}

int main() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0) {
        printf("Invalid array size.\n");
        fclose(file);
        return 1;
    }

    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    printf("The content of the array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int totalDuplicates = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                totalDuplicates++;
                break;
            }
        }
    }

    int mostRepeatingElement = findMostRepeatingElement(arr, n);

    printf("Total number of duplicate values = %d\n", totalDuplicates);
    printf("The most repeating element in the array = %d\n", mostRepeatingElement);

    free(arr);
    return 0;
}
