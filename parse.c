#include "dynamic.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
int use_info(char* first, char* second, char* third, char* fourth, array_list* source);
int modify_based(char* parsed, char* full, node* n);
bool check_dupe(char* first, char* second, char* third, char* fourth);
char* get_str(char* word, int size);
void scan_line(char* line, int* size, char* result);
int read_line(char reader[], FILE* f);
array_list* parse_data(FILE* f) {// return NULL if error
    // this ASSUMES f has already been checked for NULL pointer
    array_list* storage = new_array_list(15);
    //printf("HI");
    // first, we scan the first line
    // free the memory at the end btw
    char read_file[1024];
    char* parsed_result = (char*) malloc(strlen(read_file) + 1);
    int file_size = 0;
    // fgets(read_file, sizeof(read_file), f); // NEEDS ADJUSMENT -> SIMPLY MAKE A NEW FUNCTION THAT USES fread
    // it should stop when it reaches \n or the function returns NULL -> yeah lowk this is easy to implement
    // and then add a \0 at the end of the thing :D 
    // still a similar concept with malloc tho
    // read_file[strcspn(read_file, "\n")] = '\0';
    read_line(read_file, f);
    scan_line(read_file, &file_size, parsed_result);
    //printf("%s", read_file);
    //printf("\n%s", parsed_result);

    if (strcmp(parsed_result, "{") != 0) { // double check that this works with the \0 btw
        free(parsed_result);
        // printf("%s\n", parsed_result);
        fprintf(stderr, "INCORRECT FORMATTING WITH THE BEGINNING OF THE FILE\n");
        return NULL;
    }

    free(parsed_result);
    parsed_result = NULL;
    // call a function to do the other thing

    // ok so how about we do a for loop
    // the first one requests for an open. If no open, we break -> still use read_file as our pointer
    // and then we can still do our thing at the end
    // first -> scan for {
    // scan 4 lines 
    // scan for }
    // repeat
    while (true) { // make the while condition simply be that read_file isn't the end completetion thing -> i forgot what that is lol
        file_size = 0;
        // fgets(read_file, sizeof(read_file), f);
        // read_file[strcspn(read_file, "\n")] = '\0';
        read_line(read_file, f);
        parsed_result = (char*) malloc(strlen(read_file) + 1);
        scan_line(read_file, &file_size, parsed_result);
        // take care of the open bracket
        if (strcmp("{", parsed_result) != 0) {
            if (strcmp("}", parsed_result) == 0) {
                break;
            } else {
                free(parsed_result);
                fprintf(stderr, "INCORRECT FORMATTING WITH THE BEGINNING OF THE STANZA\n");
                return NULL;
            }
        }

        free(parsed_result);


        char first_line[1024];
        char second_line[1024];
        char third_line[1024];
        char fourth_line[1024];
        read_line(first_line, f);
        read_line(second_line, f);
        read_line(third_line, f);
        read_line(fourth_line, f);
        // printf("%s\n", first_line);
        //         printf("%s\n", second_line);

        //                 printf("%s\n", third_line);
        // printf("%s\n", fourth_line);

        // fgets(first_line, sizeof(first_line), f);
        // first_line[strcspn(first_line, "\n")] = '\0';
        // fgets(second_line, sizeof(second_line), f);
        // second_line[strcspn(second_line, "\n")] = '\0';
        // fgets(third_line, sizeof(third_line), f);
        // third_line[strcspn(third_line, "\n")] = '\0';
        // fgets(fourth_line, sizeof(fourth_line), f);
        // fourth_line[strcspn(fourth_line, "\n")] = '\0';
        /*
        fscanf(f, "%s", first_line); // TODO add a checker that ensures that if there's any error at this point, 
        // RETURN NULL
        fscanf(f, "%s", second_line);
        fscanf(f, "%s", third_line);
        fscanf(f, "%s", fourth_line);
        */
       //printf("before\n");
        if (use_info(first_line, second_line, third_line, fourth_line, storage) == 1) {
            fprintf(stderr, "INCORRECT FORMATTING WITH THE STANZA INSIDE");
            // printf("gg");
            return NULL;
        }
        // printf("hello\n");
        // take care of the ending bracket 
        file_size = 0;
        // fgets(read_file, sizeof(read_file), f);
        // read_file[strcspn(read_file, "\n")] = '\0';
        read_line(read_file, f);
        parsed_result = (char*) malloc(strlen(read_file) + 1);
        scan_line(read_file, &file_size, parsed_result);
        if (strcmp("}", parsed_result) != 0) {
            free(parsed_result);
            fprintf(stderr, "INCORRECT FORMATTING FOR STANZA ENDING\n");
            return NULL;
        }
        // printf("DONE\n");

        free(parsed_result);
    }

    // file_size = 0;
    // scan_line(read_file, &file_size, parse_result);
    if (strcmp(parsed_result, "}") != 0) {
        free(parsed_result);
        fprintf(stderr, "INCORRECT FORMATTING WITH THE ENDING OF THE FILE\n");
        return NULL;
    }
    free(parsed_result);

    return storage;
    // TODO use fclose to the pointer in the main function after 
}

int use_info(char* first, char* second, char* third, char* fourth, array_list* source) {
    // return 1 if there's an error
    // return 0 if there is no error    
    // i lowkey dont tknow how to take a substring in C LOL, so i have to look this up
    char* new_first = (char*) malloc(strlen(first) + 1);
    char* new_second = (char*) malloc(strlen(second) + 1);
    char* new_third = (char*) malloc(strlen(third) + 1);
    char* new_fourth = (char*) malloc(strlen(fourth) + 1);
    int first_size = 0;
    int second_size = 0;
    int third_size = 0;
    int fourth_size = 0;


    scan_line(first, &first_size, new_first);
    scan_line(second, &second_size, new_second);
    scan_line(third, &third_size, new_third);
    scan_line(fourth, &fourth_size, new_fourth);
        //         printf("%s\n", new_first);
        // printf("%s\n", new_second);
        // printf("%s\n", new_third);
        // printf("%s\n", new_fourth);
    // TODO add null terminators cuz apparently that's needed 
    // get all the words parsed out
    char* parsed_first = get_str(new_first, first_size);
    char* parsed_second = get_str(new_second, second_size);
    char* parsed_third = get_str(new_third, third_size);
    char* parsed_fourth = get_str(new_fourth, fourth_size);
    // printf("%s   %s\n", new_first, parsed_first);
    // printf("%s %s\n", new_second, parsed_second);
    // printf("%s %s\n", new_third, parsed_third);
    // printf("%s %s\n", new_fourth, parsed_fourth);
    if (check_dupe(parsed_first, parsed_second, parsed_third, parsed_fourth)) {
        printf("has dupe\n");
        // ADD FREE if the parsed shit has to be malloc
        free(parsed_first);
        free(parsed_second);
        free(parsed_third);
        free(parsed_fourth);
        free(new_first);
        free(new_second);
        free(new_third);
        free(new_fourth);
        return 1;
    }

    // so now just parse everything and then be happy :D 
    // CALL FUNCTION WITH THE FOUR STRINGS AND THEN HAVE FUN YAY
    // THE FUNCTION SHOULD CHECK WHAT IT IS, AND THEN DO THE THING, AND THEN 
    // CALL ANOTHER FUNCTIOn TO ACTUALLY EDIT THE VARIABLES SINCE SOME OF THEM MIGHT BE A BIT MORE COMPLICATED
    node new_node;
    int check = 0;
    // printf("testing");
    check +=  modify_based(parsed_first, new_first, &new_node);
    // printf("%d\n", check);
    check +=  modify_based(parsed_second, new_second, &new_node);
    //    printf("%d\n", check);

    check +=  modify_based(parsed_third, new_third, &new_node);
    //    printf("%d\n", check);

    check +=  modify_based(parsed_fourth, new_fourth, &new_node);
    //    printf("%d\n", check);
    // THE ISSUE IS WITH INPUT AND OUTPUT
    free(new_first);
    free(new_second);
    free(new_third);
    free(new_fourth);
    free(parsed_first);
    free(parsed_second);
    free(parsed_third);
    free(parsed_fourth);
    // printf("hi");

    if (check != 0) {
        printf("couldnt modify\n");
        return 1;
    }
    // TODO check input size for the ones with NOT

    add_to_list(source, &new_node);
    //printf("meow");
    return 0;
}

int modify_based(char* parsed, char* full, node* n) {
    // return 0 if it works
    // return 1 if it doesn't
    if (strcmp(parsed, "Type") == 0) {
        char* par;
        int size = strlen(full) - strlen(parsed);
        par = (char*) malloc(size + 1);
        strncpy(par, full + strlen(parsed) + 1, size);
        par[size] = '\0';
        if (strcmp(par, "INPUT") == 0) {
            n->type = 0;
        } else if (strcmp(par, "AND") == 0) {
            n->type = 1;
        } else if (strcmp(par, "OR") == 0) {
            n->type = 2;
        } else if (strcmp(par, "XOR") == 0) {
            n->type = 3;
        } else if (strcmp(par, "NOT") == 0) {
            n->type = 4;
        } else if (strcmp(par, "OUTPUT") == 0) {
            n->type = 5;
        } else {
            free(par);
            return 1;
        }

        free(par);
        return 0;
    } else if (strcmp(parsed, "UniqueID") == 0) {
        int index = strlen(parsed) + 1;
        if (index >= strlen(full)) {
            return 2;
        } else {
            int result = 0;
            while (full[index] != '\0') {
                int digit = full[index] - '0';
                if (digit < 0 || digit > 9) {
                    return 2;
                }
                result = 10 * result + digit;
                index++;
            }

            n->index = result;
            return 0;
        }
    } else if (strcmp(parsed, "Input") == 0) {
        char* par;
        int size = strlen(full) - strlen(parsed) - 1;
        // if (size == 0) {
        //     return 0;
        // }

        par = (char*) malloc(size + 1);
        if (size != 0) {
            strncpy(par, full + strlen(parsed) + 1, size);
        }
        par[size] = '\0';
        // printf("Testing \n");
        // printf("parsed: %s \n", parsed);
        // printf("full: %s \n", full);
        // printf("The last part: %s \n", par);
        // printf("Length of par: %d \n", strlen(par));
        // printf("\n\n");
        n->input_list =(int*) malloc(size * sizeof(int));
        int index = 0;
        int curr_number = -1;
        int actual_index = 0;
        while (index < size) {
            if (par[index] != ',') {
                if (par[index] - '0' > 9 || par[index] - '0' < 0) {
                    free(par);
                    free(n->input_list);
                    return 3;
                }

                int number = par[index] - '0';
                if (curr_number == -1) {
                    curr_number = number;
                } else {
                    curr_number = 10 * curr_number + number;
                }
            } else {
                if (curr_number != -1) {
                    n->input_list[actual_index] = curr_number;
                    curr_number = -1;
                    actual_index++;
                }
            }

            index++;
        }

        n->input_size = actual_index;
        free(par);
        return 0;

    } else if (strcmp(parsed, "Output") == 0) {
        char* par;
        int size = strlen(full) - strlen(parsed) - 1;
        // if (size == 0) {
        //     return 0;
        // }
        int actual_index = 0;
        par = (char*) malloc(size + 1);
        if (size != 0) {
            strncpy(par, full + strlen(parsed) + 1, size);
        }

        par[size] = '\0';
        // printf("parsed: %s \n", parsed);
        // printf("full: %s \n", full);
        // printf("The last part: %s \n", par);
        // printf("Length of par: %d \n", strlen(par));
        // printf("\n\n");
        n->output_list = (int*) malloc(size * sizeof(int));
        int index = 0;
        int curr_number = -1;
        while (index < size) {
            if (par[index] != ',') {
                if (par[index] - '0' > 9 || par[index] - '0' < 0) {
                    free(par);
                    free(n->output_list);
                    return 4;
                }

                int number = par[index] - '0';
                if (curr_number == -1) {
                    curr_number = number;
                } else {
                    curr_number = 10 * curr_number + number;
                }
            } else {
                if (curr_number != -1) {
                    n->output_list[actual_index] = curr_number;
                    curr_number = -1;
                    actual_index++;
                }
            }

            index++;
        }

        n->output_size = actual_index;
        free(par);
        return 0;
    } else {
        return 5;
    }
}
bool check_dupe(char* first, char* second, char* third, char* fourth) {
    if (strcmp(first, second) == 0 || strcmp(second, third) == 0 || strcmp(third, fourth) == 0) {
        return true;
    }

    if (strcmp(first, third) == 0 || strcmp(first, fourth) == 0 || strcmp(second, fourth) == 0) {
        return true;
    }

    return false;
}

char* get_str(char* word, int size) {
    int index = 0;
    
    while (index < size && word[index] != '=') {
        index++;
    }

    if (index == size) {
        return NULL; // this means that we didn't find a = sign at all, which is not okay
    }

    char* result;
    result = (char*) malloc(index + 1);
    strncpy(result, word, index);
    result[index] = '\0';
    return result;
}

void scan_line(char* line, int* size, char* result) {
    *size = 0;
    int index = 0;
    while (line[index] != '\0') {
        if (line[index] != ' ') {
            result[*size] = line[index];
            //printf("%c", line[index]);
            *size += 1;
        }

        index++;
    }
    // printf("\n\n%c\n", result[0]);
    result[*size] = '\0';
    // printf("\n%c\n", result[0]);
    // printf("\n%d\n", strlen(result));
    // TODO double check if i have to add the '\0' myself
}

int read_line(char reader[], FILE* f) {
    int index = 0;
    //printf("hi");
    char store[1];
    size_t status = fread(store, 1, 1, f);
    //printf("hey");
    while (*store != '\0' && *store != '\n' && status != 0) {
        reader[index] = *store;
        index++;
        //printf("%c\n", *store);

        status =  fread(store, 1, 1, f);
    }

    reader[index] = '\0';
    return 0;

}