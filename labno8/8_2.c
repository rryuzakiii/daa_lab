// Aim of the program: Write a program to find out the Longest Common Subsequence of two
// given strings. Calculate length of the LCS.
// Input:

// Enter the first string into an array: 10010101
// Enter the second string into an array: 010110110

// Output:
// LCS: 100110
// LCS Length: 6

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100 

void computeLCS(char *str1, char *str2, int lcs[MAX_LENGTH][MAX_LENGTH]) {
    int m = strlen(str1);
    int n = strlen(str2);

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                lcs[i][j] = 0; 
            } else if (str1[i - 1] == str2[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = (lcs[i - 1][j] > lcs[i][j - 1]) ? lcs[i - 1][j] : lcs[i][j - 1];
            }
        }
    }
}

void printLCS(char *str1, char *str2, int lcs[MAX_LENGTH][MAX_LENGTH]) {
    int i = strlen(str1);
    int j = strlen(str2);
    char lcsString[MAX_LENGTH];
    int index = lcs[i][j];

    lcsString[index] = '\0';

    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            lcsString[index - 1] = str1[i - 1];
            i--;
            j--;
            index--;
        } else if (lcs[i - 1][j] > lcs[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS: %s\n", lcsString);
printf("LCS Length: %d\n", lcs[strlen(str1)][strlen(str2)]);
}

int main() {
    char str1[MAX_LENGTH], str2[MAX_LENGTH];
    int lcs[MAX_LENGTH][MAX_LENGTH];

    printf("Enter the first string: ");
    scanf("%s", str1);
    printf("Enter the second string: ");
    scanf("%s", str2);

    computeLCS(str1, str2, lcs);

    
    printLCS(str1, str2, lcs);

    return 0;
}
