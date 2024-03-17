
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

//chưa test function
int search_index_to_get_info_fromstr(char *find_this, char *array[]){
    for (int i = 0; array[i] != NULL; i++) {
        if (strcmp(array[i], find_this) == 0) {
            return i;
        }
    }
    return -1;
}

//function này sai
int search_index_to_get_info_fromint(int find_this, int array[]){
    int index = -1;
    for (int i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
        if (array[i] == find_this) {
            index = i;
            break;
        }
    }
    return index;
}

int main(){
    int number_of_current_member_index = 0;
    int number_of_current_book_index = 0;
    int number_of_current_ticket_index = 0;



    int member_id[MAX_MEMBERS];
    char member_name[MAX_MEMBERS][MAX_NAME_LENGTH];
    char member_citizen_ID[MAX_MEMBERS][MAX_NAME_LENGTH];
    int member_dayOfBirth[MAX_MEMBERS];
    char member_email[MAX_MEMBERS][MAX_NAME_LENGTH];
    char member_gender[MAX_MEMBERS][MAX_NAME_LENGTH];
    int member_register_date[MAX_MEMBERS];
    int member_expired_date[MAX_MEMBERS];

    char book_ISBN[MAX_BOOK];
    char book_name[MAX_BOOK];
    char book_author[MAX_BOOK];
    char book_publishing_company[MAX_BOOK];
    int book_publishing_year[MAX_BOOK];
    char book_type[MAX_BOOK];
    int book_price[MAX_BOOK];
    int book_amount[MAX_BOOK];

    int lib_ticket_member_id[MAX_TICKET];
    int lib_ticket_borrow_date[MAX_TICKET];
    int lib_ticket_return_date_expected[MAX_TICKET];
    int lib_ticket_return_date_real[MAX_TICKET];
    char lib_ticket_ISBN[MAX_TICKET];

int lib_ticket_fine(int lib_ticket_return_date_real, int lib_ticket_return_date_expected){
    int days = lib_ticket_return_date_real - lib_ticket_return_date_expected;
    if(days < 0){
        days = 0;
    }
    return 5000 * days;
}



enum options {
    START = 1,
    MEMBER_MANAGEMENT =2,
    BOOK_MANAGEMENT = 3,
    BORROW_BOOK = 4,
    RETURN_BOOK = 5,
    STATISTIC_ANALYSIS = 6,
    EXIT = 7
} ;

    enum options input_option = START;
    while(1) {
        switch (input_option) {
            case START:
            {
                printf("Enter an option number (1 - START, 2 - MEMBER_MANAGEMENT, 3 - BOOK_MANAGEMENT, 4 - BORROW_BOOK, 5 - RETURN_BOOK, 6 - STATISTIC_ANALYSIS, 7 - EXIT): ");
                scanf(" %d", &input_option);                
            }
            case MEMBER_MANAGEMENT:
            {
                char member_name_to_search[MAX_NAME_LENGTH];  // Khai báo biến
                int option;
                printf("Do you want to add, search or change a member (1-add, 2-search, 3-change, 4-watch members list,5-search by citizen_id,6-search book borrowed by name) ?");
                scanf(" %d", &option);

                if(option == 1)
                {
                    printf("Enter member ID: ");
                    scanf("%d", &member_id[number_of_current_member_index]);
                    getchar(); // Đọc ký tự xuống dòng sau khi nhập số

                    printf("Enter member name: ");
                    fgets(member_name[number_of_current_member_index], MAX_NAME_LENGTH, stdin);

                    printf("Enter member citizen ID: ");
                    fgets(member_citizen_ID[number_of_current_member_index], MAX_NAME_LENGTH, stdin);

                    printf("Enter member day of birth: ");
                    scanf("%d", &member_dayOfBirth[number_of_current_member_index]);
                    getchar(); // Đọc ký tự xuống dòng sau khi nhập số

                    printf("Enter member email: ");
                    fgets(member_email[number_of_current_member_index], MAX_NAME_LENGTH, stdin);

                    printf("Enter member gender: ");
                    fgets(member_gender[number_of_current_member_index], MAX_NAME_LENGTH, stdin);

                    printf("Enter member register date: ");
                    scanf("%d", &member_register_date[number_of_current_member_index]);
                    getchar(); // Đọc ký tự xuống dòng sau khi nhập số

                    // Tính ngày hết hạn (48 tháng sau ngày lập thẻ)
                    member_expired_date[number_of_current_member_index] = member_register_date[number_of_current_member_index] + 48;                        
                    number_of_current_member_index++;
                }
                else if(option == 2) //bug ???
                {
                    // getchar(); // Đọc ký tự xuống dòng sau khi nhập số
                    printf("Enter member name to search: ");
                    // memset(member_name_to_search, 0, sizeof(member_name_to_search));  // Xoá dữ liệu biến
                    fgets(member_name_to_search, sizeof(member_name_to_search), stdin);  // Đọc dữ liệu vào biến
                    member_name_to_search[strcspn(member_name_to_search, "\n")] = 0; // Xóa kí tự newline từ fgets

                    int index = search_index_to_get_info_fromstr(member_name_to_search, member_name);
                    if(index != -1)
                    {
                        printf("Member info:\nName: %s\nCitizen ID: %s\n", member_name[index], member_citizen_ID[index]);
                    }
                    else
                    {
                        printf("Member not found\n");
                    }

                }
                else if(option == 3)
                {
                    printf("Enter member name to change: ");
                    fflush(stdout);
                    member_name_to_search[0] = '\0';  // Chạy đến ký tự \0 đầu tiên của chuỗi
                    fgets(member_name_to_search, 100, stdin);  // Nhập tên thành viên
                    member_name_to_search[strcspn(member_name_to_search, "\n")] = '\0';  // Loại bỏ ký tự \n

                    int index = search_index_to_get_info_fromstr(member_name, member_name_to_search);
                    if(index != -1)
                    {
                        printf("Which info do you want to change? (1-member_id, 2-member_name, 3-member_citizen_ID, 4-member_dayOfBirth, 5-member_email, 6-member_gender, 7-member_register_date, 8-member_expired_date)");
                        int change_option;
                        scanf(" %d", &change_option);
                        switch(change_option) {
                            case 1:
                                printf("Enter new member_id: ");
                                fflush(stdout);
                                scanf("%d", &member_id[index]);
                                break;
                            case 2:
                                printf("Enter new member_name: ");
                                scanf(" %99[^\n]", member_name[index]);
                                break;
                            case 3:
                                printf("Enter new member_citizen_ID: ");
                                scanf(" %99[^\n]", member_citizen_ID[index]);
                                break;
                            case 4:
                                int day, month, year;
                                printf("Enter new day of birth (dd/mm/yyyy): ");
                                scanf("%d/%d/%d", &day, &month, &year);
                                member_dayOfBirth[index] = countDays(day, month, year);
                            case 5:
                                printf("Enter new email: ");
                                scanf(" %99[^\n]", member_email[index]);
                                break;
                            case 6:
                                printf("Enter new gender (M/F): ");
                                scanf(" %c", &member_gender[index]);
                                break;
                            case 7:
                                printf("Enter new register date (dd/mm/yyyy): ");
                                scanf("%d/%d/%d", &day, &month, &year);
                                member_register_date[index] = countDays(day, month, year);
                            case 8:
                                printf("Enter new expired date (dd/mm/yyyy): ");
                                scanf("%d/%d/%d", &day, &month, &year);
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
                    int index = search_index_to_get_info_fromint(citizen_id, member_citizen_ID);
                    if (index != -1)
                    {
                        printf("Member id: %s\n", member_id[index]);
                        printf("Member name: %s\n", member_name[index]);
                        printf("Member citizen_id: %d\n", member_citizen_ID[index]);
                        printf("Member dayOfBirth: %d\n", member_dayOfBirth[index]);
                        printf("Member email: %s\n", member_email[index]);
                        printf("Member gender: %c\n", member_gender[index]);
                        printf("Member register_date: %d\n", member_register_date[index]);
                        printf("Member expired_date: %d\n", member_expired_date[index]);
                    }

                }
                else if (option == 6)
                {
                    printf("Enter member name to search: ");
                    char name_to_search[100];
                    scanf(" %99[^\n]", name_to_search);
                    int index = search_index_to_get_info_fromstr(member_name, name_to_search);
                    if (index != -1)
                    {
//xuất sách làm sau
                    }
                    else
                    {
                        printf("Member not found\n");
                    }
            }
        }                
                input_option = START;
                break;
            case BOOK_MANAGEMENT:
                printf("Book management selected\n");
                input_option = START;
                break;
            case BORROW_BOOK:
                printf("Borrow book selected\n");
                input_option = START;
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