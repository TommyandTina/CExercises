
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 100
#define MAX_BOOK 100
#define MAX_TICKET 100
#define MAX_NAME_LENGTH 100  // Độ dài tên tối đa

//Hàm countDays để tính số ngày 
int countDays(int day, int month, int year) {
    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Tính số ngày trong các năm trước năm cho trước
    int totalDays = year * 365;

    // Thêm số ngày của các tháng trước tháng cho trước
    for (int i = 0; i < month - 1; i++) {
        totalDays += monthDays[i];
    }

    // Thêm số ngày từ đầu tháng đến ngày cho trước
    totalDays += day;

    // Thêm số ngày nhuận
    totalDays += year / 4 - year / 100 + year / 400;

    // Trừ đi số ngày nhuận nếu năm cho trước là năm nhuận và tháng nhỏ hơn 3
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && month < 3) {
        totalDays--;
    }

    return totalDays;
}

int search_index_to_get_info_fromstr(char find_this[MAX_NAME_LENGTH], char array[][MAX_NAME_LENGTH], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i], find_this) == 0) {
            return i;
        }
    }
    return -1;
}


int search_index_to_get_info_fromint(int find_this, int array[MAX_MEMBERS]){
    int index = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (array[i] == find_this) {
            index = i;
            return index;
        }
    }
    return index;
}

int main(){
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
    int* member_borrowed_ISBN[MAX_MEMBERS];
    int member_borrowed_book[MAX_MEMBERS];

    int book_ISBN[MAX_BOOK];
    char book_name[MAX_BOOK][MAX_NAME_LENGTH];
    char book_author[MAX_BOOK][MAX_NAME_LENGTH];
    char book_publishing_company[MAX_BOOK][MAX_NAME_LENGTH];
    int book_publishing_year[MAX_BOOK];
    char book_type[MAX_BOOK][MAX_NAME_LENGTH];
    int book_price[MAX_BOOK];
    int book_amount[MAX_BOOK];

enum options {
    START = 1,
    MEMBER_MANAGEMENT =2,
    BOOK_MANAGEMENT = 3,
    BORROW_BOOK = 4,
    RETURN_BOOK = 5,
    STATISTIC_ANALYSIS = 6,
    EXIT = 7
} ;

    enum options input_option;
    while(1) {
        printf("Enter an option number (1 - START, 2 - MEMBER_MANAGEMENT, 3 - BOOK_MANAGEMENT, 4 - BORROW_BOOK, 5 - RETURN_BOOK, 6 - STATISTIC_ANALYSIS, 7 - EXIT): ");
        scanf(" %d", &input_option);
        getchar();
        switch (input_option) {
            case MEMBER_MANAGEMENT:
            {
                char member_name_to_search[MAX_NAME_LENGTH];  // Khai báo biến
                int option;
                printf("Do you want to add, search or change a member (1-add, 2-search, 3-change, 4-watch members list,5-search by citizen_id,6-search book borrowed by name, 7-delete) ?");
                scanf(" %d", &option);
                getchar();

                if(option == 1)
                {
                    printf("Enter member ID: ");
                    scanf("%d", &member_id[number_of_current_member_index]);
                    getchar(); // Đọc ký tự xuống dòng sau khi nhập số
                    
                    printf("Enter member name: ");
                    fgets(member_name[number_of_current_member_index], MAX_NAME_LENGTH, stdin);
                    member_name[number_of_current_member_index][strlen(member_name[number_of_current_member_index])-1] = '\0'; // bỏ \n


                    printf("Enter member citizen ID: ");
                    scanf("%d", &member_citizen_ID[number_of_current_member_index]);
                    getchar(); // Đọc ký tự xuống dàn sau khi nhap so

                    printf("Enter day of birth (dd/mm/yyyy): ");
                    scanf("%d/%d/%d", &day, &month, &year);
                    getchar();
                    member_dayOfBirth[number_of_current_member_index] = countDays(day, month, year);                    
                    

                    printf("Enter member email: ");
                    fgets(member_email[number_of_current_member_index], MAX_NAME_LENGTH, stdin);
                    member_email[number_of_current_member_index][strcspn(member_email[number_of_current_member_index], "\n")] = '\0'; // bỏ \n
                    

                    printf("Enter member gender: ");
                    fgets(member_gender[number_of_current_member_index], MAX_NAME_LENGTH, stdin);
                    member_gender[number_of_current_member_index][strcspn(member_gender[number_of_current_member_index], "\n")] = '\0'; // bỏ \n

                    printf("Enter register date (dd/mm/yyyy): ");
                    scanf("%d/%d/%d", &day, &month, &year);
                    getchar();
                    member_register_date[number_of_current_member_index] = countDays(day, month, year);
                    

                    // Tính ngày hết hạn (48 tháng sau ngày lập thẻ)
                    member_expired_date[number_of_current_member_index] = member_register_date[number_of_current_member_index] + 48;                        
                    number_of_current_member_index++;
                }
                else if(option == 2) 
                {
                    // getchar(); // Đọc ký tự xuống dòng sau khi nhập số
                    printf("Enter member name to search: ");
                    // memset(member_name_to_search, 0, sizeof(member_name_to_search));  // Xoá dữ liệu biến
                    
                    fgets(member_name_to_search, MAX_NAME_LENGTH, stdin);  // Đọc dữ liệu vào biến
                    member_name_to_search[strlen(member_name_to_search)-1] = '\0'; // Xóa kí tự newline từ fgets

                    int index = search_index_to_get_info_fromstr(member_name_to_search, member_name,MAX_NAME_LENGTH);
                    if(index != -1)
                    {
                        printf("Member info:\nName: %s\nCitizen ID: %d\n", member_name[index], member_citizen_ID[index]);
                    }
                    else
                    {
                        printf("Member not found\n");
                    }

                }
                else if(option == 3)
                {
                    printf("Enter member name to change: ");
                    // fflush(stdout);
                    // member_name_to_search[0] = '\0';  // Chạy đến ký tự \0 đầu tiên của chuỗi
                    fgets(member_name_to_search, MAX_NAME_LENGTH, stdin);  // Nhập tên thành viên
                    member_name_to_search[strlen(member_name_to_search)-1] = '\0';  // Loại bỏ ký tự \n
                
                    int index = search_index_to_get_info_fromstr(member_name_to_search, member_name,MAX_NAME_LENGTH);
                    if(index != -1)
                    {
                        printf("Which info do you want to change? (1-member_id, 2-member_name, 3-member_citizen_ID, 4-member_dayOfBirth, 5-member_email, 6-member_gender, 7-member_register_date, 8-member_expired_date)");
                        int change_option;
                        scanf(" %d", &change_option);
                        getchar();
                        switch(change_option) {
                            case 1:
                                printf("Enter new member_id: ");
                                // fflush(stdout);
                                scanf("%d", &member_id[index]);
                                getchar();
                                break;
                            case 2:
                                printf("Enter new member_name: ");
                                fgets(member_name[index], MAX_NAME_LENGTH, stdin);  // Nhập tên thành viên
                                member_name[index][strlen(member_name[index])-1] = '\0';  // Loại bỏ ký tự \n                                
                                break;
                            case 3:
                                printf("Enter new member_citizen_ID: ");
                                scanf("%d", &member_citizen_ID[index]);
                                getchar();
                                break;
                            case 4:
                                printf("Enter new day of birth (dd/mm/yyyy): ");
                                scanf("%d/%d/%d", &day, &month, &year);
                                getchar();
                                member_dayOfBirth[index] = countDays(day, month, year);
                            case 5:
                                printf("Enter new email: ");
                                fgets(member_email[index], MAX_NAME_LENGTH, stdin);  // Nhập tên thành viên
                                member_email[index][strlen(member_email[index])-1] = '\0';  // Loại bỏ ký tự \n 
                                break;
                            case 6:
                                printf("Enter new gender: ");
                                fgets(member_gender[index], MAX_NAME_LENGTH, stdin);  // Nhập tên thành viên
                                member_gender[index][strlen(member_gender[index])-1] = '\0';  // Loại bỏ ký tự \n 
                                break;
                            case 7:
                                printf("Enter new register date (dd/mm/yyyy): ");
                                scanf("%d/%d/%d", &day, &month, &year);
                                getchar();
                                member_register_date[index] = countDays(day, month, year);
                            case 8:
                                printf("Enter new expired date (dd/mm/yyyy): ");
                                scanf("%d/%d/%d", &day, &month, &year);
                                getchar();
                                member_expired_date[index] = countDays(day, month, year);
                                break;
                            default:
                                printf("Invalid option\n");
                        }
                    }
                    else
                    {
                        printf("Member not found\n");
                    }
                }
                else if (option == 4)
                {
                    printf("Option 4: Current members:\n");
                    for(int i = 0; i < number_of_current_member_index; i++)
                    {
                        if(strlen(member_name[i]) > 0)
                        {
                            printf("%s\n", member_name[i]);
                        }
                    }
                }
                else if (option == 5)
                {
                    printf("Enter citizen_id to search: ");
                    int citizen_id;
                    scanf("%d", &citizen_id);
                    getchar();
                    printf("ID: %d\n", citizen_id);
                    int new_index = search_index_to_get_info_fromint(citizen_id, member_citizen_ID);
                    printf("Index: %d\n", new_index);
                    if (new_index != -1)
                    {
                        printf("Member id: %d\n", member_id[new_index]);
                        printf("Member name: %s\n", member_name[new_index]);
                        printf("Member citizen_id: %d\n", member_citizen_ID[new_index]);
                        printf("Member dayOfBirth: %d\n", member_dayOfBirth[new_index]);
                        printf("Member email: %s\n", member_email[new_index]);
                        printf("Member gender: %c\n", member_gender[new_index]);
                        printf("Member register_date: %d\n", member_register_date[new_index]);
                        printf("Member borrowed_ISBN:\n");
                        for (int j = 0; j < member_borrowed_book[new_index]; j++) {
                            printf("%d\n", member_borrowed_ISBN[new_index][j]);
                        }
                    }
                }
                else if (option == 6)
                {
                    printf("Enter member name to search: ");
                    char name_to_search[MAX_NAME_LENGTH];
                    fgets(name_to_search, MAX_NAME_LENGTH, stdin);
                    name_to_search[strcspn(name_to_search, "\n")] = '\0'; // bỏ \n
                    int index = search_index_to_get_info_fromstr(name_to_search, member_name,MAX_NAME_LENGTH);
                    if (index != -1)
                    {
                        printf("Member info:\nName: %s\nCitizen ID: %d\nDay of Birth: %d\nEmail: %s\nGender: %s\nRegister Date: %d\n", member_name[index], member_citizen_ID[index], member_dayOfBirth[index], member_email[index], member_gender[index], member_register_date[index]);
                        printf("Books borrowed:\n");
                        for (int j = 0; j < member_borrowed_book[index]; j++) {
                            printf("%d\n", member_borrowed_ISBN[index][j]);
                        }
                        printf("Do you want to delete this member (y/n): ");
                        char delete_member;
                        scanf(" %c", &delete_member);
                        getchar();
                        if (delete_member == 'y' || delete_member == 'Y') {
                            // Move elements to the right of the deleted element
                            free(member_borrowed_ISBN[index]);
                            for (int i = index; i < number_of_current_member_index - 1; i++) {
                                strcpy(member_name[i], member_name[i + 1]);
                                member_citizen_ID[i] = member_citizen_ID[i + 1];
                                member_dayOfBirth[i] = member_dayOfBirth[i + 1];
                                strcpy(member_email[i], member_email[i + 1]);
                                strcpy(member_gender[i], member_gender[i + 1]);
                                member_register_date[i] = member_register_date[i + 1];
                                member_borrowed_book[i] = member_borrowed_book[i + 1];
                                memmove(&member_borrowed_ISBN[i], &member_borrowed_ISBN[i + 1], sizeof(member_borrowed_ISBN[i]) * member_borrowed_book[i]);
                            }
                            number_of_current_member_index--;
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
        }                
                break;
            case BOOK_MANAGEMENT:
        while(1) {
            printf("Enter an option number for book management (1 - get_book_list, 2 - add_book, 3 - change_info, 4 - delete_book, 5 - search_book_from_ISBN, 6 - search_book_from_name, 7 - exit): ");
            int input_option_book;
            scanf(" %d", &input_option_book);
            getchar();
            
            if(input_option_book == 1) {
                for (int i = 0; i < number_of_current_book_index; i++) {
                    printf("%s ", book_name[i]);
                }
                printf("\n");
                
            } else if (input_option_book == 5) {
                printf("Enter book_ISBN to search: ");
                int isbn;
                scanf(" %d", &isbn);
                getchar();

                int index = -1;
                for (int i = 0; i < number_of_current_book_index; i++) {
                    if (book_ISBN[i] == isbn) {
                        index = i;
                        break;
                    }
                }

                if (index != -1) {
                    printf("Book ISBN: %d\n", book_ISBN[index]);
                    printf("Book name: %s\n", book_name[index]);
                    printf("Book author: %s\n", book_author[index]);
                    printf("Book publishing company: %s\n", book_publishing_company[index]);
                    printf("Book publishing year: %d\n", book_publishing_year[index]);
                    printf("Book type: %s\n", book_type[index]);
                    printf("Book price: %d\n", book_price[index]);
                    printf("Book quantity: %d\n", book_amount[index]);
                } else {
                    printf("Book not found\n");
                }
            }
            else if (input_option_book == 2) {
                int index = number_of_current_book_index;
                printf("Enter book_ISBN: ");
                scanf(" %d", &book_ISBN[number_of_current_book_index]);
                getchar();

                printf("Enter book_name: ");
                fgets(book_name[number_of_current_book_index], MAX_NAME_LENGTH, stdin);
                book_name[number_of_current_book_index][strlen(book_name[number_of_current_book_index])-1] = '\0'; // bỏ \n

                printf("Enter book_author: ");
                fgets(book_author[number_of_current_book_index], MAX_NAME_LENGTH, stdin);
                book_author[number_of_current_book_index][strlen(book_author[number_of_current_book_index])-1] = '\0'; // bỏ \n

                printf("Enter book_publishing_company: ");
                fgets(book_publishing_company[number_of_current_book_index], MAX_NAME_LENGTH, stdin);
                book_publishing_company[number_of_current_book_index][strlen(book_publishing_company[number_of_current_book_index])-1] = '\0'; // bỏ \n

                printf("Enter book_publishing_year: ");
                scanf(" %d", &book_publishing_year[number_of_current_book_index]);
                getchar();

                printf("Enter book_type: ");
                fgets(book_type[number_of_current_book_index], MAX_NAME_LENGTH, stdin);
                book_type[number_of_current_book_index][strcspn(book_type[number_of_current_book_index], "\n")] = '\0'; // bỏ \n

                printf("Enter book_price: ");
                scanf(" %d", &book_price[number_of_current_book_index]);
                getchar();

                printf("Enter book_amount: ");
                scanf(" %d", &book_amount[number_of_current_book_index]);
                getchar();

                number_of_current_book_index++;
            }
            else if (input_option_book == 3) {
                char name_to_change[MAX_NAME_LENGTH];
                printf("Enter book name to change info: ");
                fgets(name_to_change, MAX_NAME_LENGTH, stdin);
                name_to_change[strcspn(name_to_change, "\n")] = '\0'; // bỏ \n

                int index = -1;
                for(int i = 0; i < number_of_current_book_index; i++){
                    if(strcmp(name_to_change, book_name[i]) == 0){
                        index = i;
                        break;
                    }
                }

                if(index == -1){
                    printf("Book not found\n");
                }
                else{
                    printf("Enter info to change (book_ISBN, book_author, book_publishing_company, book_publishing_year, book_type, book_price, book_amount, book_name): ");
                    char info_to_change[MAX_NAME_LENGTH];
                    fgets(info_to_change, MAX_NAME_LENGTH, stdin);
                    info_to_change[strcspn(info_to_change, "\n")] = '\0'; // bỏ \n

                    if(strcmp(info_to_change, "book_ISBN") == 0){
                        printf("Enter new book_ISBN: ");
                        scanf(" %d", &book_ISBN[index]);
                        getchar();
                    }
                    else if(strcmp(info_to_change, "book_author") == 0){
                        printf("Enter new book_author: ");
                        fgets(book_author[index], MAX_NAME_LENGTH, stdin);
                        book_author[index][strlen(book_author[index])-1] = '\0'; // bỏ \n
                    }
                    else if(strcmp(info_to_change, "book_publishing_company") == 0){
                        printf("Enter new book_publishing_company: ");
                        fgets(book_publishing_company[index], MAX_NAME_LENGTH, stdin);
                        book_publishing_company[index][strlen(book_publishing_company[index])-1] = '\0'; // bỏ \n
                    }
                    else if(strcmp(info_to_change, "book_publishing_year") == 0){
                        printf("Enter new book_publishing_year: ");
                        scanf(" %d", &book_publishing_year[index]);
                        getchar();
                    }
                    else if(strcmp(info_to_change, "book_type") == 0){
                        printf("Enter new book_type: ");
                        fgets(book_type[index], MAX_NAME_LENGTH, stdin);
                        book_type[index][strcspn(book_type[index], "\n")] = '\0'; // bỏ \n
                    }
                    else if(strcmp(info_to_change, "book_price") == 0){
                        printf("Enter new book_price: ");
                        scanf(" %d", &book_price[index]);
                        getchar();
                    }
                    else if(strcmp(info_to_change, "book_amount") == 0){
                        printf("Enter new book_amount: ");
                        scanf(" %d", &book_amount[index]);
                        getchar();
                    }
                    else if (strcmp(info_to_change, "book_name") == 0) { // Đổi tên sách
                    printf("Enter new book_name: ");
                    fgets(book_name[index], MAX_NAME_LENGTH, stdin);
                    book_name[index][strlen(book_name[index]) - 1] = '\0'; // bỏ \n
                    }
                    else{
                        printf("Invalid info to change\n");
                    }
                }

            }
            else if (input_option_book == 4) {
                printf("Enter book_ISBN to delete: ");
                int isbn;
                scanf(" %d", &isbn);
                getchar();

                int index = -1;
                for (int i = 0; i < number_of_current_book_index; i++) {
                    if (book_ISBN[i] == isbn) {
                        index = i;
                        break;
                    }
                }

                if (index != -1) {
                    printf("Book ISBN: %d\n", book_ISBN[index]);
                    printf("Book name: %s\n", book_name[index]);
                    printf("Book author: %s\n", book_author[index]);
                    printf("Book publishing company: %s\n", book_publishing_company[index]);
                    printf("Book publishing year: %d\n", book_publishing_year[index]);
                    printf("Book type: %s\n", book_type[index]);
                    printf("Book price: %d\n", book_price[index]);
                    printf("Book quantity: %d\n", book_amount[index]);

                    char answer[3];
                    printf("Do you want to delete this book (y/n): ");
                    fgets(answer, sizeof(answer), stdin);
                    answer[strcspn(answer, "\n")] = '\0'; // bỏ \n

                    if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
                        // Di chuyển các phần tử đến phần tử được xóa sang phải
                        for (int i = index; i < number_of_current_book_index - 1; i++) {
                            book_ISBN[i] = book_ISBN[i + 1];
                            strcpy(book_name[i], book_name[i + 1]);
                            strcpy(book_author[i], book_author[i + 1]);
                            strcpy(book_publishing_company[i], book_publishing_company[i + 1]);
                            book_publishing_year[i] = book_publishing_year[i + 1];
                            strcpy(book_type[i], book_type[i + 1]);
                            book_price[i] = book_price[i + 1];
                            book_amount[i] = book_amount[i + 1];
                        }
                        number_of_current_book_index--;
                        printf("Book deleted\n");
                    } else {
                        printf("Deletion cancelled\n");
                    }
                } else {
                    printf("Book not found\n");
                }
            }
            else if (input_option_book == 6) {
                char book_name_to_search[MAX_NAME_LENGTH];
                printf("Enter book name to search: ");
                fgets(book_name_to_search, sizeof(book_name_to_search), stdin);
                book_name_to_search[strcspn(book_name_to_search, "\n")] = '\0'; // bỏ \n

                int index = search_index_to_get_info_fromstr(book_name_to_search, book_name, number_of_current_book_index);

                if(index != -1) {
                    printf("Book info:\n");
                    printf("Book ISBN: %d\n", book_ISBN[index]);
                    printf("Book name: %s\n", book_name[index]);
                    printf("Book author: %s\n", book_author[index]);
                    printf("Book publishing company: %s\n", book_publishing_company[index]);
                    printf("Book publishing year: %d\n", book_publishing_year[index]);
                    printf("Book type: %s\n", book_type[index]);
                    printf("Book price: %d\n", book_price[index]);
                    printf("Book quantity: %d\n", book_amount[index]);
                }
                else {
                    printf("Book not found\n");
                }
            }
            else if (input_option_book == 7) {
                printf("exit\n");
                break;
            }
            else {
                printf("Invalid option\n");
            }
        }
                break;
            case BORROW_BOOK:
                printf("Borrow book selected\n");
                break;
            case RETURN_BOOK:
                printf("Return book selected\n");
                break;
            case STATISTIC_ANALYSIS:
                printf("Statistic analysis selected\n");
                break;
            case EXIT:
                printf("Exit selected\n");
                return 0;
            default:
                printf("Invalid option\n");
                break;
        }
    }

    return 0;
}