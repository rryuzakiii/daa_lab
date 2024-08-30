
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_PERSONS 100

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

void readData(struct person **persons, int *n);
void createMinHeap(struct person *persons, int n);
void createMaxHeap(struct person *persons, int n);
void displayYoungestWeight(struct person *persons, int n);
void insertMinHeap(struct person **persons, int *n);
void deleteOldestPerson(struct person *persons, int *n);
void swap(struct person *a, struct person *b);
void minHeapify(struct person *persons, int n, int i);
void maxHeapify(struct person *persons, int n, int i);
void printPersons(struct person *persons, int n);

int main() {
    struct person *persons = NULL;
    int n = 0;
    int choice;

    while (1) {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readData(&persons, &n);
                break;
            case 2:
                createMinHeap(persons, n);
                break;
            case 3:
                createMaxHeap(persons, n);
                break;
            case 4:
                displayYoungestWeight(persons, n);
                break;
            case 5:
                insertMinHeap(&persons, &n);
                break;
            case 6:
                deleteOldestPerson(persons, &n);
                break;
            case 7:
                free(persons);
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void readData(struct person **persons, int *n) {
    FILE *file = fopen("data.txt", "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    fscanf(file, "%d", n);
    *persons = (struct person *)malloc(*n * sizeof(struct person));

    for (int i = 0; i < *n; i++) {
        (*persons)[i].name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
        fscanf(file, "%d %s %d %d %d", &(*persons)[i].id, (*persons)[i].name, &(*persons)[i].age, &(*persons)[i].height, &(*persons)[i].weight);
    }
    fclose(file);
    printf("Data read successfully!\n");
}

void createMinHeap(struct person *persons, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(persons, n, i);
    }
    printf("Min-heap created based on age.\n");
}

void createMaxHeap(struct person *persons, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(persons, n, i);
    }
    printf("Max-heap created based on weight.\n");
}

void displayYoungestWeight(struct person *persons, int n) {
    if (n == 0) {
        printf("No persons in the list.\n");
        return;
    }

    int minAgeIndex = 0;
    for (int i = 1; i < n; i++) {
        if (persons[i].age < persons[minAgeIndex].age) {
            minAgeIndex = i;
        }
    }
    printf("Weight of the youngest person (%s): %d\n", persons[minAgeIndex].name, persons[minAgeIndex].weight);
}

void insertMinHeap(struct person **persons, int *n) {
    *persons = realloc(*persons, (*n + 1) * sizeof(struct person));
    struct person newPerson;
    newPerson.name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));

    printf("Enter ID, Name, Age, Height, Weight: ");
    scanf("%d %s %d %d %d", &newPerson.id, newPerson.name, &newPerson.age, &newPerson.height, &newPerson.weight);

    (*persons)[*n] = newPerson;
    (*n)++;

    for (int i = (*n / 2) - 1; i >= 0; i--) {
        minHeapify(*persons, *n, i);
    }
    printf("New person inserted into Min-heap.\n");
}

void deleteOldestPerson(struct person *persons, int *n) {
    if (*n == 0) {
        printf("No persons to delete.\n");
        return;
    }

    int maxAgeIndex = 0;
    for (int i = 1; i < *n; i++) {
        if (persons[i].age > persons[maxAgeIndex].age) {
            maxAgeIndex = i;
        }
    }

    printf("Deleting oldest person: %s (Age: %d)\n", persons[maxAgeIndex].name, persons[maxAgeIndex].age);
    free(persons[maxAgeIndex].name);

    for (int i = maxAgeIndex; i < *n - 1; i++) {
        persons[i] = persons[i + 1];
    }
    (*n)--;

    if (*n > 0) {
        for (int i = (*n / 2) - 1; i >= 0; i--) {
            minHeapify(persons, *n, i);
        }
    }
}

void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct person *persons, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && persons[left].age < persons[smallest].age) {
        smallest = left;
    }
    if (right < n && persons[right].age < persons[smallest].age) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&persons[i], &persons[smallest]);
        minHeapify(persons, n, smallest);
    }
}

void maxHeapify(struct person *persons, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && persons[left].weight > persons[largest].weight) {
        largest = left;
    }
    if (right < n && persons[right].weight > persons[largest].weight) {
        largest = right;
    }
    if (largest != i) {
        swap(&persons[i], &persons[largest]);
        maxHeapify(persons, n, largest);
    }
}

void printPersons(struct person *persons, int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Name: %s, Age: %d, Height: %d, Weight: %d\n", persons[i].id, persons[i].name, persons[i].age, persons[i].height, persons[i].weight);
    }
}
