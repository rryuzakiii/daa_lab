#include < stdio.h >
#include < stdlib.h >

void findSecondSmallestAndLargest(int arr[], int n) {
    if (n < 2) {
        printf("Array size must be at least 2 to find second smallest and second largest.\n");
        return;
    }
    qsort(arr, n, sizeof(int), compare);


    int second_smallest = arr[1];

    
    int second_largest = arr[n - 2];

    printf("Second smallest element: %d\n", second_smallest);
    printf("Second largest element: %d\n", second_largest);
}


int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    FILE *fp;
    int n;
    
    fp = fopen("file1.exe", "r");
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
    
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    
    fclose(fp);
    findSecondSmallestAndLargest(arr, n);
    free(arr);
    return EXIT_SUCCESS;
}
