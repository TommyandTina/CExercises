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

// bool compare

// int find_in_lib_ticket(struct LibTicket lib_ticket[], int size, bool (*compare)(struct LibTicket, struct LibTicket), char compare_function_name[MAX_NAME_LENGTH]) {
//     for (int i = 0; i < size; i++) {
//         if (compare(lib_ticket[i], "compare_function_name")) {
//             return i;
//         }
//     }
// }

void updateMemberData_AddBorrowTicket(struct Member *member, struct Book book) {
    //add book amount, isbn to member
    member->borrowed_ISBN[member->borrowed_book] = book.ISBN;
    member->borrowed_book++;
}

int updateBookData_AddBorrowTicket(struct Book *book) {
    return book->amount--;
}

int writeToLibTicket(struct LibTicket *lib_ticket,struct CurrentIndex *currentIdx, struct Member member_borrowing,int member_index, struct Book book_borrowed, int book_index) {
    int day, month, year;
    printf("Enter borrowing date: ");
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

#if 0
// if (book_amount[book_index] > 0) {
//         // Tăng số lượt mượn, cập nhật thông tin của member
//         member_borrowed_book[index]++;
//         lib_ticket_borrowed_book[number_of_current_ticket_index]++;
//         member_borrowed_ISBN[index][member_borrowed_book[index]-1] = book_ISBN[book_index];
//         // Giảm số lượng sách
//         book_amount[book_index]--;
//         // Lưu thông tin về phiếu mượn
//         lib_ticket_id[number_of_current_ticket_index] = number_of_current_ticket_index;
//         lib_ticket_member_id[number_of_current_ticket_index] = member_id[index];
//         lib_ticket_borrow_date[number_of_current_ticket_index] = countDays(day, month, year);
//         lib_ticket_return_date_expected[number_of_current_ticket_index] = countDays(day, month, year) + 7;
//         lib_ticket_return_date_real[number_of_current_ticket_index] = 0;
//         // if(lib_ticket_borrowed_book[number_of_current_ticket_index] - 1 == 0) {
//         //     lib_ticket_ISBN[number_of_current_ticket_index] = (int*)malloc(MAX_BOOK * sizeof(int));
//         // }
//         lib_ticket_ISBN[number_of_current_ticket_index][lib_ticket_borrowed_book[number_of_current_ticket_index]-1] = book_ISBN[book_index]; // ghi ISBN vào ticket_ISBN

//         //add sách vào ticket
//         char answer = 'y'; // giá trị mặc định
//         while (answer == 'y' || answer == 'Y') { //vòng lặp để mượn thêm cuốn
//             printf("Do you want to borrow more book? (y/n) "); // hỏi còn mượn thêm cuốn không
//             scanf(" %c", &answer); // đọc giá trị
//             getchar();
//             if (answer == 'y' || answer == 'Y') { // nếu có thì tìm tên sách xong tra ISBN để đưa vào index kế của ticket_ISBN
//                 printf("Enter book name to borrow: "); // hỏi tên sách
//                 fgets(input_book_name, MAX_NAME_LENGTH, stdin);
//                 input_book_name[strlen(input_book_name)-1] = '\0'; // loại bỏ ký tự \n
//                 book_index = search_index_to_get_info_fromstr(input_book_name,book_name,MAX_NAME_LENGTH); // tìm ISBN
//                 if (book_index != -1) { // nếu tìm thấy sách
//                     printf("Book found\n");
//                     // lib_ticket_ISBN[number_of_current_ticket_index] = (int*)realloc(lib_ticket_ISBN[number_of_current_ticket_index], sizeof(int) * (member_borrowed_book[index]+1)); // mở rộng ticket_ISBN
//                     lib_ticket_ISBN[number_of_current_ticket_index][lib_ticket_borrowed_book[number_of_current_ticket_index]] = book_ISBN[book_index]; // ghi ISBN vào ticket_ISBN
//                     member_borrowed_ISBN[index][member_borrowed_book[index]] = book_ISBN[book_index];// ghi vào member
//                     member_borrowed_book[index]++; // tăng số lượt mượn ở member
//                     lib_ticket_borrowed_book[number_of_current_ticket_index]++; // tăng số lượt mượn ở ticket
//                     book_amount[book_index]--;   // Giảm số lượng sách                     
//                 }
//             }
//         }

//         //in ra thông tin ticket
//     printLibTicket(lib_ticket, number_of_current_ticket_index);
//     } else {
//         printf("Book is out of stock\n");
//     }
#endif