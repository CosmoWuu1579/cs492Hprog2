#include "dynamic.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"
#include <stdlib.h>
#include <math.h>
void printing(array_list* arr);
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of formats");
        return 1;
    }
    char* path = argv[1];
    FILE* f = fopen(path, "r");
    array_list *poop = parse_data(f);
    
    // printf("tesitng \n");
    // print_list(poop);
    //printing(poop);
    // int* input = malloc(sizeof(int) * 2);
    // int* output = malloc(sizeof(int));
    // input[0] = 0;
    // input[1] = 1;
    // evaluate_input(poop, input, output);
    // printf(" \n%d \n",output[0]);
    // free(input);
    // free(output);
    printing(poop);
    free_all(poop);
    free(poop);
    fclose(f);
}

int compare(const void* a, const void* b) {
    int x = ((node*) a) ->index;
    int y = ((node*) b) ->index;
    return (x > y) - (x < y); 
}
// Plan for evaluating:
// First, print out all the first row first and then store the indices so we know how to print
// Then, for the n input, make a for loop from 1 to 2^N and then just use bitmasking to go thru all of them
void printing(array_list* arr) {

    int* inputs = (int*) malloc((arr->total_input) * sizeof(int));
    int* outputs = (int*) malloc((arr->total_output) * sizeof(int));
    int index1 = 0;
    int index2 = 0;
    node* list = arr->data;
    qsort(list, arr->size, sizeof(node), compare);
    for (int i = 0; i < arr->size; i++) {
        if (list[i].type == 0) {
            inputs[index1] = list[i].index;
            index1++;  
        } else if(list[i].type == 5) {
            outputs[index2] = list[i].index;
            index2++;
        }
    }

    if (index1 != arr->total_input) {
        printf("yo input stuff is wrong lol\n");
    }

    if (index2 != arr->total_output) {
        printf("yo output stuff is wrong lol\n");
    }

    for (int i = 0; i < arr->total_input;i++) {
        printf("%d ", inputs[i]);
    }
    printf("| ");
    for (int i = 0; i < arr->total_output; i++) {
        printf("%d ", outputs[i]);
    }
    printf("\n");
    long num = (long) pow(2, arr->total_input);
    for (long i = 0; i < num; i++) {
        for (int j = 0; j < arr->total_input; j++) {
            if (((i >> j) & 1) == 1) {
                inputs[j] = 1;
            }  else {
                inputs[j] = 0;
            }
        }

        evaluate_input(arr, inputs, outputs);
        for (int i = 0; i < arr->total_input; i++) {
            printf("%d ", inputs[i]);
        }
        printf("| ");
        for (int i = 0; i < arr->total_output; i++) {
            printf("%d ", outputs[i]);
        }
        printf("\n");
    }
    free(inputs);
    free(outputs);

}