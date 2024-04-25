#ifndef SETTING_H_
#define SETTING_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_MEMBERS 100
#define MAX_BOOK 100
#define MAX_TICKET 100
#define MAX_NAME_LENGTH 100  // Độ dài tên tối đa

struct CurrentIndex
{
    int member_index;
    int book_index;
    int ticket_index;
};

enum options {
    START = 1,
    MEMBER_MANAGEMENT =2,
    BOOK_MANAGEMENT = 3,
    BORROW_BOOK = 4,
    RETURN_BOOK = 5,
    STATISTIC_ANALYSIS = 6,
    EXIT = 7
} ;

int countDays(int day, int month, int year);
void printDate_from_countDays(int totalDays);
void reduceCurrentIndex(int *index);
void increaseCurrentIndex(int *index);
#endif




