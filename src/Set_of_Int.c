/***
 *
 * Project name: Interval
 * File: Interval.c
 * Project was created by Chicha Olexandr on 15.12.19
 * Year: 2-nd
 * Specialization: Computer mathematics
 * Taras Shevchenko National University of Kyiv
 * e-mail: sashachicha13@gmail.com
 * phone number: +380957519417
***/

#include "../headers/Set_of_Int.h"
#include "Interval.c"

// Функція для виводу на екран масиву інтервалів
void PrintRes(set_intervals *res)
{
    Interval *i;
    for ( i = res->interval_array; i <= &(res->interval_array[sizeof(res) + 1]) ; i ++)
    {
        PrintRes1(i);
    }
}

// Функція що створює массив інтервалів
set_intervals *Make_arrayof_Int(Interval *content, int length)
{
    set_intervals *SetInt;
    SetInt = (set_intervals *) malloc(sizeof(length));
    SetInt->interval_array = content;
    SetInt->size = length;
    return SetInt;
}

// Функція що знаходить перетин масивів
set_intervals    *Set_Insection(set_intervals *first, set_intervals *second)
{
    set_intervals *Result = (set_intervals *) malloc(sizeof(set_intervals));

    Interval *test;
    Result->size = first->size * second->size;
    Result->interval_array = (Interval*) malloc(sizeof(Interval)*Result->size);
    int k = 0;
    for (int i = 0; i < first->size; i++)
    {
        for (int j = 0; j < second->size; j++)
        {
            test = DivideIntervals(&first->interval_array[i], &second->interval_array[j]);
            if(test->type != Empty){
                Result->interval_array[k] = *test;
                k += 1;
            }
        }
    }
    return Result;


    //-----------------------------------------------------

}


// ----------------------------------------------------------------------------------------
void PrintRes3(set_intervals *res)
{
    Interval *i;
    for ( i = res->interval_array; i < &(res->interval_array[sizeof(res)/ sizeof(int)]) ; i ++)
    {
        PrintRes1(i);
    }
}

set_intervals *FindElem(set_intervals *kek, Interval * b)
{
    bool flag = false;
    Interval *i;
    set_intervals *Test;
    Test = kek;
    for ( i = kek->interval_array; i <= &(kek->interval_array[sizeof(kek) ]) ; i ++)
    {
        if (i == b){
            flag = true;
        }
    }
    if (flag == true)
    {
        return kek;
    }else
    {
        Test->interval_array[sizeof(kek) + 1 ] = *b;
        return Test;
    }
}

set_intervals    *Set_Difference(set_intervals *first, set_intervals *second)
{
    set_intervals *Result = (set_intervals *) calloc(sizeof(set_intervals), sizeof(Interval));
    Interval *test;


    set_intervals *tmp = Set_Insection(first, second);

    Result->size = first->size * (second->size + 1);
    Result->interval_array = (Interval*) malloc(sizeof(Interval)*Result->size);

    int k = 0;
    for (int i = 0; i < first->size; i++)
    {
        for (int j = 0; j < tmp->size; j++)
        {
            test = Difference_Int(&first->interval_array[i], &tmp->interval_array[j]);
            for (int i1 = 0; i1 < sizeof(test) + 1; i1 ++)
            {
                Result->interval_array[k] = test[i1];
                k++;
            }

        }
    }
    return Result;
}


//------------------------------------------------------------------------------------------


set_intervals    *Set_Multyp(set_intervals *first, set_intervals *second)
{
    set_intervals *Result = (set_intervals *) malloc(sizeof(set_intervals));
    Interval *test;


    //set_intervals *tmp = Set_Insection(first, second);
    Result->size = first->size * second->size;
    Result->interval_array = (Interval*) calloc (sizeof(Interval), sizeof(Interval));

    int k = 0;
    for (int i = 0; i < first->size; i++)
    {
        for (int j = 0; j < second->size; j++)
        {
            test = Multiplication_Int(&first->interval_array[i], &second->interval_array[j]);
//            PrintRes1(&test[1]);
            for (int j1= 0; j1 < sizeof(test)/ sizeof(int) + 1 ; j1++)
            {

                Result->interval_array[k] = test[j1];
                k += 1;
//                PrintRes3(Result);
//                printf("------------\n");

            }
        }
    }
    return Result;
}

set_intervals *TheLenght(set_intervals *first)
{

    int res = 0;
    for (int i = 0; i < first->size; i ++)
    {

        float  k = INFINITY;

        if (first->interval_array[i].type == Infinite || first->interval_array[i].type == InfiniteLeft_RightClosed ||
                first->interval_array[i].type == InfiniteLeft_RightOpen ) {
            res = -1 * k;
        }
        if (first->interval_array[i].type == Infinite || first->interval_array[i].type == InfiniteRight_LeftClosed ||
                first->interval_array[i].type == InfiniteRight_LeftOpen ) {
            res = -1 * k;
        }
        res+= first->interval_array[i].b - first->interval_array[i].a;
    }
    printf("%d", res);
}