#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100000


// SNOWFLAKE OBJECT for linked list
typedef struct snowflake_node {
    int snowflake[6];
    struct snowflake_node *next;
} snowflake_node;

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

int scan_snowflakes(snowflake_node *snowflakes[]) {

    int index;
    snowflake_node *node1, *node2;

    // Go through every entry in snowflakes hash table
    for (index = 0; index < SIZE; index++) {

        
        node1 = snowflakes[index];
        
        // We're comparing every snowflake in the bucket with each other
        // compare the first item to everyother item
        // then compare second item to every item after the first and itself
        // n(n-1)
        while (node1 != NULL) {

            
            node2 = node1->next;
            
            while (node2 != NULL) {
                
                if (match_test(node1->snowflake, node2->snowflake)) {
                    printf("Matching snowflakes found");
                    return 1;
                };

                node2 = node2->next;
            }
            
            node1 = node1->next;
        }
        
    }
    printf("No matching snowflakes found");
    return 0;

}

// returns sum of snowflake
int hashSnowflake(int snowflake[]) {
    int i;
    int hash = 0;

    for (i = 0; i < 6; i++) {
        hash = snowflake[i] + hash;
    };

    return hash % SIZE;
};




int main(void) {
    
    //CREATE 2-DIM ARRAY OF SNOWFLAKES FROM INPUT
    // SIZE rows of 6 columns
    static snowflake_node *snowflakes[SIZE] = {NULL};
    snowflake_node *snowflakePointer;
    int numberOfSnowflakes, row, snowflakeLeg, snowflakeHash;
    
    scanf("%d", &numberOfSnowflakes);
    
    // read each row of input
    for (row = 0; row < numberOfSnowflakes; row++) {

        // Allocate memory for snowflake from input
        // note the pointer is now pointing at a memory location
        snowflakePointer = malloc(sizeof(snowflake_node));

        // no memory
        if (snowflakePointer == NULL) {
            fprintf(stderr, "Memory error");
            exit(1);
        };

        // read each column of data
        for (snowflakeLeg = 0; snowflakeLeg < 6; snowflakeLeg++) {
            // loading data into struct snowflake var
            scanf("%d", &snowflakePointer->snowflake[snowflakeLeg]);
        };

        // sending snowflake array varible from struct to function
        snowflakeHash = hashSnowflake(snowflakePointer->snowflake);

        // Set pointer to what ever is stored at snowflakes[snowflakeHash]
        snowflakePointer->next = snowflakes[snowflakeHash];

        // Set snowflakes[snowflakeHash] to address of current node
        snowflakes[snowflakeHash] = snowflakePointer;

    }

    scan_snowflakes(snowflakes);

    return 0;
}