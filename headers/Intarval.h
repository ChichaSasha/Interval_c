/***
 *
 * Project name: Interval
 * File: Interval.h
 * Project was created by Chicha Olexandr on 15.12.19
 * Year: 2-nd
 * Specialization: Computer mathematics
 * Taras Shevchenko National University of Kyiv
 * e-mail: sashachicha13@gmail.com
 * phone number: +380957519417
 *
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#include "stdbool.h"

#ifndef INTERVAL_SAV_INTERVAL_H
#define INTERVAL_SAV_INTERVAL_H

// енам типів інтервалів
enum type_interval{
    Empty,
    SingleDot,
    Closed,
    HalfClosedLeft,
    HalfClosedRight,
    Opened,
    InfiniteLeft_RightOpen,
    InfiniteLeft_RightClosed,
    InfiniteRight_LeftOpen,
    InfiniteRight_LeftClosed,
    Infinite
} ;

// Конструктор структури Інтервал
typedef struct s_interval{
    int a;
    int b;
    enum type_interval type;
}               Interval;


// Перелік функцій що відносяться до цієї структури
Interval  *SetInterval(int a, int b, enum type_interval type);
char  WhatTypeLeft(Interval *test);
char WhatTypeRight(Interval *test);
char Whatisreasltype(bool a, bool b);
enum type_interval FinilType(bool a, bool b);
void    PrintInterval(Interval *interval);
Interval    *DivideIntervals(Interval *first, Interval *second);
char Whatisreasltype1(char a, char b);
Interval *Multiplication_Int(Interval *first, Interval *second);
void PrintRes1(Interval *res);
char Type_dif(bool a);
Interval *Difference_Int(Interval *first, Interval *second);

#endif //INTERVAL_SAV_ASD_H
