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
void printing2(array_list* arr) {
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
    char* result = (char*) malloc(16);
    int size = 0;
    int checker = 0;
    char* expected = "0 2 3 | 1 ";
    for (int i = 0; i < arr->total_input;i++) {
        printf("%d ", inputs[i]);
        result[size] = inputs[i] + 48;
        size++;
        result[size] = ' ';
        size++;
    }
    printf("| ");
    result[size] = '|';
    size++;
    result[size] = ' ';
    size++;
    for (int i = 0; i < arr->total_output; i++) {
        printf("%d ", outputs[i]);
        result[size] = outputs[i] + 48;
        size++;
        result[size] = ' ';
        size++;
    }
    result[size] = '\0';
    if (strcmp(result, expected) != 0) {
        checker++;
    }
    printf("\n");
    free(result);
    long num = (long) pow(2, arr->total_input);
    for (long i = 0; i < num; i++) {
        for (int j = 0; j < arr->total_input; j++) {
            if (((i >> j) & 1) == 1) {
                inputs[j] = 1;
            }  else {
                inputs[j] = 0;
            }
        }
        if (i == 3) {
            size = 0;
            result = (char*) malloc(16);
        }
        evaluate_input(arr, inputs, outputs);
        for (int j = 0; j < arr->total_input; j++) {
            printf("%d ", inputs[j]);
            if (i == 3) {
                result[size] = inputs[j] + 48;
                size++;
                result[size] = ' ';
                size++;
            }
        }
        printf("| ");
        if (i == 3) {
            result[size] = '|';
            size++;
            result[size] = ' ';
            size++;
        }
        for (int j = 0; j < arr->total_output; j++) {
            printf("%d ", outputs[j]);
            if (i == 3) {
                result[size] = outputs[j] + 48;
                size++;
                result[size] = ' ';
                size++;
            }
        }
        printf("\n");
    }
    if (strcmp(result, "1 1 0 | 0 ") != 0) {
        checker++;
    }
    free(result);
    if (checker != 0) {
        printf("\n TEST 2 FAILED\n");
    } else {
        printf("\n PASSED TEST 2\n");
    }
    free(inputs);
    free(outputs);

}

void printing1(array_list* arr) {

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
    char* result = (char*) malloc(8);
    int size = 0;
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
        for (int j = 0; j < arr->total_input; j++) {
            printf("%d ", inputs[j]);
        }
        printf("| ");
        for (int j = 0; j < arr->total_output; j++) {
            printf("%d ", outputs[j]);
        }
        printf("\n");
    }
    free(inputs);
    free(outputs);

}

void printing3(array_list* arr) {

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
    char* result = (char*) malloc(8);
    int size = 0;
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
        for (int j = 0; j < arr->total_input; j++) {
            printf("%d ", inputs[j]);
        }
        printf("| ");
        for (int j = 0; j < arr->total_output; j++) {
            printf("%d ", outputs[j]);
        }
        printf("\n");
    }
    free(inputs);
    free(outputs);

}

void test1(char* path) {
    FILE* f = fopen(path, "r");
    array_list *arr = parse_data(f);
    if (arr == NULL) {
        return;
    }
    print_list(arr);
    printing1(arr);
    free_all(arr);
    free(arr);
    fclose(f);
}

void test2(char* path) {
    FILE* f = fopen(path, "r");
    array_list *arr = parse_data(f);
    if (arr == NULL) {
        return;
    }
    print_list(arr);
    printing2(arr);
    free_all(arr);
    free(arr);
    fclose(f);
}

void test3(char* path) {
    FILE* f = fopen(path, "r");
    array_list *arr = parse_data(f);
    if (arr == NULL) {
        return;
    }
    print_list(arr);
    printing3(arr);
    free_all(arr);
    free(arr);
    fclose(f);
}
int main() {
    char* path1 = "circuit2.txt";
    char* path2 = "circuit3.txt";
    char* path3 = "xor.txt";
    test1(path1);
    test2(path2);
    test3(path3);
}

