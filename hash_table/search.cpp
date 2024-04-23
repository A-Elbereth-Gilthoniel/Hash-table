#include "hash.h"

// my_strcmp.asm
extern "C" int my_strcmp(char* word1, char* word2);

//===============================================

word_pos search_elem_in_list(list_struct** list, char* word, int (*cmptor)(char*))
{
    word_pos position;
    int list_ind = cmptor(word);

    for (int i = 0; i < list[list_ind]->size; i++)
    {
        #ifdef MY_STRCMP
        if (my_strcmp(list[list_ind]->data[i], word) == 0)
        #else
        if (strcmp(list[list_ind]->data[i], word) == 0)
        #endif
        {
            position.list_ind = list_ind;
            position.word_ind = i;
            return position;
        }
    }
    position.list_ind = ELEM_NOT_FOUND;
    position.word_ind = ELEM_NOT_FOUND;
    return position;
}

//=================================================

double get_work_time(list_struct** list, int (*cmptor)(char*))
{
    word_pos pos;
    const char* check_list[CHECK_LIST_LEN] = CHECK_LIST;
    clock_t begin = clock();
    for (int i = 0; i < CHECK_LIST_LEN; i++)
    {
        for (int _ = 0; _ < ITER_QTY; _++)
            pos = search_elem_in_list(list, (char*)check_list[i], cmptor);
    }
    clock_t end = clock();

    return (double)(end - begin) / CLOCKS_PER_SEC;
}

//===============================================
