#include <stdio.h>
#include <stdlib.h>

int fileRows(FILE *fp)
{
    int count = 1;
    char c;

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count++;

    rewind(fp);

    return count;
}

// NOTE:: bubble sort font site: https://www.programiz.com/dsa/bubble-sort
// perform the optimized bubble sort
int optimizedBubbleSort(int *array, int size) {

  // loop to access each array element
  for (int step = 0; step < size - 1; ++step) {
    
    // check if swapping occurs  
    int swapped = 0;
    
    // loop to compare array elements
    for (int i = 0; i < size - step - 1; ++i) {
      
      // compare two array elements
      // change > to < to sort in descending order
      if (array[i] > array[i + 1]) {
        
        // swapping occurs if elements
        // are not in the intended order
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        
        swapped = 1;
      }
    }
    
    // no swapping means the array is already sorted
    // so no need for further comparison
    if (swapped == 0) {
      break;
    }
  }

  return array[0];
}

int main(int argc, char *argv[]) 
{
    FILE *fp = fopen(argv[1], "r");
    int n_inputs;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL)
    {
        printf("Error fp NULL!\n");
        return -1;
    }

    n_inputs = fileRows(fp);

    fseek(fp, 0, SEEK_SET);

    int input[n_inputs];
    int i = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        // put inputs on desired data structure
        input[i] = atoi(line);
        i++;
    }

    int res;
    i = 0;

    while (i < 100)
    {
        res = optimizedBubbleSort(input, n_inputs);
        printf("%d\n", res);
        i++;
    }

    fclose(fp);
    if (line)
    {
        free(line);
    }

    return 0;
}
