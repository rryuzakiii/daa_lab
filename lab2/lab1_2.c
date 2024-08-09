#include <stdio.h>

void computePrefixSum(int arr[], int prefixSum[], int N) {
    prefixSum[0] = arr[0]; // First element of prefix sum array is the same as arr[0]

    
    for (int i = 1; i < N; i++) {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int N = sizeof(arr) / sizeof(arr[0]);

    int prefixSum[N]; 
    computePrefixSum(arr, prefixSum, N);

    
    printf("Prefix sum array:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", prefixSum[i]);
    }
    printf("\n");

    return 0;
}
