#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_BITS 17
#define WORD_LENGTH 16
#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

// given a list of string
// identify compound words

typedef struct word_node {
    char **word; // pointer to poitner
    struct word_node *next;
} word_node;

// https://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length
// returns pointer
// read word into array
char *read_line(int size) {
    char *str;
    int letter;
    int len = 0;
    str = malloc(size);

    if (str == NULL ) {
        fprintf(stderr, "memory error");
        exit(1);
    }

    // get char from input, keep going until EOL
    while ((letter = getchar()) != EOF && (letter != '\n')) {

        // returns len before incr
        str[len++] = letter;

        // if size of word gets too big, re-allocate mem
        if (len == size) {
            size = size * 2;
            str = realloc(str, size);
                if (str == NULL ) {
                    fprintf(stderr, "memory error");
                    exit(1);
                }
        };

    }
    str[len] = '\0'; //EOL
    return str;
}

unsigned long jenkins_one_at_a_time_hash(
    char *key, 
    unsigned long int length, 
    unsigned long bits) {

  unsigned long i, hash;

  for (hash = 0, i = 0; i < length; i++) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
  }

  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash & hashmask(bits);
}

// we hash the word, and see if it exists in the hashtable
int check_hash_table(word_node *hash_table[], char *wordToFind,
                  unsigned find_len) {

  unsigned wordHash;
  word_node *wordptr;
  
  wordHash = jenkins_one_at_a_time_hash(wordToFind, find_len, NUM_BITS);
  wordptr = hash_table[wordHash];

  // if linked list in hash table, just cycle through it
  while (wordptr) {

      // get value from value from pointer *(wordptr->word)
    if ((strlen(*(wordptr->word)) == find_len) &&
        (strncmp(*(wordptr->word), wordToFind, find_len) == 0)) {
            return 1;
        }
      
    wordptr = wordptr->next;
  }

  return 0;
}


// we slice the word and try to find every prefix and suffix pair
// if pair found, we have a compound word
void find_compound_words(char *words[],
                             word_node *hash_table[],
                             int total_words) {
  int i, j, prefix, suffix;
  unsigned len;

  for (i = 0; i < total_words; i++) {

    len = strlen(words[i]);

    for (j = 1; j < len; j++) {
      
      // what is going on here?
      // the first part
      prefix = check_hash_table(hash_table, words[i], j);

      // all strings in c are arrays, &words[i][j] - this means get word at index i, and start slice at index j, so we only read the suffix
      suffix = check_hash_table(hash_table, &words[i][j], len - j);
      
      // if we find a value for both prefix and suffix, we have found a compound words
      if (prefix && suffix) {

        printf("%s\n", words[i]);
        break; // no need to search any more

      }

    }

  }
}

// LOAD THE HASH TABLE
int main(void) {

    // OUR HASH FUNCTIONS NEED A LIST SIZE OF 2^2
    // SHIFT 1 TO THE RIGHT
    // we expect 120,000 word max, 2^17 is closest
    static char *words[1 << NUM_BITS] = {NULL};
    static word_node *hashmap[1 << NUM_BITS] = {NULL};
    int wordIndex = 0;
    char *inputWordPointer;
    word_node *nodePointer;
    unsigned length, wordHash;
    int counter = 0;
    int limit = 3;

    printf("Enter up to %d words\n", limit);


    // Load first word
    inputWordPointer = read_line(WORD_LENGTH);

    // Start a loop of reading all word inputs line by line
    // fill the hash map
    while (counter < limit) {
        
        // store word
        words[wordIndex] = inputWordPointer;

        // creating node
        nodePointer = malloc(sizeof(nodePointer));

        if (nodePointer == NULL ) {
            fprintf(stderr, "memory error");
            exit(1);
        };

        // hash word
        wordHash = jenkins_one_at_a_time_hash(inputWordPointer, strlen(inputWordPointer), NUM_BITS);

        // set word in node
        nodePointer->word = &words[wordIndex];

        // point to whatever is currently stored in hashmap, incase of linked list
        nodePointer->next = hashmap[wordHash]; // we're going to the front of the list
        hashmap[wordHash] = nodePointer; // set address of current node

        inputWordPointer = read_line(WORD_LENGTH);
        wordIndex++;
        counter++;
    }

    printf("\n----PROCESSING----\n");
    find_compound_words(words, hashmap, wordIndex);
    

    return 0;
}