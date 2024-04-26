#ifndef LIB_TICKET_FUNCTION_H
#define LIB_TICKET_FUNCTION_H

#include "setting.h"
#include "member_function.h"
#include "book_function.h"

struct BorrowingMember {
    int id;
    int index;
};
struct BorrowedBook {
    int ISBN;
    int index;
};
struct LibTicket{
    int id;
    struct BorrowingMember member;
    int borrow_date;
    int return_date_expected;
    int return_date_real;
    struct BorrowedBook borrowed_book[MAX_BOOK];
    int borrowed_book_amount;
};

void printLibTicket(struct LibTicket lib_ticket);
void updateMemberData_AddBorrowTicket(struct Member *member, struct Book book);
int updateBookData_AddBorrowTicket(struct Book *book);
int writeToLibTicket(struct LibTicket *lib_ticket,struct CurrentIndex *currentIdx, struct Member member_borrowing,int member_index, struct Book book_borrowed, int book_index);

int compare_ticket_index(struct LibTicket a, struct LibTicket b);
int find_ticket_book_ISBN(struct LibTicket a, struct LibTicket b);
int find_in_lib_ticket(struct LibTicket lib_ticket[], int size, int (*compare)(struct LibTicket, struct LibTicket), char compare_function_name[MAX_NAME_LENGTH]);
int returnLibTicket(struct LibTicket *lib_ticket,int ticket_index,int ISBN_index_libTicket ,struct CurrentIndex *currentIdx, struct Member *member_borrowing, struct Book *book_borrowed);
void save_lib_ticket_to_file(struct LibTicket *lib_ticket);
void load_lib_ticket_from_file(struct LibTicket *lib_ticket);
#endif