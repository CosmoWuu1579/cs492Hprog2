#ifndef DYNAMIC_H
#define DYNAMIC_H

typedef struct {
    int index;
    int type; // 0 is input, 1 is AND, 2 is OR, 3 is XOR, 4 is NOT, 5 is OUTPUT
    int* input_list;
    int input_size;
    int* output_list;
    int output_size;
    int current_value; // used for 0 or 1 when evaluating
} node;

typedef struct {
    node* data; // TS NEEDS TO BE A POINTER TO A POINTER
    // Wait actually im not sure if this needs to be a pointer or not -> double check 
    // seems like because it's a struct it doesnt actually matter too much, but lemme test it in jsut a second 
    // after this plane goes off 
    int size;
    int capacity;
    int total_input;
    int total_output;
} array_list;

array_list* new_array_list(int cap);
void add_to_list(array_list* arr, node *new_element);
int evaluate_input(array_list* arr, int* input, int* final_result); //we store the final results in an array
// // REMEMBER TO FREE THIS ARRAY EVERYTIME
// // Final result should be originally null, and then you allocate memory based on 
void free_all(array_list* arr); // clean up the memory
void resize(array_list* arr);
void print_list(array_list* arr);
int find_answer(int* storage, int index, array_list* arr);
#endif // double check why you need this
