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
 *
***/

#include "../headers/Intarval.h"

// Функція, що задає інтервал
Interval  *SetInterval(int a, int b, enum type_interval type)
{
    Interval *interval = (Interval*) malloc(sizeof(Interval));
    interval->a = a;
    interval->b = b;
    interval->type = type;
    return interval;
}

//функція для визначення типу лівого кінця інтервалу
//true - закритий
//false - відкритий
char  WhatTypeLeft(Interval *test)
{
    if (test->type == Closed || test->type == SingleDot || test->type == HalfClosedLeft ||
    test->type == InfiniteRight_LeftClosed)
    {
        return true;
    }else
    {
        return false;
    }
}

//функція для визначення типу правого кінця інтервалу
//true - закритий
//false - відкритий
char WhatTypeRight(Interval *test)
{
    if (test->type == Closed || test->type == SingleDot || test->type == HalfClosedRight ||
            test->type == InfiniteLeft_RightClosed)
    {
        return true;
    }else
    {
        return false;
    }
}

//функція для визначення типу реального типу**(відкритого чи закрито відповідно до умови)
//true - закритий
//false - відкритий
char Whatisreasltype(bool a, bool b)
{
    if (a == true &&  b == true)
    {
        return true;
    }else
    {
        return false;
    }
}

// функція що генерує новий тип інтервалу
enum type_interval FinilType(bool a, bool b)
{
    Interval *Result = (Interval*) malloc(sizeof(Interval));

    if (a == false && b == false)
    {
        Result->type = Opened;
    }

    if (a == true && b == true)
    {
        Result->type = Closed;
    }

    if (a == false && b == true)
    {
        Result->type = HalfClosedRight;
    }
    if (a == true && b == false)
    {
        Result->type = HalfClosedLeft;
    }
    return Result->type;
}

//функція для виводу на екран
void    PrintInterval(Interval *interval)
{
    switch (interval->type)
    {
        case Empty:
            printf("");
            break;
        case Opened:
            printf("(%d, %d)\n", interval->a, interval->b);
            break;
        case SingleDot:
            printf("[%d, %d]\n ", interval->a, interval->b);
            break;
        case Closed:
            printf("[%d, %d]\n", interval->a, interval->b);
            break;
        case HalfClosedLeft:
            printf("[%d, %d)\n", interval->a, interval->b);
            break;
        case HalfClosedRight:
            printf("(%d, %d]\n", interval->a, interval->b);
            break;
        default:
            break;
    }
}

// функція, яка обраховує перетин 2 інтервалів
// всередині створена типізація для нескінченних кінців інтервалу
Interval    *DivideIntervals(Interval *first, Interval *second)
{
    Interval *Result = (Interval*) malloc(sizeof(Interval));

    // вводимо поняття безкінечності
    float  k = 999999999;

    if (first->type == Infinite || first->type == InfiniteLeft_RightClosed || first->type == InfiniteLeft_RightOpen) {
        first->a = -1 *  k;
    }
    if (first->type == Infinite || first->type == InfiniteRight_LeftClosed || first->type == InfiniteRight_LeftOpen) {
        first->b =  k;
    }
    if (second->type == Infinite || second->type == InfiniteLeft_RightOpen || second->type == InfiniteLeft_RightClosed)
    {
        second->a = -1 * k;
    }
    if (second->type == Infinite || second->type == InfiniteRight_LeftOpen || second->type == InfiniteRight_LeftClosed)
    {
        second->b = k;
    }
    //----------------------------------------------------------------------
    //----------------------------------------------------------------------

    // перевірка чи 1 з них пустий або точок перетину не існує
    if (first->type == Empty || second->type == Empty || first->a > second->b || first->b < second->a) {
        Result->a = 0;
        Result->b = 0;
        Result->type = Empty;
        return Result;
    }

    // перший інтервал повснітю належить 2
    if (first->a < second->a && second->b < first->b) {
        Result->a = second->a;
        Result->b = second->b;
        Result->type = second->type;
        return Result;
    }

    // 2 інтервал повснітю належить 1
    if (first->a > second->a && second->b > first->b) {
        Result->a = first->a;
        Result->b = first->b;
        Result->type = second->type;
        return Result;
    }

    if (first->b == second->a && first->a == second->b) {
        if (WhatTypeRight(first) == WhatTypeLeft(second) && WhatTypeLeft(second) == true) {
            Result->a = first->b;
            Result->b = second->a;
            Result->type = Closed;
        } else {
            Result->a = 0;
            Result->b = 0;
            Result->type = Empty;
        }
        return Result;
    }

    // Однакові інтервали
    if (first->a == second->a && second->b == first->b) {
        Result->a = first->a;
        Result->b = first->b;
        Result->type = FinilType(Whatisreasltype(WhatTypeLeft(first), WhatTypeLeft(second)),
                                 Whatisreasltype(WhatTypeRight(first), WhatTypeRight(second)));
        return Result;
    }

    //----------------------------------------------------

    // 2 лежить частинно в 1
    if (first->a < second->a && second->b > first->b) {
        Result->a = second->a;
        Result->b = first->b;
        Result->type = FinilType(WhatTypeLeft(second), WhatTypeRight(first));
        return Result;
    }


    // ---------------------------------------------------


    // якщо 1 частинно знах в 2
    if (first->a > second->a && first->a < second->b && second->b < first->b)
    {
        Result->a = first->a;
        Result->b = second->b;
        Result->type = FinilType(WhatTypeLeft(first),WhatTypeRight(second));
        return Result;
    }
    // ліва однакова
    if (first->a == second->a && second->b < first->b)
    {
        Result->a = first->a;
        Result->b = second->b;
        Result->type = FinilType(Whatisreasltype(WhatTypeLeft(first),WhatTypeLeft(second)),WhatTypeRight(second));
        return Result;
    }
    //liva odnakova v2
    if (first->a == second->a && second->b > first->b)
    {
        Result->a = first->a;
        Result->b = first->b;
        Result->type = FinilType(Whatisreasltype(WhatTypeLeft(first),WhatTypeLeft(second)),WhatTypeRight(first));
        return Result;
    }

    //prava odnakova v2
    if (first->a > second->a && second->b == first->b)
    {
        Result->a = first->a;
        Result->b = first->b;
        Result->type = FinilType(WhatTypeLeft(first), Whatisreasltype(WhatTypeRight(first),WhatTypeRight(second)));
        return Result;
    }

    //prava odnakova v1
    if (first->a < second->a && second->b == first->b)
    {
        Result->a = second->a;
        Result->b = first->b;
        Result->type = FinilType(WhatTypeRight(second),Whatisreasltype(WhatTypeRight(first),WhatTypeRight(second)));
        return Result;
    }
}


//------------------------------------------

// функція для визначення одного з типів кінців інтервалу для об'єднання
char Whatisreasltype1(char a, char b)
{
    if (a == false &&  b == false)
    {
        return false;
    }else
    {
        return true;
    }
}

// функція для визначення об'єднання 2 інтервалів
// може повертати массив
// всередині визначено поняття нескінченності
Interval *Multiplication_Int(Interval *first, Interval *second)
{
    Interval *res = (Interval*) malloc(sizeof(Interval)*2) ;


    // ------------------------------------------------------------
    // вводимо поняття безкінечності
    float  k = INFINITY;

    if (first->type == Infinite || first->type == InfiniteLeft_RightClosed || first->type == InfiniteLeft_RightOpen) {
        first->a = -1 * k;
    }
    if (first->type == Infinite || first->type == InfiniteRight_LeftClosed || first->type == InfiniteRight_LeftOpen) {
        first->b = k;
    }
    if (second->type == Infinite || second->type == InfiniteLeft_RightOpen || second->type == InfiniteLeft_RightClosed)
    {
        second->a = -1 * k;
    }
    if (second->type == Infinite || second->type == InfiniteRight_LeftOpen || second->type == InfiniteRight_LeftClosed)
    {
        second->b = k;
    }
    // -------------------------------------------------------------
    //однакові інтервали
    if (first->a == second->a && first->b == second->b) {
        res->a = first->a;
        res->b = second->b;
        res->type = FinilType(Whatisreasltype1(WhatTypeLeft(first), WhatTypeLeft(second)),
                              Whatisreasltype1(WhatTypeRight(second), WhatTypeRight(first)));
        return res;
    }
    // перетин між фьорст a == сек b
    if (first->a == second->b)
    {
        res->a = second->a;
        res->b = first->b;
        res->type = FinilType(WhatTypeLeft(second), WhatTypeRight(first));
        return res;
    }

    //1 лежить в 2
    if (first->a < second->a && first->b > second->b)
    {
        res->a = first->a;
        res->b = first->b;
        res->type = FinilType(WhatTypeLeft(first), WhatTypeRight(first));
        return res;
    }

    //2 лежить в 1
    if (first->a > second->a && first->b < second->b)
    {
        res->a = second->a;
        res->b = second->b;
        res->type = FinilType(WhatTypeLeft(second), WhatTypeRight(second));
        return res;
    }


    // перетин між фьорст б == сек а
    if (first->b == second->a)
    {
        res->a = first->a;
        res->b = second->b;
        res->type = FinilType(WhatTypeLeft(first), WhatTypeRight(second));
        return res;
    }

    // перетин між фьорст б і сек а
    if (first->a < second->a && first->b > second->a && second->b > first->b)
    {
        res->a = first->a;
        res->b = second->b;
        res->type = FinilType(WhatTypeLeft(first), WhatTypeRight(second));
        return res;
    }

    // перетин між фьорст a і сек b
    if (first->a > second->a && first->a < second->b && second->b < first->b)
    {
        res->a = second->a;
        res->b = first->b;
        res->type = FinilType(WhatTypeLeft(second), WhatTypeRight(first));
        return res;
    }


    // лівий край однаковий і 2 більший
    if(first->a == second->a && first->b < second->b)
    {
        res->a = first->a;
        res->b = second->b;
        res->type = FinilType(Whatisreasltype1(WhatTypeLeft(first),WhatTypeLeft(second)), WhatTypeRight(second));
        return res;
    }

    //лівий однаковий і правий більший
    if(first->a == second->a && first->b > second->b)
    {
        res->a = first->a;
        res->b = first->b;
        res->type = FinilType(Whatisreasltype1(WhatTypeLeft(first),WhatTypeLeft(second)), WhatTypeRight(first));
        return res;
    }

    //правий однаковий лівий менший
    if(first->a < second->a && first->b == second->b)
    {
        res->a = first->a;
        res->b = first->b;
        res->type = FinilType(WhatTypeLeft(first),Whatisreasltype1(WhatTypeRight(first), WhatTypeRight(second)));
        return res;
    }

    //правий однаковий і лівий більший
    if(first->a > second->a && first->b == second->b)
    {
        res->a = second->a;
        res->b = first->b;
        res->type = FinilType(WhatTypeLeft(second),Whatisreasltype1(WhatTypeRight(first), WhatTypeRight(second)));
        return res;
    }

    // усі випадки коли потрібно вивести 2 інтервали
    if (second->b < first->a || first->b < second->a || ((first->a == second->b && Whatisreasltype1(WhatTypeLeft(first),
            WhatTypeRight(second) == false))) || (first->b == second->a && Whatisreasltype1(WhatTypeRight(first),
                                                                                                                                                                                    WhatTypeLeft(second) == false)))
    {
        res[0] = *first;
        res[1] = *second;
        return res;
    }
}


// ------------------------------------------------

// функція для виводу масива інтрвалів
void PrintRes1(Interval *res)
{
    for (int i = 0; i < sizeof(res)/ sizeof(int) + 1; i ++)
    {
        PrintInterval(&res[i]);
    }
}

// функція для визначення кінця різниці інтервалів
char Type_dif(bool a)
{
    if (a == true)
    {
        return false;
    }else
    {
        return true;
    }
}

//функція для визначення різниці 2 інтервалів
// може повертати масив
Interval *Difference_Int(Interval *first, Interval *second)
{
    Interval *res = (Interval *) malloc(sizeof(Interval) * 2);

    Interval *res_test ;

    // ------------------------------------------------------------
    // вводимо поняття безкінечності
    float  k = INFINITY;

    if (first->type == Infinite || first->type == InfiniteLeft_RightClosed || first->type == InfiniteLeft_RightOpen) {
        first->a = -1 * k;
    }
    if (first->type == Infinite || first->type == InfiniteRight_LeftClosed || first->type == InfiniteRight_LeftOpen) {
        first->b = k;
    }
    if (second->type == Infinite || second->type == InfiniteLeft_RightOpen || second->type == InfiniteLeft_RightClosed)
    {
        second->a = -1 * k;
    }
    if (second->type == Infinite || second->type == InfiniteRight_LeftOpen || second->type == InfiniteRight_LeftClosed)
    {
        second->b = k;
    }

    //---------------------------------------------------
    res_test = DivideIntervals(first,second);
    //перевірка на то чи є перетин пустим
    if(res_test->type == Empty)
    {
        res->a = first->a;
        res->b = first->b;
        res->type = first->type;
        return res;
    }
    // він і є перетин
    if(res_test->type == first->type && res_test->a == first->a && res_test->b == first->b)
    {
        res->a = 0;
        res->b = 0;
        res->type = Empty;
        return res;
    }

    // 2 кінці не співпадають
    if (res_test->a == first->a && res_test->b == first->b && WhatTypeLeft(res_test) != WhatTypeLeft(first) &&
        WhatTypeRight(res_test) != WhatTypeRight(first))
    {
        res[0].a = first->a;
        res[0].b = first->a;
        res[0].type = Closed;

        res[1].a = first->b;
        res[1].b = first->b;
        res[1].type = Closed;
        return res;
    }

    //лівий не співпадає
    if (res_test->a == first->a && res_test->b == first->b && WhatTypeLeft(res_test) != WhatTypeLeft(first))
    {
        res->a = first->a;
        res->b = first->a;
        res->type = Closed;

        return res;

    }
    //правий не співпадає
    if (res_test->a == first->a && res_test->b == first->b && WhatTypeRight(res_test) != WhatTypeRight(first))
    {
        res->a = first->b;
        res->b = first->b;
        res->type = Closed;

        return res;
    }

    //перетин є частиною інтервалу без кінців
    if (res_test->a > first->a && res_test->b < first->b)
    {
        res[0].a = first->a;
        res[0].b = res_test->a;
        res[0].type = FinilType(WhatTypeLeft(first), Type_dif(WhatTypeLeft(res_test)));

        res[1].a = res_test->b;
        res[1].b = first->b;
        res[1].type = FinilType(Type_dif(WhatTypeRight(res_test)), WhatTypeRight(first));

        return res;
    }

    // ліва однакова права менша
    if(res_test->a == first->a && res_test->b < first->b)
    {
        if(WhatTypeLeft(res_test) == WhatTypeLeft(first))
        {
            res->a = res_test->b;
            res->b = first->b;
            res->type = FinilType(Type_dif(WhatTypeRight(res_test)), WhatTypeRight(first));
        } else
        {
            res[0].a = first->a;
            res[0].b = first->a;
            res[0].type = Closed;

            res[1].a = res_test->b;
            res[1].b = first->b;
            res[1].type = FinilType(Type_dif(WhatTypeRight(res_test)), WhatTypeRight(first));
        }
        return res;
    }

    // права однакова ліва менша
    if(res_test->a < first->a && res_test->b == first->b)
    {
        if(WhatTypeRight(res_test) == WhatTypeRight(first))
        {
            res->a = first->a;
            res->b = res_test->a;
            res->type = FinilType(WhatTypeLeft(first), Type_dif(WhatTypeLeft(res)));
        } else
        {
            res[0].a = first->b;
            res[0].b = first->b;
            res[0].type = Closed;

            res[1].a = res_test->b;
            res[1].b = first->b;
            res[1].type = FinilType(WhatTypeLeft(first), Type_dif(WhatTypeLeft(res)));
        }
        return res;
    }

}
