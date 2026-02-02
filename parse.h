#include "dynamic.h"
#include <stdio.h>
array_list* parse_data(FILE* f);
int use_info(char* first, char* second, char* third, char* fourth, array_list* source);
int modify_based(char* parsed, char* full, node* n);
bool check_dupe(char* first, char* second, char* third, char* fourth);
char* get_str(char* word, int size);
void scan_line(char* line, int* size, char* result);