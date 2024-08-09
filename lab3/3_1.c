#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int num, FILE *destFile) {
    if (num > 1) {
        decimalToBinary(num / 2, destFile);
    }
    fprintf(destFile, "%d", num % 2);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <source file> <destination file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("The value of 'n' must be a positive integer.\n");
        return 1;
    }

    FILE *sourceFile, *destFile;
    int num;
    int count = 0;

    sourceFile = fopen(argv[2], "r");
    if (sourceFile == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    destFile = fopen(argv[3], "w");
    if (destFile == NULL) {
        printf("Error opening destination file.\n");
        fclose(sourceFile);
        return 1;
    }

    while (fscanf(sourceFile, "%d", &num) == 1 && count < n) {
        fprintf(destFile, "Decimal: %d, Binary: ", num);
        decimalToBinary(num, destFile);
        fprintf(destFile, "\n");
        count++;
    }

    fclose(sourceFile);
    fclose(destFile);

    destFile = fopen(argv[3], "r");
    if (destFile == NULL) {
        printf("Error reopening destination file for reading.\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), destFile)) {
        printf("%s", line);
    }

    fclose(destFile);

    return 0;
}
