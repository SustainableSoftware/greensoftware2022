#include <stdio.h>
#include <stdlib.h>


int bubblesort(int* input) {
    int min = 0;

    // return lowest number
    return min;
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    int n_inputs = 10;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL) {
        return -1;
    }

    int input[n_inputs];

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        input[i] = atoi(line);
        
        // put inputs on desired data structure
        i++;
    }

    int res;
    i = 0;
    while (i < 100) {
        res = bubblesort(input);
        printf("%d\n", res);
        i++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    return 0;
}

