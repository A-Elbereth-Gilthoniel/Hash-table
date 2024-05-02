#ifndef HEX
#define HEX

#include "../general/dsl.h"
#include "../general/libr.h"
#include "../list/list.h"

typedef struct {
    int list_ind;
    int word_ind;
} word_pos;



// file.cpp
void fill_word_array(char** word_array);
size_t find_file_size(FILE* fp);
size_t take_symb_qty();
void put_hash_into_file(list_struct** hash_list, const char* file_name);

// search.cpp
word_pos search_elem_in_list(list_struct** list, char* word, int (*cmptor)(char*));
int fast_strcmp(char* s1, char* s2);

// hash_functions.cpp
list_struct** make_hash_table(int (*cmptor)(char*), char** word_array, size_t word_qty);
int const_func(char* word);
int first_ascii_func(char* word);
int word_length(char* word);
int shift_right(char* word);
int shift_left(char* word);
int ascii_sum(char* word);
int crc32(char* word);
int new_strlen(char* word);

// measuring.cpp
double* measure_sample(list_struct** list, int (*cmptor)(char*));
double get_work_time(list_struct** list, int (*cmptor)(char*));

#endif
