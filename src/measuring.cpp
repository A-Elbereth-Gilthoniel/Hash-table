#include "hash.h"


double* measure_sample(list_struct** list, int (*cmptor)(char*))
{
    double* time_and_accuracy = (double*) calloc(2, sizeof(double));

    double oper_times[SAMPLE];
    double time_sum = 0, accuracy = 0, med_time = 0;

    for (int i = 0; i < SAMPLE; i++)
    {
        oper_times[i] = get_work_time(list, cmptor);
        time_sum += oper_times[i];
    }

    med_time = time_sum / SAMPLE;
    for (int i = 0; i < SAMPLE; i++)
    {
        accuracy += (med_time - oper_times[i]) * (med_time - oper_times[i]);
    }

    accuracy = sqrt(accuracy / SAMPLE);

    time_and_accuracy[0] = med_time;
    time_and_accuracy[1] = accuracy;

    return time_and_accuracy;
}
//=========================================================

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

//=======================================================
