#include <stdio.h>

void EXCHANGE(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int *arr, int p2) {
    if (p2 <= 1) return;
    
    EXCHANGE(&arr[0], &arr[p2 - 1]);

    for (int i = p2 - 1; i > 1; i--) {
        EXCHANGE(&arr[i], &arr[i - 1]);
    }
}

int main() {
    int arr[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    int size = sizeof(arr) / sizeof(arr[0]);
    int p2 = 5;

    printf("Before ROTATE: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    ROTATE_RIGHT(arr, p2);

    printf("After ROTATE: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
