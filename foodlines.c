#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100

// RETURNS INDEX OF SHORTEST LINE
int find_shortest_line(int lines[], int numberOfLines) {
    int currentIndex;
    int shortestLineIndex = 0;

    for ( currentIndex = 1; currentIndex < numberOfLines; currentIndex++ ) {

        if (lines[currentIndex] < lines[shortestLineIndex]) {
            shortestLineIndex = currentIndex;
        }

        return shortestLineIndex;
    }

    return 1;
}

// READS DATA FROM TEST CASES
void solve(int lines[], int numberOfLines, int numberOfNewPeople) {
    int i, shortest;
    for (i = 0; i < numberOfNewPeople; i++) {
        shortest = find_shortest_line(lines, numberOfLines);
        printf("%d\n", lines[shortest]);

        // INCREMENT NUMBER OF PEOPLE IN THE LINE
        // SINCE A PERSON HAS JOINED
        lines[shortest]++;
    }


}

// READ INPUT
int main(void) {

    int lines[MAX_LINES];
    int numberOfLines, numberOfNewPeople, i;

    // GET NUMBER OF LINES AND NUMBER OF NEW PEOPLE TO BE ADDED
    scanf("%d%d", &numberOfLines, &numberOfNewPeople);

    // GET NUMBER OF PEOPLE IN EACH LINES
    for (i = 0; i < numberOfLines; i++) {

        scanf("%d", &lines[i]);
    };

    solve(lines, numberOfLines, numberOfNewPeople);
    return 0;
}
