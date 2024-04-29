#include "hash.h"

// my_strcmp.asm
 extern "C" int my_strcmp(char* word1, char* word2);

//===============================================

word_pos search_elem_in_list(list_struct** list, char* word, int (*cmptor)(char*))
{
    word_pos position;
    volatile int cmp = 0;
    int list_ind = cmptor(word);
    int size = list[list_ind]->size;

    for (int i = 0; i < size; ++i)
    {
        #ifdef MY_STRCMP
        cmp = my_strcmp(list[list_ind]->data[i], word);
        #else
        cmp = strcmp(list[list_ind]->data[i], word);
        #endif
        if (cmp == 0)
        {
            position.list_ind = list_ind;
            position.word_ind = i;
            return (word_pos)position;
        }
    }
    position.list_ind = ELEM_NOT_FOUND;
    position.word_ind = ELEM_NOT_FOUND;
    return (word_pos)position;
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

//=============================================

int fast_strcmp_avx2(char* s1, char* s2)
{
    __m256i v1, v2, cmp_result;
    int mask = 0;
    const __m256i zero = _mm256_setzero_si256();

    while (1) {
        v1 = _mm256_loadu_si256((__m256i*)s1);
        v2 = _mm256_loadu_si256((__m256i*)s2);

        cmp_result = _mm256_cmpeq_epi8(v1, v2);
        mask = ~_mm256_movemask_epi8(cmp_result);

        if (mask != 0)
        {
            int index = __builtin_ctz(mask) - 1;
            return (s1[index] == '\0' && s2[index] == '\0') ? 0 : -1;
        }

        s1 += 32;
        s2 += 32;
    }
    return 0;
}
