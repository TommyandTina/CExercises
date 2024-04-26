#include "lib_ticket_function.h"
// #include "book_function.h"
// #include "member_function.h"


void printLibTicket(struct LibTicket lib_ticket){
    printf("----------------------------- \n");
    printf("id: %d\n", lib_ticket.id);
    printf("member_id: %d\n", lib_ticket.member.id);
    printf("borrow_date: %d\n", lib_ticket.borrow_date);
    printf("return_date_expected: %d\n", lib_ticket.return_date_expected);
    printf("return_date_real: %d\n", lib_ticket.return_date_real);
    printf("ISBN: ");
    for (int i = 0; i < MAX_BOOK; i++) {
        if(lib_ticket.borrowed_book[i].ISBN > 0){
            printf("%d ", lib_ticket.borrowed_book[i].ISBN);
        }
    }
    printf("\n");
    printf("borrowed_book: %d\n", lib_ticket.borrowed_book_amount);
    printf("----------------------------- \n");
}

/*finding function*/
int compare_ticket_index(struct LibTicket a, struct LibTicket b) {
    return a.id == b.id;
}

int find_ticket_book_ISBN(struct LibTicket a, struct LibTicket b) {
    struct LibTicket find_this;
    struct LibTicket buf;
    /*Buf is a larger var, find_this is a smaller var (only have ISBN at [0]). Return index of ISBN in array*/
    if(a.borrowed_book_amount<b.borrowed_book_amount){
        buf = b;
        find_this = a;
    } else {
        buf = a;
        find_this = b;
    }
        for (int i = 0; i < buf.borrowed_book_amount; i++) {
        if(find_this.borrowed_book[0].ISBN == buf.borrowed_book[i].ISBN){
            return i;
        }
    }
    return -1;
}

int find_in_lib_ticket(struct LibTicket lib_ticket[], int size, int (*compare)(struct LibTicket, struct LibTicket), char compare_function_name[MAX_NAME_LENGTH]) {
    struct LibTicket find_this;
    if(strcmp(compare_function_name, "compare_ticket_index") == 0){
        printf("Enter id to search: ");
        scanf(" %d", &find_this.id);
        getchar();
        for (int i = 0; i < size; i++) {
            if (compare(lib_ticket[i], find_this )) {
                return i;
                //return ticket index
            }
        }
    } else if(strcmp(compare_function_name, "find_ticket_book_ISBN") == 0){
        printf("Enter ISBN to search: ");
        scanf(" %d", &find_this.borrowed_book[0].ISBN);
        getchar();
        if(size == 1){
                //Search on 1 library ticket for book
                return compare(*lib_ticket, find_this);
                //return ISBN index
        }
    }
    return -1;
}

/*update data function*/
void updateMemberData_AddBorrowTicket(struct Member *member, struct Book book) {
    //add book amount, isbn to member
    member->borrowed_ISBN[member->borrowed_book] = book.ISBN;
    member->borrowed_book++;
}

void updateMemberData_ReturnBorrowTicket(struct Member *member, int book_index_from_member) {
    //remove book amount, isbn from member
    for(int i = book_index_from_member ; i < member->borrowed_book; i++) {
        // start at book we want to remove, then copy next book to the current
        member->borrowed_ISBN[i] = member->borrowed_ISBN[i+1];
    }
    member->borrowed_book--;
}

void updateLibTicketData_ReturnBorrowTicket(struct LibTicket *lib_ticket, int book_index_from_lib_ticket) {
    for(int i = book_index_from_lib_ticket ; i < lib_ticket->borrowed_book_amount; i++) {
        // start at book we want to remove, then copy next book to the current
        lib_ticket->borrowed_book[i] = lib_ticket->borrowed_book[i+1];
    }
    lib_ticket->borrowed_book_amount--;
}

int updateBookData_AddBorrowTicket(struct Book *book) {
    return book->amount--;
}

int updateBookData_ReturnBorrowTicket(struct Book *book) {
    return book->amount++;
}

/*process ticket*/
int writeToLibTicket(struct LibTicket *lib_ticket,struct CurrentIndex *currentIdx, struct Member member_borrowing,int member_index, struct Book book_borrowed, int book_index) {
    int day, month, year;
    printf("Enter borrowing date: (dd/mm/yyyy)");
    scanf("%d/%d/%d", &day, &month, &year);
    getchar();

    lib_ticket->id = currentIdx->ticket_index;
    lib_ticket->member.id = member_borrowing.id;
    lib_ticket->member.index = member_index;
    lib_ticket->borrow_date = countDays(day, month, year);
    lib_ticket->return_date_expected = countDays(day, month, year) + 7;
    lib_ticket->return_date_real = 0;
    lib_ticket->borrowed_book[lib_ticket->borrowed_book_amount].ISBN = book_borrowed.ISBN;
    lib_ticket->borrowed_book[lib_ticket->borrowed_book_amount].index = book_index;
    lib_ticket->borrowed_book_amount++;
    currentIdx->ticket_index++;

    return currentIdx->ticket_index;
}

int returnLibTicket(struct LibTicket *lib_ticket,int ticket_index,int ISBN_index_libTicket ,struct CurrentIndex *currentIdx, struct Member *member_borrowing, struct Book *book_borrowed) {
    char answer[2];
    printf("Do you want to continue returning book? (y/n): ");
    scanf(" %c", answer);
    getchar();
    if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
            //RETURN TICKET
            int penalty_fee = 0;
            int book_index_from_ticket = ISBN_index_libTicket;
            int book_index_from_member = lib_ticket[ticket_index].member.index;
            int book_index_from_book = lib_ticket[ticket_index].borrowed_book[book_index_from_ticket].index;

            // update current date of ticket
            printf("Enter current day/month/year: ");
            int day, month, year;
            scanf("%d/%d/%d", &day, &month, &year);
            getchar();
            lib_ticket[ticket_index].return_date_real = countDays(day, month, year); // update current date of ticket

            /*PROCESSING...*/                   
            if (book_index_from_ticket != -1) {
                printf("Book found, are you missing it? (y/n): ");
                scanf(" %c", answer);
                getchar();
                if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {

                    penalty_fee = book_borrowed[book_index_from_book].price * 2;
                    printf("Penalty fee: %d\n", book_borrowed[book_index_from_book].price * 2);      
                } else {
                    int diff_day = countDays(day, month, year)- lib_ticket[ticket_index].return_date_expected;
                    if ( diff_day > 0) {
                        penalty_fee = book_borrowed[book_index_from_book].price * diff_day;
                        printf("Penalty fee: %d\n", book_borrowed[book_index_from_book].price * diff_day);
                    }
                }


            /*BOOK RETURNING...*/
            updateBookData_ReturnBorrowTicket(&book_borrowed[book_index_from_book]);

            /*MEMBER RETURNING...*/
            updateMemberData_ReturnBorrowTicket(&member_borrowing[lib_ticket[ticket_index].member.index], book_index_from_member); 

            /*TICKET RETURNING...*/
            updateLibTicketData_ReturnBorrowTicket(&lib_ticket[ticket_index], book_index_from_ticket);
            reduceCurrentIndex(&currentIdx->ticket_index);
            return penalty_fee;
        }
    } else {
        printf("Returning canceled OR book not found\n");
        return -1;
    }
    return -1;      
}             

void save_lib_ticket_to_file(struct LibTicket *lib_ticket) {
    FILE *file = fopen("lib_ticket_data.bin", "wb");
    if (file != NULL) {
        fwrite(lib_ticket, sizeof(struct LibTicket), MAX_TICKET, file);
        fclose(file);
    } else {
        printf("Cannot open file\n");
    }
}

void load_lib_ticket_from_file(struct LibTicket *lib_ticket) {
    FILE *file = fopen("lib_ticket_data.bin", "rb");
    if (file != NULL) {
        fread(lib_ticket, sizeof(struct LibTicket), MAX_TICKET, file);
        // fseek(file, 0, SEEK_SET);
        fclose(file);
    } else {
        // printf("Cannot open file\n");
    }
}