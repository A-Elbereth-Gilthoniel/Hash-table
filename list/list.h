#ifndef LIST_H
#define LIST_H
#include "../general/libr.h"

#define TYPE_LIST       char*

typedef struct {
    TYPE_LIST* data;
    int capacity;
    int size;
} list_struct;

//==============================================================

list_struct* make_list(int length);
void list_realloc(list_struct* list, int new_capacity);
void append_to_list(list_struct* list, TYPE_LIST value);
void insert_into_list(list_struct* list, TYPE_LIST value, int index);
void remove_from_list(list_struct* list, int index);
// void destruct_list(list_struct* list);
void print_list(list_struct* list);
list_struct* cut_from_list(list_struct* copied_list, int start_i, int finish_i);
list_struct* reversed_list(list_struct* list);
void destruct_list(list_struct* list);

//==============================================================

#endif // LIST_H
