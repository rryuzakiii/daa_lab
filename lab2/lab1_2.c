#include <stdio.h>

#define SIZE 5

int main() {
    int arr[SIZE] = {3, 4, 5, 1, 2};
    int prefixSum[SIZE];

    prefixSum[0] = arr[0];
    for (int i = 1; i < SIZE; i++) {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", prefixSum[i]);
    }
    printf("\n");

    return 0;
}
