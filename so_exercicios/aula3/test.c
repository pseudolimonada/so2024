#include <stdio.h>
#include <string.h>

void replaceString(char *X, const char *S, const char *Y) {
    // Calculate lengths of the original string and the strings to be replaced and replacing with
    size_t lenX = strlen(X);
    size_t lenS = strlen(S);
    size_t lenY = strlen(Y);

    // Buffer to store the result with substituted strings
    char result[lenX + 1];  // +1 for the null terminator

    // Pointer to the current position in the original string
    char *currentPosition = X;

    // Pointer to the position in the result buffer
    char *resultPosition = result;

    // Loop until no more occurrences of S are found
    while ((currentPosition = strstr(currentPosition, S)) != NULL) {
        // Copy the portion of the original string before the occurrence of S
        size_t lenBefore = currentPosition - X;
        strncpy(resultPosition, X, lenBefore);
        resultPosition += lenBefore;

        // Copy the replacement string Y
        strcpy(resultPosition, Y);
        resultPosition += lenY;

        // Move the current position in the original string past the occurrence of S
        currentPosition += lenS;
        X = currentPosition;  // Update the pointer for the next iteration
    }

    // Copy the remaining portion of the original string after the last occurrence of S
    strcpy(resultPosition, X);

    // Copy the result back to the original string
    strcpy(X, result);
}

int main() {
    // Example usage
    char biggerString[100] = "This is a sample string. This is another sample string.";
    const char *stringToReplace = "sample";
    const char *replacementString = "example";

    printf("Original String: %s\n", biggerString);

    replaceString(biggerString, stringToReplace, replacementString);

    printf("Modified String: %s\n", biggerString);

    return 0;
}

