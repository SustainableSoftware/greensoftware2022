#include <stdio.h>
#include <stdlib.h>


// Define a structure for the linked list node
struct node {
    int data;
    struct node *next;
};

// Function prototypes
struct node *create_node(int data);
void insert_node(struct node **head, int data);
void print_list(struct node *head);
int bubble_sort(struct node *list, int n);


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

    struct node *input = NULL;

    int i = 0;
    // needs i < n_inputs check
    while ((read = getline(&line, &len, fp)) != -1 && i < n_inputs) {
        insert_node(&input, atoi(line));
        i++;
    }
    int res;
    i = 0;
    while (i < 1) {
        // needs array size 
        res = bubble_sort(input, n_inputs);
        printf("%d\n", res);
        i++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    return 0;
}


// Function to create a new node with the given data
struct node *create_node(int data) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a new node at the beginning of the list
void insert_node(struct node **head, int data) {
    struct node *new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}


// Function to sort a linked list using the bubble sort algorithm
int bubble_sort(struct node *list, int n) {
    int i, temp;
    struct node *p, *q;

    // Iterate through the list, swapping adjacent elements if they are in the wrong order
    for (i = 0; i < n - 1; i++) {
        p = list;
        q = p->next;
        while (q != NULL) {
            if (p->data > q->data) {
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
            p = p->next;
            q = p->next;
        }
    }

    // Return the first element of the sorted list
    return list->data;
}