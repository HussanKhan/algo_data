#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000000 // max string size



// INPUT
// abcdxxxef
// adcdxxef


// ALWAYS OFF BY 1 CHAR
// OUTPUT
// 3 - HOW MANY DIFF CHARS CAN YOU DELETE
// 5 6 7 - WHAT ARE THE INDEXES

// Returns index of where matching stops
int longest_prefix(char string_typo[], char string_correct[]) {

    int i = 0;
    int match = 0;
    while (string_typo[i] == string_correct[i]) {
        i++;
        match++;
    }

    // since we i++, we have to go 1 back
    return match-1;

}

// returns index of where matching from right stops
int longest_suffix(char string_typo[], char string_correct[]) {

    int length = strlen(string_typo);
    int i = length;
    int match = 0;
    while (string_typo[i] == string_correct[i-1]) {
        i--;
        match++;
    }

    return match;

}

int main(void) {

    static char string_typo[SIZE], string_correct[SIZE];
    int length, prefix_index, suffix_index, total, i;

    // GET INPUT
    gets(string_typo);
    gets(string_correct);

    // parse info
    length = strlen(string_typo);
    prefix_index = longest_prefix(string_typo, string_correct);
    suffix_index = longest_suffix(string_typo, string_correct);

    total = (prefix_index + 1) - (length - suffix_index) + 1;

    printf("\n%s\n", string_typo);
    printf("%s\n", string_correct);
    printf("\n%d\n", total);
    for (i = 0; i < total; i++) {

        // start printing from lower bound
        printf("%d", i + (length - suffix_index));

        if (i < total) {
            printf(" ");
        } else {
            printf("\n");
        }

    }

    return 0;
}
