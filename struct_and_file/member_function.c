#include "member_function.h"


void printMember(struct Member *member) {
    printf("id: %d\n", member->id);
    printf("name: %s\n", member->name);
    printf("citizen_ID: %d\n", member->citizen_ID);
    printf("dayOfBirth: ");
    printDate_from_countDays(member->dayOfBirth);
    printf("email: %s\n", member->email);
    printf("gender: %s\n", member->gender);
    printf("register_date: ");
    printDate_from_countDays(member->register_date);
    printf("expired_date: ");
    printDate_from_countDays(member->expired_date);
    printf("borrowed_book: %d\n", member->borrowed_book);
    if(member->borrowed_book>0){
        printf("borrowed_ISBN: ");
        for (int i = 0; i < MAX_BOOK; i++) {
            if(member->borrowed_ISBN[i] > 0){
                printf("%d ", member->borrowed_ISBN[i]);
            }
        }
    }
    printf("\n");
}

int writeToMember(struct Member *member,struct CurrentIndex *currentIdx){
    int day, month, year;
    printf("Enter member ID: ");
    scanf("%d", &member->id);
    getchar(); // Đọc ký tự xuống dòng sau khi nhập số
    
    printf("Enter member name: ");
    fgets(member->name, MAX_NAME_LENGTH, stdin);
    member->name[strlen(member->name)-1] = '\0'; // bỏ \n

    printf("Enter member citizen ID: ");
    scanf("%d", &member->citizen_ID);
    getchar(); // Đọc ký tự xuống dàn sau khi nhap so

    printf("Enter day of birth (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &day, &month, &year);
    getchar();
    member->dayOfBirth = countDays(day, month, year);                    
    

    printf("Enter member email: ");
    fgets(member->email, MAX_NAME_LENGTH, stdin);
    member->email[strcspn(member->email, "\n")] = '\0'; // bỏ \n
    

    printf("Enter member gender (male/female/other): ");
    fgets(member->gender, MAX_NAME_LENGTH, stdin);
    member->gender[strcspn(member->gender, "\n")] = '\0'; // bỏ \n

    printf("Enter register date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &day, &month, &year);
    getchar();
    member->register_date = countDays(day, month, year);
    

    // Tính ngày hết hạn (48 tháng sau ngày lập thẻ)
    member->expired_date = member->register_date + 48;                        
    
    // currentIdx->member_index++;
    // printf("current member index is %d\n",currentIdx->member_index);
    //     currentIdx->member_index++;
    // printf("current member index is %d\n",currentIdx->member_index);
    //     currentIdx->member_index++;
    // printf("current member index is %d\n",currentIdx->member_index);
    return currentIdx->member_index++;
    // printMember(member);
}

// Hàm so sánh ID
bool compare_Citizen_id(struct Member a, struct Member b) {
    return a.citizen_ID == b.citizen_ID;
}

// Hàm so sánh tên
bool compare_name(struct Member a, struct Member b) {
    return strcmp(a.name, b.name) == 0;
}

//Hàm tìm kiếm trong member
int find_in_members(struct Member member[], int size, bool (*compare)(struct Member, struct Member)) {
    struct Member find_this;
    printf("Enter name to search:(skip if don't use) ");
    fgets(&find_this.name, MAX_NAME_LENGTH, stdin);
    find_this.name[strlen(find_this.name)-1] = '\0';  // Loại bỏ ký tự xuống dòng
    
    printf("Enter Citizen ID to search: (skip if don't use)");
    scanf(" %d",&find_this.citizen_ID);
    getchar();
    
    for (int i = 0; i < size; i++) {
        if (compare(member[i], find_this)) {
            return i;
        }
    }
    return -1;
}

void changeMemberinfo(struct Member *member, int index){
    printf("Which info do you want to change? (1-member_id, 2-member_name, 3-member_citizen_ID, 4-member_dayOfBirth, 5-member_email, 6-member_gender, 7-member_register_date, 8-member_expired_date)");
    int change_option;
    int day, month, year;
    scanf(" %d", &change_option);
    getchar();
    switch(change_option) {
        case 1:
            printf("Enter new member_id: ");
            // fflush(stdout);
            scanf("%d", &member[index].id);
            getchar();
            break;
        case 2:
            printf("Enter new member_name: ");
            fgets(member[index].name, MAX_NAME_LENGTH, stdin);  // Nhập tên thành viên
            member[index].name[strlen(member[index].name)-1] = '\0';  // Loại bỏ ký tự \n                                
            break;
        case 3:
            printf("Enter new member_citizen_ID: ");
            scanf("%d", &member[index].citizen_ID);
            getchar();
            break;
        case 4:
            printf("Enter new day of birth (dd/mm/yyyy): ");
            scanf("%d/%d/%d", &day, &month, &year);
            getchar();
            member[index].dayOfBirth = countDays(day, month, year);
        case 5:
            printf("Enter new email: ");
            fgets(member[index].email, MAX_NAME_LENGTH, stdin);  // Nhập tên thành viên
            member[index].email[strlen(member[index].email)-1] = '\0';  // Loại bỏ ký tự \n 
            break;
        case 6:
            printf("Enter new gender (male/female/other): ");
            fgets(member[index].gender, MAX_NAME_LENGTH, stdin);  // Nhập tên thành viên
            member[index].gender[strlen(member[index].gender)-1] = '\0';  // Loại bỏ ký tự \n 
            break;
        case 7:
            printf("Enter new register date (dd/mm/yyyy): ");
            scanf("%d/%d/%d", &day, &month, &year);
            getchar();
            member[index].register_date = countDays(day, month, year);
        case 8:
            printf("Enter new expired date (dd/mm/yyyy): ");
            scanf("%d/%d/%d", &day, &month, &year);
            getchar();
            member[index].expired_date = countDays(day, month, year);
            break;
        default:
            printf("Invalid option\n");
    }
}

void deleteMember(struct Member *member,int index , int amount_of_current_member){
    /*HANDLE 'DELETING FUNCTION' FOR N MEMBER*/
    //index is where to delete
    for (int i = index; i < amount_of_current_member ; i++) {
        // member[i].id = member[i + 1].id;
        // strcpy(member[i].name, member[i + 1].name);
        // member[i].citizen_ID = member[i + 1].citizen_ID;
        // member[i].dayOfBirth = member[i + 1].dayOfBirth;
        // strcpy(member[i].email, member[i + 1].email);
        // strcpy(member[i].gender, member[i + 1].gender);
        // member[i].register_date = member[i + 1].register_date;
        // member[i].borrowed_book = member[i + 1].borrowed_book;
        // // memmove(&member_borrowed_ISBN[i], &member_borrowed_ISBN[i + 1], sizeof(member_borrowed_ISBN[i]) * member_borrowed_book[i]);
        // for (int j = 0; j < MAX_BOOK; j++) {
        //     member[i].borrowed_ISBN[j] = member[i + 1].borrowed_ISBN[j];
        // }
        member[i]= member[i+1];
    }
}