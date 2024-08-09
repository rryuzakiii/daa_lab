#include<stdio.h>
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
    
    findDuplicatesAndMostRepeated(arr, n);
    free(arr);
    
    return EXIT_SUCCESS;
}
