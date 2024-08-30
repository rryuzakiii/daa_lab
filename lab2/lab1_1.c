#include <stdio.h>
#include <limits.h>

#define FILENAME "input.txt"

void findSecondSmallestAndLargest(int arr[], int n, int *secondSmallest, int *secondLargest) {
    int smallest = INT_MAX, largest = INT_MIN;
    *secondSmallest = INT_MAX;
    *secondLargest = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] < smallest) {
            *secondSmallest = smallest;
            smallest = arr[i];
        } else if (arr[i] > smallest && arr[i] < *secondSmallest) {
            *secondSmallest = arr[i];
        }

        if (arr[i] > largest) {
            *secondLargest = largest;
            largest = arr[i];
        } else if (arr[i] < largest && arr[i] > *secondLargest) {
            *secondLargest = arr[i];
        }
    }
}

int main() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n < 2) {
        printf("Array should have at least 2 elements.\n");
        fclose(file);
        return 1;
    }

    int arr[n];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    int secondSmallest, secondLargest;
    findSecondSmallestAndLargest(arr, n, &secondSmallest, &secondLargest);

    if (secondSmallest == INT_MAX || secondLargest == INT_MIN) {
        printf("Not enough distinct elements to determine second smallest and second largest.\n");
    } else {
        printf("Second smallest element: %d\n", secondSmallest);
        printf("Second largest element: %d\n", secondLargest);
    }

    return 0;
}
