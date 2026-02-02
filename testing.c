#include "dynamic.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"
#include <stdlib.h>
#include <math.h>
int compare(const void* a, const void* b) {
    int x = ((node*) a) ->index;
    int y = ((node*) b) ->index;
    return (x > y) - (x < y); 
}
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
        printf("Your input is wrong\n");
        return;
    }

    if (index2 != arr->total_output) {
        printf("Your output is wrong\n");
        return;
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

void test(char* path) {
    FILE* f = fopen(path, "r");
    array_list *arr = parse_data(f);
    if (arr == NULL) {
        return;
    }
    print_list(arr);
    printing(arr);
    free_all(arr);
    free(arr);
    fclose(f);
}

int main() {
    char* path1 = "circuit2.txt";
    char* path2 = "circuit3.txt";
    char* path3 = "xor.txt";
    test(path1);
    test(path2);
    test(path3);
}

