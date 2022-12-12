#include <stdio.h>
#include <stdlib.h>

int bubblesort(int *arr, int n) {
    int i, j, temp;

    // Iterate through the array, swapping adjacent elements if they are in the wrong order
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Return the first element of the sorted array
    return arr[0];
}

int main(){
    FILE* fp = fopen("../inputs/input_10000.txt", "r");
    int n_inputs = 10000;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL) {
        printf("sorry :( \n");
        return -1;
    }

    int input[n_inputs];

    int i = 0;
    // needs i < n_inputs check
    while ((read = getline(&line, &len, fp)) != -1 && i < n_inputs) {
        input[i] = atoi(line);
        i++;
    }

    int res;
    i = 0;
    while (i < 1) {
        // needs array size 
        res = bubblesort(input, n_inputs);
        printf("%d\n", res);
        i++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    return 0;
}