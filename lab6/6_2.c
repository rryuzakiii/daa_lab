#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char alphabet;
    int frequency;
} SYMBOL;

typedef struct HuffmanNode {
    SYMBOL symbol;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef struct {
    int size;
    HuffmanNode **array;
} MinHeap;

MinHeap* createMinHeap(int capacity);
HuffmanNode* newNode(SYMBOL symbol);
void swapMinHeapNode(HuffmanNode **a, HuffmanNode **b);
void minHeapify(MinHeap *minHeap, int idx);
void insertMinHeap(MinHeap *minHeap, HuffmanNode *node);
HuffmanNode* extractMin(MinHeap *minHeap);
void buildHuffmanTree(SYMBOL symbols[], int size);
void printCodes(HuffmanNode *root, int arr[], int top);

MinHeap* createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->array = (HuffmanNode**)malloc(capacity * sizeof(HuffmanNode*));
    return minHeap;
}

HuffmanNode* newNode(SYMBOL symbol) {
    HuffmanNode *node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->symbol = symbol;
    node->left = node->right = NULL;
    return node;
}

void swapMinHeapNode(HuffmanNode **a, HuffmanNode **b) {
    HuffmanNode *temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->symbol.frequency < minHeap->array[smallest]->symbol.frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->symbol.frequency < minHeap->array[smallest]->symbol.frequency)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

void insertMinHeap(MinHeap *minHeap, HuffmanNode *node) {
    int i = minHeap->size++;
    while (i && node->symbol.frequency < minHeap->array[(i - 1) / 2]->symbol.frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

HuffmanNode* extractMin(MinHeap *minHeap) {
    HuffmanNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

void buildHuffmanTree(SYMBOL symbols[], int size) {
    MinHeap *minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i) {
        HuffmanNode *node = newNode(symbols[i]);
        insertMinHeap(minHeap, node);
    }

    while (minHeap->size > 1) {
        HuffmanNode *left = extractMin(minHeap);
        HuffmanNode *right = extractMin(minHeap);

        SYMBOL sum;
        sum.alphabet = '$';
        sum.frequency = left->symbol.frequency + right->symbol.frequency;

        HuffmanNode *top = newNode(sum);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    HuffmanNode *root = extractMin(minHeap);

    int arr[100], top = 0;
    printCodes(root, arr, top);
}

void printCodes(HuffmanNode *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        printf("%c: ", root->symbol.alphabet);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

int main() {
    SYMBOL symbols[] = {
        {'a', 5},
        {'b', 9},
        {'c', 12},
        {'d', 13},
        {'e', 16},
        {'f', 45}
    };
    int size = sizeof(symbols) / sizeof(symbols[0]);

    buildHuffmanTree(symbols, size);

    return 0;
}
