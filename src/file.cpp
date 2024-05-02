#include "hash.h"

void fill_word_array(char** word_array)
{
    FILE* fp = fopen(HANDLED_FILE, "r");
    size_t n = find_file_size(fp);

    char *words = (char*)calloc(n + 1, sizeof(char));
    char* start_words = words;
    int garbage = fread(words, sizeof(char), n, fp);

    char* end_of_str = NULL;
    int k = 0;
    int length = 0;
    while (end_of_str = strchr(words, '\n'))
    {
        k = end_of_str - words;
        word_array[length] = (char*) calloc(k + 1, sizeof(char));
        strncpy(word_array[length], words, k);

        words = words + k +1;
        length++;
    }
    fclose(fp);
    free(start_words);
}

//=================================================

size_t find_file_size(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    size_t n = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return n;
}

//=================================================

size_t take_symb_qty()
{
    size_t n = 0;
    FILE* qty_fp = fopen(SYMB_QTY_FILE, "r");
    int garbage = fscanf(qty_fp, "%zu", &n);
    return n;
}

//=================================================

void put_hash_into_file(list_struct** hash_list, const char* file_name)
{
    FILE* fp = fopen(file_name, "w");
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        fprintf(fp, "%d\n", hash_list[i]->size);
    }
    fclose(fp);
}
