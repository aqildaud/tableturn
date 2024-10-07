#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void swap(char **a, char **b) {
    char *t = *a;
    *a = *b;
    *b = t;
}

// shuffle
void turntable(char **a, int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&a[i], &a[j]);
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
    
    clock_t start_time = clock();
    turntable(strings, current_size);
   
    printf("\n"); 
    for (int i = 0; i < current_size; i++) {
        printf("%s ", strings[i]);
    }
    printf("\n\n");
    clock_t end_time = clock();

    double time_taken = ((double) end_time - start_time) / CLOCKS_PER_SEC;
    printf("Executed in %f seconds...\n", time_taken);

    for (int i = 0; i < current_size; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}
