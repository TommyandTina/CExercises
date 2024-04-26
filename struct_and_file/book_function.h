#ifndef BOOK_FUNCTION_H
#define BOOK_FUNCTION_H

#include "setting.h"

struct Book 
{
        int ISBN;
        char name[MAX_NAME_LENGTH];
        char author[MAX_NAME_LENGTH];
        char publishing_company[MAX_NAME_LENGTH];
        int publishing_year;
        char type[MAX_NAME_LENGTH];
        int price;
        int amount;
};

void printBook(struct Book book);
bool compare_book_ISBN(struct Book a, struct Book b);
bool compare_book_name(struct Book a, struct Book b);
int find_in_books(struct Book book[], int size, bool (*compare)(struct Book, struct Book), char compare_function_name[MAX_NAME_LENGTH]);
int writeToBook(struct Book *book,struct CurrentIndex *currentIdx);
int changeBookinfo(struct Book *book, int index);
void deleteBook(struct Book *book,int index , int amount_of_current_book);
void save_book_to_file(struct Book *book);
void load_book_from_file(struct Book *book);
// void book_management(struct Book *book, struct CurrentIndex *currentIdx);







#endif
