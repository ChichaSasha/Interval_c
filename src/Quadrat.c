/***
 *
 * Project name: Interval
 * File: Quadrat.c
 * Project was created by Chicha Olexandr on 15.12.19
 * Year: 2-nd
 * Specialization: Computer mathematics
 * Taras Shevchenko National University of Kyiv
 * e-mail: sashachicha13@gmail.com
 * phone number: +380957519417
 *
***/

#include "../headers/Quadrat.h"
#include "Set_of_Int.c"

//функція яка задає новий тип квадратного рівння
QuadraticInequalities   *SetIneq(float a, float b, float c, enum type_of_sign sign)
{
    QuadraticInequalities  *Inequaliti =  (QuadraticInequalities *) malloc(sizeof(QuadraticInequalities));
    Inequaliti->a = a;
    Inequaliti->b = b;
    Inequaliti->c = c;
    Inequaliti->sign = sign;
    return Inequaliti;
}

//функція яка вирішує рівння й повертає його розв'язки
set_intervals *Make_set(QuadraticInequalities test)
{
    set_intervals *Result = (set_intervals *) malloc(sizeof(2));
    float D, root1, root2;
    D = powf(test.b, 2.0) - 4 * test.a * test.c;
    if (D < 0)
    {
        printf("Wrong numbers, sry");
        return 0;
    } else
    {
        root1 = (-1*test.b - powf(D, 0.5 ))/ 2 * test.a;
        root2 = (-1*test.b + powf(D, 0.5)) / 2 * test.a;
        switch(test.sign) {
            case greater: {
                if (test.a == 0) {
                    float root;
                    root = -test.c / test.b;
                    Result->interval_array = (Interval *) malloc(sizeof(Interval));
                    Interval *int1;
                    int1 = SetInterval(root, 0, InfiniteRight_LeftOpen);
                    Result->interval_array = int1;
                    Result->size = 1;
                    return Result;
                }
                if (test.a > 0) {
                    if (D > 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        Interval *int2;
                        int1 = SetInterval(0, root1, InfiniteLeft_RightOpen);
                        int2 = SetInterval(root2, 0, InfiniteRight_LeftOpen);
                        Result->interval_array[0] = *int1;
                        Result->interval_array[1] = *int2;
                        Result->size = 2;
                        return Result;
                    }
                    if (D == 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval(root1, root1, Infinite);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }

                }
                if (test.a < 0) {
                    if (D > 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval(root1, root2, Closed);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }
                    if (D == 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval(root1, root1, Empty);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }
                }
            }
            case less: {
                if (test.a > 0) {
                    if (D > 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval( root1, root2, Opened);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }
                    if (D == 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval( root1, root1, Empty);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }

                }
                if (test.a < 0) {
                    if (D > 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval) * 2);
                        Interval *int1;
                        Interval *int2;
                        int1 = SetInterval( 0, root1, InfiniteLeft_RightOpen);
                        int2 = SetInterval( root2, 0, InfiniteRight_LeftOpen);
                        Result->interval_array[0] = *int1;
                        Result->interval_array[1] = *int2;
                        Result->size = 2;
                        return Result;
                    }
                    if (D == 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval( root1, root1, Infinite);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }
                }
                if (test.a == 0) {
                    float root;
                    root = test.c / test.b;
                    Result->interval_array = (Interval *) malloc(sizeof(Interval));
                    Interval *int1;
                    int1 = SetInterval( 0, root, InfiniteLeft_RightOpen);
                    Result->interval_array = int1;
                    Result->size = 1;
                    return Result;
                }
            }
            case less_equal: {
                if (test.a > 0) {
                    if (D > 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval( root1, root2, Closed);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }
                    if (D == 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval( root1, root1, SingleDot);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }

                }
                if (test.a < 0) {
                    if (D > 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval) * 2);
                        Interval *int1;
                        Interval *int2;
                        int1 = SetInterval( 0, root1, InfiniteLeft_RightClosed);
                        int2 = SetInterval( root2, 0, InfiniteRight_LeftClosed);
                        Result->interval_array[0] = *int1;
                        Result->interval_array[1] = *int2;
                        Result->size = 2;
                        return Result;
                    }
                    if (D == 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval(root1, root1, SingleDot);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }

                }
                if (test.a == 0) {
                    float root;
                    root = test.c / test.b;
                    Result->interval_array = (Interval *) malloc(sizeof(Interval));
                    Interval *int1;
                    int1 = SetInterval( 0, root, InfiniteLeft_RightClosed);
                    Result->interval_array = int1;
                    Result->size = 1;
                    return Result;
                }
            }
            case greater_equal: {
                if (test.a > 0) {
                    if (D > 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval) * 2);
                        Interval *int1;
                        Interval *int2;
                        int1 = SetInterval( 0, root1, InfiniteLeft_RightClosed);
                        int2 = SetInterval( root2, 0, InfiniteRight_LeftClosed);
                        Result->interval_array[0] = *int1;
                        Result->interval_array[1] = *int2;
                        Result->size = 2;
                        return Result;
                    }
                    if (D == 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval( root1, root1, SingleDot);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }

                }
                if (test.a < 0) {
                    if (D > 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval( root1, root2, Closed);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }
                    if (D == 0) {
                        Result->interval_array = (Interval *) malloc(sizeof(Interval));
                        Interval *int1;
                        int1 = SetInterval( root1, root1, SingleDot);
                        Result->interval_array = int1;
                        Result->size = 1;
                        return Result;
                    }

                }
                if (test.a == 0) {
                    float root;
                    root = test.c / test.b;
                    Result->interval_array = (Interval *) malloc(sizeof(Interval));
                    Interval *int1;
                    int1 = SetInterval( root, 0, InfiniteRight_LeftClosed);
                    Result->interval_array = int1;
                    Result->size = 1;
                    return Result;
                }
            }
            case equal: {
                if (test.a == 0) {
                    float root;
                    root = test.c / test.b;
                    Result->interval_array = (Interval *) malloc(sizeof(Interval));
                    Interval *int1;
                    int1 = SetInterval( root, root, SingleDot);
                    Result->interval_array = int1;
                    Result->size = 1;
                    return Result;
                }
                if (D > 0) {
                    Result->interval_array = (Interval *) malloc(sizeof(Interval));
                    Interval *int1;
                    Interval *int2;
                    int1 = SetInterval(root1, root1, SingleDot);
                    int2 = SetInterval( root2, root2, SingleDot);
                    Result->interval_array[0] = *int1;
                    Result->interval_array[1] = *int2;
                    Result->size = 2;
                    return Result;
                }
                if (D == 0) {
                    Result->interval_array = (Interval *) malloc(sizeof(Interval));
                    Interval *int1;
                    int1 = SetInterval( root1, root1, SingleDot);
                    Result->interval_array = int1;
                    Result->size = 1;
                    return Result;
                }
            }
            case not_equal: {
                if (test.a == 0) {
                    float root;
                    root = test.c / test.b;
                    Result->interval_array = (Interval *) malloc(sizeof(Interval) * 2);
                    Interval *int1;
                    Interval *int2;
                    int1 = SetInterval( 0, root, InfiniteLeft_RightOpen);
                    int2 = SetInterval( root, 0, InfiniteRight_LeftOpen);
                    Result->interval_array[0] = *int1;
                    Result->interval_array[1] = *int2;
                    Result->size = 2;
                    return Result;
                }
                if (D > 0) {
                    Result->interval_array = (Interval *) malloc(sizeof(Interval) * 3);
                    Interval *int1;
                    Interval *int2;
                    Interval *int3;
                    int1 = SetInterval( 0, root1, InfiniteLeft_RightOpen);
                    int2 = SetInterval( root1, root2, Opened);
                    int3 = SetInterval( root2, 0, InfiniteRight_LeftOpen);
                    Result->interval_array[0] = *int1;
                    Result->interval_array[1] = *int2;
                    Result->interval_array[2] = *int3;
                    Result->size = 3;
                    return Result;
                }
                if (D == 0) {
                    Result->interval_array = (Interval *) malloc(sizeof(Interval) * 2);
                    Interval *int1;
                    Interval *int2;
                    int1 = SetInterval( 0, root1, InfiniteLeft_RightOpen);
                    int2 = SetInterval( root1, 0, InfiniteRight_LeftOpen);
                    Result->interval_array[0] = *int1;
                    Result->interval_array[1] = *int2;
                    Result->size = 2;
                    return Result;
                }
            }
        }
    }
}

// функція яка порівнює масиви розв'язку систем й дає фінальний массив відповідь
set_intervals* find_solution(set_intervals* ints1, set_intervals* ints2)
{
    set_intervals* Result ;
    Result = Set_Insection(ints1, ints2);
    return Result;
}
