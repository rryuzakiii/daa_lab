#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    FILE *sourceFile, *destFile;
    int num1, num2;
    
    sourceFile = fopen(argv[1], "r");
    if (sourceFile == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    destFile = fopen(argv[2], "w");
    if (destFile == NULL) {
        printf("Error opening destination file.\n");
        fclose(sourceFile);
        return 1;
    }

    while (fscanf(sourceFile, "%d %d", &num1, &num2) == 2) {
        int result = gcd(num1, num2);
        fprintf(destFile, "GCD of %d and %d is %d\n", num1, num2, result);
    }

    
    fclose(sourceFile);
    fclose(destFile);

    printf("GCD calculations completed. Check the destination file.\n");
    
    return 0;
}