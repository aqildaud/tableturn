#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// limit words allowed
#define MAX_PERMUTATION 362880

void swap(char **a, char **b) {
    char *t = *a;
    *a = *b;
    *b = t;
}

void permute(char **a, int l, int r, char ***s, int *count) {
    if (l == r) {
        if (*count >= MAX_PERMUTATION) {
            fprintf(stderr, "The sentence given has exceeded the limit of permutation allowed");
            exit(EXIT_FAILURE);
        }

        // store the current permutation in s
        (*s) = realloc(*s, (*count + 1) * sizeof(char *));
        if (*s == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        (*s)[*count] = (char *)malloc(1024);  // allocate memory for the sentence
        if ((*s)[*count] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        (*s)[*count][0] = '\0';  // initialize the string

        for (int i = 0; i <= r; i++) {
            strcat((*s)[*count], a[i]);
            strcat((*s)[*count], " ");
        }
        (*s)[*count][strlen((*s)[*count]) - 1] = '\0';
        (*count)++;
    } else {
        for (int i = l; i <= r; i++) {
            swap(&a[l], &a[i]);
            permute(a, l + 1, r, s, count);
            swap(&a[l], &a[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Improper input. Exit\n");
        return 1;
    }

    char **strings = NULL;
    const char d[] = " ";
    char *token;
    int current_size = 0;

    token = strtok(argv[1], d);

    while( token != NULL ) {
        strings = realloc(strings, (current_size + 1) * sizeof(char *));
        strings[current_size] = strdup(token);
        current_size++;
        token = strtok(NULL, d);
    }

    char **p = NULL;
    int permutation_count = 0;

    if (current_size > 0) {
        // generate all permutations
        permute(strings, 0, current_size - 1, &p, &permutation_count);
    }
    // to prevent sequence repetition between runs 
    srand(time(NULL));

    int r = rand() % permutation_count;

    // print the randomly picked permutation
    printf("%s\n", p[r]);

    for (int i = 0; i < current_size; i++) {
        free(strings[i]);
    }
    free(strings);

    for (int i = 0; i < permutation_count; i++) {
        free(p[i]);
    }
    free(p);

    return 0;
}
