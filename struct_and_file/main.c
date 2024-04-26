#include "setting.h"
#include "member_function.h"
#include "book_function.h"
#include "lib_ticket_function.h"

int main(){
    struct Member member[MAX_MEMBERS];
    struct Book book[MAX_BOOK];
    struct LibTicket lib_ticket[MAX_TICKET];
    struct CurrentIndex currentIdx = {
        0, 0, 0,
    };

#if 0
    int number_of_current_member_index = 0;
    int number_of_current_book_index = 0;
    int number_of_current_ticket_index = 0;
    int day, month, year;

    int member_id[MAX_MEMBERS];
    char member_name[MAX_MEMBERS][MAX_NAME_LENGTH];
    int member_citizen_ID[MAX_MEMBERS];
    int member_dayOfBirth[MAX_MEMBERS];
    char member_email[MAX_MEMBERS][MAX_NAME_LENGTH];
    char member_gender[MAX_MEMBERS][MAX_NAME_LENGTH];
    int member_register_date[MAX_MEMBERS];
    int member_expired_date[MAX_MEMBERS];
    int member_borrowed_ISBN[MAX_MEMBERS][MAX_BOOK];
    int member_borrowed_book[MAX_MEMBERS];
    memset(member_borrowed_book, 0, sizeof(member_borrowed_book));

    int book_ISBN[MAX_BOOK];
    char book_name[MAX_BOOK][MAX_NAME_LENGTH];
    char book_author[MAX_BOOK][MAX_NAME_LENGTH];
    char book_publishing_company[MAX_BOOK][MAX_NAME_LENGTH];
    int book_publishing_year[MAX_BOOK];
    char book_type[MAX_BOOK][MAX_NAME_LENGTH];
    int book_price[MAX_BOOK];
    int book_amount[MAX_BOOK];

    int lib_ticket_id[MAX_TICKET];
    int lib_ticket_member_id[MAX_TICKET];
    int lib_ticket_borrow_date[MAX_TICKET];
    int lib_ticket_return_date_expected[MAX_TICKET];
    int lib_ticket_return_date_real[MAX_TICKET];
    int lib_ticket_ISBN[MAX_TICKET][MAX_BOOK];
    int lib_ticket_borrowed_book[MAX_TICKET];
    memset(lib_ticket_borrowed_book, 0, sizeof(lib_ticket_borrowed_book));
    // int lib_ticket_book_alive[MAX_TICKET];
#endif


    enum options input_option;
    while(1) {
        printf("Enter an option number (1 - START - DATA INIT (RESET DATA), 2 - MEMBER_MANAGEMENT, 3 - BOOK_MANAGEMENT, 4 - BORROW_BOOK, 5 - RETURN_BOOK, 6 - STATISTIC_ANALYSIS, 7 - EXIT): ");
        scanf(" %d", &input_option);
        getchar();
        switch (input_option) {
            case START:
            printf("Data init, choose this option again can lost all data\n");

            break;
#if 0 //sửa lại find in member
            case MEMBER_MANAGEMENT:
            while(1)
            {
                // char member_name_to_search[MAX_NAME_LENGTH];  // Khai báo biến
                int option;
                printf("Do you want to add, search or change a member (1-add, 2-search by name, 3-change info, 4-watch members list,5-search by citizen_id,6-search book borrowed by name and delete ?, 7-exit) ?");
                scanf(" %d", &option);
                getchar();

                if(option == 1)
                {
                    writeToMember(&member[currentIdx.member_index], &currentIdx);
                    printf("current member index is %d\n",currentIdx.member_index);
                }
                else if(option == 2) 
                {
                    printf("Only name affect, don't use ID\n");
                    int index = find_in_members(member,MAX_NAME_LENGTH,compare_name,"compare_name");
                    if(index != -1)
                    {
                        printMember(&member[index]);
                        printf("member index is %d\n",index);
                    }
                    else
                    {
                        printf("Member not found\n");
                    }

                }
                else if(option == 3)
                {
                    printf("Only name affect, don't use ID\n");
                    int index = find_in_members(member,MAX_NAME_LENGTH,compare_name,"compare_name");
                    if(index == -1)
                    {
                        printf("Member not found\n");
                    }
                    else
                    {
                        changeMemberinfo(&member[index],index);
                    }
                }
                else if (option == 4)
                {
                    printf("Option 4: Current members:\n");
                    for(int i = 0; i < currentIdx.member_index; i++)
                    {
                        printMember(&member[i]);
                        printf("member index is %d\n",i);
                        printf("----------------------------\n");
                    }
                }
                else if (option == 5)
                {
                    printf("Only citizen ID affect, don't use name\n");
                    int new_index = find_in_members(member,sizeof(int),compare_Citizen_id,"compare_Citizen_id");
                    printf("Index: %d\n", new_index);
                    if (new_index != -1)
                    {
                        printMember(&member[new_index]);
                    }
                    else
                    {
                        printf("User not found\n");
                    }
                }
                else if (option == 6)
                {
                    printf("Only name affect, don't use ID\n");
                    int index = find_in_members(member,MAX_NAME_LENGTH,compare_name,"compare_name");
                    if (index != -1)
                    {
                        printMember(&member[index]);
                        printf("Do you want to delete this member (y/n): ");
                        char delete_member;
                        scanf(" %c", &delete_member);
                        getchar();
                        if (delete_member == 'y' || delete_member == 'Y') {
                            // Move elements to the right of the deleted element
                            deleteMember(member,index,currentIdx.member_index);
                            reduceCurrentIndex(&currentIdx.member_index);
                            printf("Member deleted\n");
                        }
                        else {
                            printf("Member not deleted\n");
                        }
                    }
                    else
                    {
                        printf("Member not found\n");
                    }
                } 
                else if (option == 7) 
                {
                    //WRTIE TO FILE
                    break;
                }
            }                
                break;

            case BOOK_MANAGEMENT:
            while(1) {
                printf("Enter an option number for book management (1 - get_book_list, 2 - add_book, 3 - change_info, 4 - delete_book, 5 - search_book_from_ISBN, 6 - search_book_from_name, 7 - exit): ");
                int input_option_book;
                scanf(" %d", &input_option_book);
                getchar();
            
            if(input_option_book == 1) {
                for (int i = 0; i < currentIdx.book_index; i++) {
                    printBook(book[i]);
                }
                printf("\n");
                
            } 
            else if (input_option_book == 2) {
                int book_amount = writeToBook(book, &currentIdx);
                printf("Book amount right now: %d\n", book_amount);
            }
            else if (input_option_book == 3) {
                printf("Enter name to change: ");
                int index = find_in_books(book, MAX_NAME_LENGTH, compare_book_name, "compare_book_name");
                if(index == -1){
                    printf("Book not found\n");
                }
                else{
                    int result = changeBookinfo(book, index);
                    if (result == -1) {
                        printf("Book cannot be changed\n");
                    }
                    else {
                        printf("Book changed\n");
                    }
                }

            }
            else if (input_option_book == 4) {
                printf("Only ISBN affect, don't use name\n");
                int index = find_in_books(book, sizeof(int), compare_book_ISBN, "compare_book_ISBN");

                if (index != -1) {
                    printBook(book[index]);
                    char answer[3];
                    printf("Do you want to delete this book (y/n): ");
                    fgets(answer, sizeof(answer), stdin);
                    answer[strcspn(answer, "\n")] = '\0'; // bỏ \n

                    if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
                        // Di chuyển các phần tử đến phần tử được xóa sang phải
                        deleteBook(book, index, currentIdx.book_index);
                        reduceCurrentIndex(&currentIdx.book_index);
                        printf("Book deleted\n");
                    } else {
                        printf("Deletion cancelled\n");
                    }
                } else {
                    printf("Book not found\n");
                }
            }
            else if (input_option_book == 5) {
                printf("Enter ISBN only, don't use name: \n");
                int index = find_in_books(book, sizeof(int), compare_book_ISBN, "compare_book_ISBN");
                if (index != -1) {
                    printBook(book[index]);
                } else {
                    printf("Book not found\n");
                }
            }
            else if (input_option_book == 6) {
                printf("Only name affect, don't use ISBN\n");
                int index = find_in_books(book, MAX_NAME_LENGTH, compare_book_name, "compare_book_name");

                if(index != -1) {
                    printBook(book[index]);
                }
                else {
                    printf("Book not found\n");
                }
            }
            else if (input_option_book == 7) {
                //WRITE TO FILE
                printf("exit\n");
                break;
            }
            else {
                printf("Invalid option\n");
            }
        } 
        break;
#endif                    
            case BORROW_BOOK:
                printf("Book borrow selected\n");

                int index = find_in_members(member, MAX_NAME_LENGTH, compare_name, "compare_name");
                if (index != -1) {
                    printMember(&member[index]);
                    int book_index = find_in_books(book, MAX_NAME_LENGTH, compare_book_name, "compare_book_name");
                    if (book_index != -1) {
                        printf("Book found\n");
                        if (book[book_index].amount > 0) {
                            //ADD TICKET
                            updateMemberData_AddBorrowTicket(&member[index], book[book_index]);
                            updateBookData_AddBorrowTicket(&book[book_index]);
                            int current_ticket_index = writeToLibTicket(&lib_ticket[currentIdx.ticket_index], &currentIdx, member[index], index, book[book_index], book_index);
                            printf("Ticket ID: %d\n", current_ticket_index);
                        } else {
                            printf("Book is out of stock\n");
                        }
                    } else {
                        printf("Book not found\n");
                    }
                } else {
                    printf("Member not found\n");
                }

                break;
#if 0
            case RETURN_BOOK:
                //print list of ticket to choose
                printf("Existing tickets:\n");
                //number_of_current_ticket_index is the ticket ID
                int ticket_id;
                for (int i = 0; i < number_of_current_ticket_index; i++) {
                    printf("%d\n", lib_ticket_id[i]);
                }

                //choose ticket
                printf("Enter ticket ID to return book: ");
                scanf("%d", &ticket_id);
                getchar();

                //print info of ticket
                int ticket_index = ticket_id;
                if (ticket_index != -1) {
                    printf("Information of ticket %d:\n", ticket_id);
                    printf("Ticket ID: %d\n", lib_ticket_id[ticket_index]);
                    printf("Member ID: %d\n", lib_ticket_member_id[ticket_index]);
                    printf("Borrow date:");
                    printDate_from_countDays(lib_ticket_borrow_date[ticket_index]);
                    printf("Expected return date:");
                    printDate_from_countDays(lib_ticket_return_date_expected[ticket_index]);
                    printf("Lastest return date : ");
                    if(lib_ticket_return_date_real[ticket_index] > 1) {
                        printDate_from_countDays(lib_ticket_return_date_real[ticket_index]);                            
                    } else { 
                        printf("Unknown\n");
                    }

                    printf("Book(s) borrowed:\n");
                    for (int i = 0; i < lib_ticket_borrowed_book[ticket_index]; i++) {
                        printf("%d\n", lib_ticket_ISBN[ticket_index][i]);
                    }

                    //ask for next action
                    char answer[2];
                    printf("Do you want to continue returning book? (y/n): ");
                    scanf(" %c", answer);
                    getchar();
                    if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
                        int penalty_fee = 0;
                        printf("Enter book ISBN to return: ");
                        int book_ISBN_search;
                        scanf("%d", &book_ISBN_search);
                        getchar();

                        int book_index_from_ticket = search_index_to_get_info_fromint(book_ISBN_search,lib_ticket_ISBN[ticket_index]);
                        int book_index_from_member = search_index_to_get_info_fromint(book_ISBN_search,member_borrowed_ISBN[search_index_to_get_info_fromint(lib_ticket_member_id[ticket_index],member_id)]);
                        int book_index_from_book = search_index_to_get_info_fromint(book_ISBN_search,book_ISBN);                        
                        // update current date of ticket
                        printf("Enter current day/month/year: ");
                        int day, month, year;
                        scanf("%d/%d/%d", &day, &month, &year);
                        getchar();
                        lib_ticket_return_date_real[ticket_index] = countDays(day, month, year); // update current date of ticket
                        /*PROCESSING...*/                   
                        if (book_index_from_ticket != -1) {
                            printf("Book found, are you missing it? (y/n): ");
                            scanf(" %c", answer);
                            getchar();
                            if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
                                penalty_fee += book_price[book_index_from_book] * 2;
                                printf("Penalty fee: %d\n", book_price[book_index_from_book] * 2);      
                            } else {
                                int diff_day = countDays(day, month, year)- lib_ticket_return_date_expected[ticket_index];
                                if ( diff_day > 0) {
                                    penalty_fee += book_price[book_index_from_book] * diff_day;
                                    printf("Penalty fee: %d\n", book_price[book_index_from_book] * diff_day);
                                }
                            }

                        book_amount[book_index_from_book]++; // return a book
                        /*BOOK_LIST*/
                        if(member_borrowed_book[book_index_from_member] > 0) {
                            for(int i = book_index_from_member ; i < member_borrowed_book[book_index_from_member]; i++) {
                                // start at book we want to remove, then copy next book to the current
                                member_borrowed_ISBN[book_index_from_member][i] = member_borrowed_ISBN[book_index_from_member][i+1];
                            }
                            member_borrowed_ISBN[book_index_from_member][member_borrowed_book[book_index_from_member]-1] = -1;
                            member_borrowed_book[book_index_from_member]--;                                
                        }
                        
                        /*MEMBER_LIST*/
                        if(lib_ticket_borrowed_book[ticket_index] > 0) {
                            for(int i = book_index_from_ticket ; i < lib_ticket_borrowed_book[ticket_index]; i++) {
                                // start at book we want to remove, then copy next book to the current
                                lib_ticket_ISBN[ticket_index][i] = lib_ticket_ISBN[ticket_index][i+1];
                            }
                            lib_ticket_ISBN[ticket_index][lib_ticket_borrowed_book[ticket_index]-1] = -1;
                            lib_ticket_borrowed_book[ticket_index]--;  
                            // if(lib_ticket_borrowed_book[ticket_index] == 0) {
                            //     free(lib_ticket_ISBN[ticket_index]);
                            //     lib_ticket_ISBN[ticket_index] = -1;
                            // }
                        }
                        } else {
                            printf("Book not found\n");
                        }
                    } else {
                        printf("Returning canceled\n");
                    }
                } else {
                    printf("Ticket not found\n");
                }
                
                printf("Return book : Done\n");
                
                break;
            case STATISTIC_ANALYSIS:
                //enter current date to analyse
                printf("Input current date (day/month/year): ");                
                int day, month, year;
                scanf("%d/%d/%d", &day, &month, &year);
                getchar();            
                // A. Total books in library
                int amount_of_books = 0;                
                for (int i = 0; i < number_of_current_book_index; i++) {
                    if(book_amount[i] > 0){
                        amount_of_books += book_amount[i];
                    } 
                }
                printf("a. Amount of books in library: %d\n", amount_of_books);

                // B. Total books by categories
                
                // Số lượng sách theo thể loại
                int book_count_by_type[MAX_BOOK] = {0};
                char book_type_list[MAX_BOOK][MAX_NAME_LENGTH];
                int type_count = 0;

                // Giả sử số lượng sách là n
                int n = number_of_current_book_index;

                for(int i = 0; i < n; i++) {
                    int j;
                    for(j = 0; j < type_count; j++) {
                        if(strcmp(book_type[i], book_type_list[j]) == 0) {
                            book_count_by_type[j]+=book_amount[i];
                            break;
                        }
                    }
                    if(j == type_count) {
                        strcpy(book_type_list[type_count], book_type[i]);
                        book_count_by_type[type_count]+=book_amount[i];
                        type_count++;
                    }
                }

                printf("B.Amount of books by categories:\n");
                for(int i = 0; i < type_count; i++) {
                    printf("%s: %d\n", book_type_list[i], book_count_by_type[i]);
                }

                //C. Total members
                printf("D. Amount of members: %d\n", number_of_current_member_index);
                

                // D. Total members by gender
                int amount_of_members_by_gender[3];  // male, female, other
                for (int i = 0; i < number_of_current_member_index; i++) {
                    if (strcmp(member_gender[i], "male") == 0) {
                        amount_of_members_by_gender[0]++;
                    } else if (strcmp(member_gender[i], "female") == 0) {
                        amount_of_members_by_gender[1]++;
                    } else if(strcmp(member_gender[i], "other") == 0) {
                        amount_of_members_by_gender[2]++;
                    }
                }
                printf("D. Amount of members by gender:\n");
                printf("- male: %d\n", amount_of_members_by_gender[0]);
                printf("- female: %d\n", amount_of_members_by_gender[1]);
                printf("- other: %d\n", amount_of_members_by_gender[2]);

                //E. Total books borrowed
                int total_books_borrowed = 0;
                for (int i = 0; i < number_of_current_member_index; i++) {
                    if(member_borrowed_book[i] > 0){
                        total_books_borrowed += member_borrowed_book[i];
                    }
                }
                printf("E. Total books borrowed: %d\n", total_books_borrowed);

                //F. List of late members
                printf("F. List of late members:\n");
                int current_date = countDays(day, month, year);
                for (int i = 0; i < number_of_current_ticket_index; i++) {
                    if (lib_ticket_borrowed_book[i] > 0 && current_date > lib_ticket_return_date_expected[i]) {
                        printf("%s\n", member_name[search_index_to_get_info_fromint(lib_ticket_member_id[i], member_id)]);
                    }
                }
                break;
            case EXIT:
                printf("Exit selected\n");
                return 0;
            default:
                printf("Invalid option\n");
                break;
#endif
        }
    }

    return 0;
}