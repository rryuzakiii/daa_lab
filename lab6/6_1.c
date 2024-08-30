#include <stdio.h>

#define MAX_ITEMS 100

typedef struct {
    int item_id;
    int item_profit;
    int item_weight;
    float profit_weight_ratio;
    float amount_taken;
} ITEM;

void swap(ITEM* a, ITEM* b) {
    ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(ITEM arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(ITEM arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

float fractionalKnapsack(ITEM items[], int n, int capacity) {
    float max_profit = 0.0;
    int current_capacity = 0;

    for (int i = 0; i < n; i++) {
        if (current_capacity + items[i].item_weight <= capacity) {
            items[i].amount_taken = 1.0;
            current_capacity += items[i].item_weight;
            max_profit += items[i].item_profit;
        } else {
            items[i].amount_taken = (float)(capacity - current_capacity) / items[i].item_weight;
            max_profit += items[i].item_profit * items[i].amount_taken;
            break;
        }
    }

    return max_profit;
}

int main() {
    ITEM items[MAX_ITEMS];
    int n, capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%d %d", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = (float)items[i].item_profit / items[i].item_weight;
        items[i].amount_taken = 0.0;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%d", &capacity);

    heapSort(items, n);

    float max_profit = fractionalKnapsack(items, n, capacity);

    printf("Item No profit Weight Amount to be taken\n");
    for (int i = 0; i < n; i++) {
        printf("%d %.6f %.6f %.6f\n", items[i].item_id, (float)items[i].item_profit, 
               (float)items[i].item_weight, items[i].amount_taken);
    }
    printf("Maximum profit: %.6f\n", max_profit);

    return 0;
}
