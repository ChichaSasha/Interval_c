/***
 *
 * Project name: Interval
 * File: Set_of_Int.c
 * Project was created by Chicha Olexandr on 15.12.19
 * Year: 2-nd
 * Specialization: Computer mathematics
 * Taras Shevchenko National University of Kyiv
 * e-mail: sashachicha13@gmail.com
 * phone number: +380957519417
 *
***/

#include "Intarval.h"
#ifndef INTERVAL_SAV_SET_OF_INT_H
#define INTERVAL_SAV_SET_OF_INT_H



// Стуктура, що являє мобою массив інтервалів
typedef struct SetIntervals {
    Interval *interval_array;
    int size;
} set_intervals;

// Перелік функцій, що використовуються для роботи з даною структурою
set_intervals *Make_arrayof_Int(Interval *content, int length);
set_intervals    *Set_Insection(set_intervals *first, set_intervals *second);
void PrintRes3(set_intervals *res);
set_intervals   *FindElem(set_intervals *kek, Interval * b);
set_intervals    *Set_Difference(set_intervals *first, set_intervals *second);
set_intervals    *Set_Multyp(set_intervals *first, set_intervals *second);
set_intervals  *TheLenght(set_intervals *first);

#endif //INTERVAL_SAV_ASD_H