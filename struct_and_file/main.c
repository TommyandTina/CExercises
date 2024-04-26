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

    printf("Data init, choose this option again to load all data again\n");
    load_member_from_file(member);
    load_book_from_file(book);
    load_lib_ticket_from_file(lib_ticket);
    load_current_index_from_file(&currentIdx);
    printf("Data loaded\n");

    while(1) {
        printf("Enter an option number (1 - START - LOAD DATA FROM FILE, 2 - MEMBER_MANAGEMENT, 3 - BOOK_MANAGEMENT, 4 - BORROW_BOOK, 5 - RETURN_BOOK, 6 - STATISTIC_ANALYSIS, 7 - EXIT): ");
        int temp;
        scanf(" %d", &temp);
        getchar();
        enum options input_option = temp;
        switch (input_option) {
            case START:
            printf("Data init, choose this option again to load all data again\n");
            load_member_from_file(member);
            load_book_from_file(book);
            load_lib_ticket_from_file(lib_ticket);
            load_current_index_from_file(&currentIdx);
            printf("Data loaded\n");
            break;
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
                    int index = find_in_members(member,currentIdx.member_index,compare_name,"compare_name");
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
                    int index = find_in_members(member,currentIdx.member_index,compare_name,"compare_name");
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
                    int new_index = find_in_members(member,currentIdx.member_index,compare_Citizen_id,"compare_Citizen_id");
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
                    int index = find_in_members(member,currentIdx.member_index,compare_name,"compare_name");
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
                    save_member_to_file(member);
                    save_current_index_to_file(&currentIdx);
                    printf("Data saved\n");
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
                int index = find_in_books(book, currentIdx.book_index, compare_book_name, "compare_book_name");
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
                int index = find_in_books(book, currentIdx.book_index, compare_book_ISBN, "compare_book_ISBN");

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
                int index = find_in_books(book, currentIdx.book_index, compare_book_ISBN, "compare_book_ISBN");
                if (index != -1) {
                    printBook(book[index]);
                } else {
                    printf("Book not found\n");
                }
            }
            else if (input_option_book == 6) {
                printf("Only name affect, don't use ISBN\n");
                int index = find_in_books(book, currentIdx.book_index, compare_book_name, "compare_book_name");

                if(index != -1) {
                    printBook(book[index]);
                }
                else {
                    printf("Book not found\n");
                }
            }
            else if (input_option_book == 7) {
                //WRITE TO FILE
                save_book_to_file(book);
                save_current_index_to_file(&currentIdx);
                printf("exit\n");
                break;
            }
            else {
                printf("Invalid option\n");
            }
        } 
        break;        
            case BORROW_BOOK:
                printf("Book borrow selected\n");
                printf("MEMBER:\n");
                int index = find_in_members(member, currentIdx.member_index, compare_name, "compare_name");
                if (index != -1) {
                    printMember(&member[index]);
                    printf("BOOK:\n");
                    int book_index = find_in_books(book, currentIdx.book_index, compare_book_name, "compare_book_name");
                    if (book_index != -1) {
                        printf("Book found\n");
                        if (book[book_index].amount > 0) {
                            //ADD TICKET
                            updateMemberData_AddBorrowTicket(&member[index], book[book_index]);
                            updateBookData_AddBorrowTicket(&book[book_index]);
                            int current_ticket_index = writeToLibTicket(&lib_ticket[currentIdx.ticket_index], &currentIdx, member[index], index, book[book_index], book_index);
                            printf("Ticket ID: %d\n", current_ticket_index);
                            save_lib_ticket_to_file(lib_ticket);
                            save_current_index_to_file(&currentIdx);
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

            case RETURN_BOOK:
                //print list of ticket to choose
                printf("Existing tickets:\n");
                //number_of_current_ticket_index is the ticket ID
                for (int i = 0; i < currentIdx.ticket_index; i++) {
                    printf("%d\n", lib_ticket[i].id);
                }
                //ask for ticket ID
                int ticket_index = find_in_lib_ticket(lib_ticket, currentIdx.ticket_index, compare_ticket_index, "compare_ticket_index");
                //print info of ticket
                if (ticket_index != -1) {
                    printLibTicket(lib_ticket[ticket_index]);
                    //ask for next action
                    int ISBN_index_libTicket = find_in_lib_ticket(lib_ticket, 1, find_ticket_book_ISBN, "find_ticket_book_ISBN");
                    if (ISBN_index_libTicket != -1) {
                        returnLibTicket(lib_ticket, ticket_index, ISBN_index_libTicket, &currentIdx, member, book);
                        save_lib_ticket_to_file(lib_ticket);
                        save_current_index_to_file(&currentIdx);
                    }

                } else {
                    printf("Ticket not found\n");
                }
                
                printf("Return book : Done\n");
                
                break;
#if 1
            case STATISTIC_ANALYSIS:
                //enter current date to analyse
                printf("Input current date (day/month/year): ");                
                int day, month, year;
                scanf("%d/%d/%d", &day, &month, &year);
                getchar();            
                // A. Total books in library
                int amount_of_books = 0;                
                for (int i = 0; i < currentIdx.book_index; i++) {
                    if(book[i].amount > 0){
                        amount_of_books += book[i].amount;
                    } 
                }
                printf("a. Amount of books in library: %d\n", amount_of_books);

                // B. Total books by categories
                
                // Số lượng sách theo thể loại
                int book_count_by_type[MAX_BOOK] = {0};
                char book_type_list[MAX_BOOK][MAX_NAME_LENGTH];
                int type_count = 0;

                // Giả sử số lượng sách là n
                int n = currentIdx.book_index;

                for(int i = 0; i < n; i++) {
                    int j;
                    for( j = 0; j < type_count; j++) {
                        if(strcmp(book[i].type, book_type_list[j]) == 0) {
                            book_count_by_type[j]+=book[i].amount;
                            break;
                        }
                    }
                    if(j == type_count) {
                        strcpy(book_type_list[type_count], book[i].type);
                        book_count_by_type[type_count]+=book[i].amount;
                        type_count++;
                    }
                }

                printf("B.Amount of books by categories:\n");
                for(int i = 0; i < type_count; i++) {
                    printf("type %s: %d\n", book_type_list[i], book_count_by_type[i]);
                }

                //C. Total members
                printf("D. Amount of members: %d\n", currentIdx.member_index);
                

                // D. Total members by gender
                int amount_of_members_by_gender[3];  // male, female, other
                for (int i = 0; i < currentIdx.member_index; i++) {
                    if (strcmp(member[i].gender, "male") == 0) {
                        amount_of_members_by_gender[0]++;
                    } else if (strcmp(member[i].gender, "female") == 0) {
                        amount_of_members_by_gender[1]++;
                    } else if(strcmp(member[i].gender, "other") == 0) {
                        amount_of_members_by_gender[2]++;
                    }
                }
                printf("D. Amount of members by gender:\n");
                printf("- male: %d\n", amount_of_members_by_gender[0]);
                printf("- female: %d\n", amount_of_members_by_gender[1]);
                printf("- other: %d\n", amount_of_members_by_gender[2]);

                //E. Total books borrowed
                int total_books_borrowed = 0;
                for (int i = 0; i < currentIdx.member_index; i++) {
                    if(member[i].borrowed_book > 0){
                        total_books_borrowed += member[i].borrowed_book;
                    }
                }
                printf("E. Total books borrowed: %d\n", total_books_borrowed);

                //F. List of late members
                printf("F. List of late members:\n");
                int current_date = countDays(day, month, year);
                for (int i = 0; i < currentIdx.ticket_index; i++) {
                    if (lib_ticket[i].borrowed_book_amount > 0 && current_date > lib_ticket[i].return_date_expected) {
                        printf("%s\n", member[lib_ticket[i].member.index].name);
                    }
                }
                break;
            case EXIT:
                printf("Exit selected\n");
                save_lib_ticket_to_file(lib_ticket);
                save_member_to_file(member);
                save_book_to_file(book);
                save_current_index_to_file(&currentIdx);
                printf("Data saved\n");
                return 0;
            case 99999:
                //DELETE FILE, TESTING ONLY, DO NOT USE
                printf("DELETE FILE\n");
                char file_name[4][MAX_NAME_LENGTH] = {"member_data.bin", "book_data.bin", "lib_ticket_data.bin", "currentIdx_data.bin"};
                for (int i = 0; i < 4; i++) {
                    int result = remove(file_name[i]);
                    if (result == 0) {
                        printf("%s deleted\n", file_name[i]);
                    } else {
                        printf("Cannot delete %s\n", file_name[i]);
                    }
                }
                break;
            default:
                printf("Invalid option\n");
                break;
#endif
        }
    }

    return 0;
}