#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100000

int match_clockwise_array(int snowflake1[], int snowflake2[], int startIndex) {

    int offset;

    // snowflakes can only have 6 sides
    for (offset = 0; offset < 6; offset++) {

        if (snowflake1[offset] != snowflake2[(startIndex + offset) % 6 ] ) {
            return 0;
        }

    }

    return 1;

}

int match_counterclockwise_array(int snowflake1[], int snowflake2[], int startIndex) {

    int offset, snowflake2Index;

    snowflake2Index = (startIndex + offset) % 6;

    if (snowflake2Index < 0) {
        snowflake2Index = snowflake2Index + 6;
    }

    // snowflakes can only have 6 sides
    for (offset = 0; offset < 6; offset++) {

        if (snowflake1[offset] != snowflake2[ snowflake2Index ] ) {
            return 0;
        }
    }

    return 1;

}

int match_test(int snowflake1[], int snowflake2[]) {
    int startIndex;

    for (startIndex = 0; startIndex < 6; startIndex++) {

        if (match_clockwise_array(snowflake1, snowflake2, startIndex)) {
            return 1;
        }

        if (match_counterclockwise_array(snowflake1, snowflake2, startIndex)) {
            return 1;
        }


    }

    return 0;
}

int scan_snowflakes(int snowflakes[][6], int numberOfSnowflakes) {

    int snowflake1, snowflake2;

    for (snowflake1 = 0; snowflake1 < numberOfSnowflakes; snowflake1 ++) {

        for (snowflake2 = snowflake1+1; snowflake2 < numberOfSnowflakes; snowflake2++) {

            if (match_test(snowflakes[snowflake1], snowflakes[snowflake2])) {
                return 1;
            }

        }

    }

    return 0;

}


int main(void) {
    
    //CREATE 2-DIM ARRAY OF SNOWFLAKES FROM INPUT
    // SIZE rows of 6 columns
    static int snowflakes[SIZE][6];
    int numberOfSnowflakes, row, snowflakeLeg;
    
    scanf("%d", &numberOfSnowflakes);
    
    // read each row of input
    for (row = 0; row < numberOfSnowflakes; row++) {
        
        // read each column of data
        for (snowflakeLeg = 0; snowflakeLeg < 6; snowflakeLeg ++) {
            scanf("%d", &snowflakes[row][snowflakeLeg]);
        }

    }

    if (scan_snowflakes(snowflakes, numberOfSnowflakes)) {
        printf("Twin snowflakes found");
    } else {
        printf("No twin snowflakes found");
    }

    return 0;
}