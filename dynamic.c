#include "dynamic.h"
#include <stdio.h>
#include <stdlib.h>
array_list* new_array_list(int cap) {
    array_list* new_list = (array_list*) malloc(sizeof(array_list));
    new_list->size = 0;
    new_list->capacity = cap;
    new_list->data = (node*) malloc(sizeof(node) * cap); 
    new_list->total_input = 0;
    new_list->total_output = 0;
    return new_list;
}

void add_to_list(array_list* arr, node *new_element) {
    if (arr->size == arr->capacity) {
        resize(arr);
    }

    if (new_element->type == 0) {
        arr->total_input += 1;
    } else if (new_element->type == 5){
        arr->total_output += 1;
    }

    node* list = arr->data;
    *(list + arr->size) = *new_element;
    arr->size++;



    // printf("\n PRINTING NODE INFO\n");
    // printf("ID: %d\n", new_element->index);
    // printf("Type: %d\n", new_element->type);
    // printf("Inputs: ");
    // for (int i = 0; i < new_element->input_size; i++) {
    //     printf(" %d", new_element->input_list[i]);
    // }
    // printf("\n");
    // printf("Outputs: ");
    // for (int i = 0; i < new_element->output_size; i++) {
    //     printf(" %d", new_element->output_list[i]);
    // }
    // printf("\n");
    // printf("\n\n");
    // printf("WE ARE DONE\n");
    // free(new_element->input_list);
    // free(new_element->output_list);
}

void free_all(array_list* arr) { // note that this only frees the attributes of arr and doesn't free the array_list itself lol
    node* ptr = arr->data; // cheeck if this copies the pointer into this variable
    for (int i = 0; i < arr->size; i++) {
        if (ptr != NULL) {
            free(ptr->input_list);
            free(ptr->output_list);
        }

        ptr++; // check if this is allowed
    }

    free(arr -> data);
}

void resize(array_list* arr) {
    int new_cap = 2 * arr->capacity + 1; 
    arr->capacity = new_cap;
    node* new_data = (node*) malloc(sizeof(node) * new_cap);
    node* ptr = arr->data;
    for (int i = 0; i < arr->size; i++) {
        *(new_data + i) = *(ptr + i);
    }

    free(arr->data);
    arr->data = new_data;
}




int evaluate_input(array_list* arr, int* input, int* final_result) {
    int storage_size = arr->size;
    int* storage =(int*) malloc((storage_size) * sizeof(int));
    // we assume the input is in sorted order and that its size is arr->total_inputs
    for (int i = 0; i < storage_size; i++) {
        storage[i] = -1;
    }
    int inputs_passed = 0;
    node* list = arr->data;
    for (int i = 0; i < arr->size; i++) {
        if (list[i].type == 0) {
            storage[i] = input[inputs_passed];
            inputs_passed++;
        }

        if (inputs_passed >= arr->total_input) {
            break;
        }
    }

    int outputs_found = 0;
    for (int i = 0; i < arr->size; i++) {
        if (list[i].type == 5) {
            final_result[outputs_found] = find_answer(storage, i, arr);
            outputs_found++;
        }

        if (outputs_found >= arr->total_output) {
            break;
        }
    }

    // printf("\n");
    // for (int i = 0; i < storage_size;i++) {
    //     printf(" %d ", storage[i]);
    // }
    // printf("\n");
    free(storage);

    return 0;
}

void print_list(array_list* arr) {
    printf("\n PRINTING NODE INFO\n");
    node* list = arr->data;
    for (int i = 0; i < arr->size; i++) {
    node* new_element = list + i;
    printf("ID: %d\n", new_element->index);
    printf("Type: %d\n", new_element->type);
    printf("Inputs: ");
    for (int i = 0; i < new_element->input_size; i++) {
        printf(" %d", new_element->input_list[i]);
    }
    printf("\n");
    printf("Outputs: ");
    for (int i = 0; i < new_element->output_size; i++) {
        printf(" %d", new_element->output_list[i]);
    }
    printf("\n");
    printf("\n\n");
    }
    printf("WE ARE DONE\n");
}

int find_answer(int* storage, int index, array_list* arr) {
    if (storage[index] != -1) {
        return storage[index];
    }

    node* list = arr->data;
    node index_node = list[index];
    int size_of_input = index_node.input_size; // this should be nonzero
    int* list_input = (int*) malloc(sizeof(int) * size_of_input);
    int num_zeroes = 0;
    int num_ones = 0;
    for (int i = 0; i < size_of_input; i++) {
        list_input[i] = find_answer(storage, index_node.input_list[i], arr);
        if (list_input[i] == 1) {
            num_ones++;
        } else if (list_input[i] == 0) {
            num_zeroes++;
        }
    }

    if (index_node.type == 4) {
        storage[index] = 1 - list_input[0];
        free(list_input);
        return storage[index];
    }

    if (index_node.type == 5) {
        storage[index] = list_input[0];
        free(list_input);

        return storage[index];
    }

    if (index_node.type == 1) {
        free(list_input);

        if (num_zeroes == 0) {
            storage[index] = 1;
            return 1;
        } else {
            storage[index] = 0;
            return 0;
        }
    }

    if (index_node.type == 2) {
        free(list_input);
        if (num_ones != 0) {
            storage[index] = 1;
            return 1;
        } else {
            storage[index] = 0;
            return 0;
        }
    }

    if (index_node.type == 3) {
        free(list_input);
        num_ones %= 2;
        num_zeroes %= 2;
        if (num_ones == 1 && num_zeroes == 1) {
            storage[index] = 1;
            return 1;
        } else if (num_ones == 1) {
            storage[index] = 1;
            return 1;
        } else {
            storage[index] = 0;
            return 0;
        }
    }
    free(list_input);
    return -1;
}
