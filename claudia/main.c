#include <stdio.h>
#include <stdlib.h>


void swap(int* j, int* next_j){
    int temp = *j;
    *j=*next_j;
    *next_j=temp;
}

int bubblesort(int* input, int size) {
    int min;

	for (int i = 0; i < (size - 1); i++)
	{
		for (int j = 0; j < (size - i - 1); j++)
		{
            //swap
			if(input[j] > input[j+1]){
                swap(&input[j], &input[j+1]);
            } 
        }
    }

    min = input[0];
    
    return min;
}



int main(){
    FILE* fp = fopen("input_1000.txt", "r");
    int n_inputs = 10;
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


