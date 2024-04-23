#include "../general/dsl.h"
#include "../general/libr.h"
#include "../list/list.h"

size_t find_file_size(FILE* fp);
int search_elem_in_list(list_struct* list, char* word);
int check_word_avail(list_struct* list, char* word);

//==============================================================

int main()
{
    size_t char_qty = 0;
    FILE* fp = fopen(TEXT_FILE, "r");
    list_struct* word_list = make_list(START_LIST_SIZE);

    size_t n = find_file_size(fp);
    char *text = (char*)calloc(n + 1, sizeof(char));
    fread(text, sizeof(char), n, fp);

    FILE* new_fp = fopen(HANDLED_FILE, "w");
    char buffer[MAX_WORD_SIZE];
    int cur_len = 0, word_qty = 0;

    for (int i = 0; i < n; i++)
    {
        if ('a' <= tolower(text[i]) && tolower(text[i]) <= 'z')
        {
            buffer[cur_len] = text[i];
            cur_len++;
        }
        else if (cur_len != 0)
        {
            buffer[cur_len] = '\0';
            if (check_word_avail(word_list, buffer) == ELEM_NOT_FOUND)
            {
                fprintf(new_fp, "%s\n", buffer);
                word_qty++;
            }
            cur_len = 0;
        }
    }

    if (cur_len != 0)
    {
        buffer[cur_len] = '\0';
        if (check_word_avail(word_list, buffer) == ELEM_NOT_FOUND)
        {
            fprintf(new_fp, "%s\n", buffer);
            word_qty++;
        }
        cur_len = 0;
    }

    FILE* qty_fp = fopen(SYMB_QTY_FILE, "w");
    fprintf(qty_fp, "%d\n", word_qty);
    fclose(qty_fp);
    fclose(fp);
    fclose(new_fp);
    destruct_list(word_list);
}

//==============================================================

size_t find_file_size(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    size_t n = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return n;
}

//==============================================================

int search_elem_in_list(list_struct* list, char* word)
{
    int start_i = 0, finish_i = 0, supple = 0;
    for (int i = 0; i < list->size; i ++)
    {
        if (strcmp(list->data[i], word) == 0)
            return i;
    }
    return ELEM_NOT_FOUND;
}

//=============================================================

int check_word_avail(list_struct* list, char* word)
{
    if (search_elem_in_list(list, word) == ELEM_NOT_FOUND)
    {
        append_to_list(list, word);
        return ELEM_NOT_FOUND;
    }
    return ELEM_IS_FOUND;
}
