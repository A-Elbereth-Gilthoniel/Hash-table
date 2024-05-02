#include "hash.h"


int main()
{
    size_t word_qty = take_symb_qty();
    char** word_array = (char**) calloc(word_qty, sizeof(char*));
    fill_word_array(word_array);

    list_struct** hash_list1 = make_hash_table(const_func, word_array, word_qty);
    list_struct** hash_list2 = make_hash_table(first_ascii_func, word_array, word_qty);
    list_struct** hash_list3 = make_hash_table(word_length, word_array, word_qty);
    list_struct** hash_list4 = make_hash_table(shift_right, word_array, word_qty);
    list_struct** hash_list5 = make_hash_table(shift_left, word_array, word_qty);
    list_struct** hash_list6 = make_hash_table(ascii_sum, word_array, word_qty);
    list_struct** hash_list7 = make_hash_table(crc32, word_array, word_qty);

    put_hash_into_file(hash_list1, CONST_FILE_NAME);
    put_hash_into_file(hash_list2, FIRST_ASCII_NAME);
    put_hash_into_file(hash_list3, LENGTH_NAME);
    put_hash_into_file(hash_list4, SHIFT_RIGHT_NAME);
    put_hash_into_file(hash_list5, SHIFT_LEFT_NAME);
    put_hash_into_file(hash_list6, ASCII_SUM_NAME);
    put_hash_into_file(hash_list7, CRC32_NAME);

    double* measurement = measure_sample(hash_list1, const_func);
    printf("const       = %lf seconds\t+- %lf\n", measurement[0], measurement[1]);
    measurement = measure_sample(hash_list2, first_ascii_func);
    printf("first ascii = %lf seconds\t+- %lf\n", measurement[0], measurement[1]);
    measurement = measure_sample(hash_list3, word_length);
    printf("length      = %lf seconds\t+- %lf\n", measurement[0], measurement[1]);
    measurement = measure_sample(hash_list4, shift_right);
    printf("shift right = %lf seconds\t+- %lf\n", measurement[0], measurement[1]);
    measurement = measure_sample(hash_list5, shift_left);
    printf("shift left  = %lf seconds\t+- %lf\n", measurement[0], measurement[1]);
    measurement = measure_sample(hash_list6, ascii_sum);
    printf("ascii sum   = %lf seconds\t+- %lf\n", measurement[0], measurement[1]);
    measurement = measure_sample(hash_list7, crc32);
    printf("crc32       = %lf seconds\t+- %lf\n", measurement[0], measurement[1]);
    free(measurement);
}
