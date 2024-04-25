#include "book_function.h"


void printBook(struct Book book) {
    printf("----------------------------- \n");
    printf("ISBN: %d\n", book.ISBN);
    printf("name: %s\n", book.name);
    printf("author: %s\n", book.author);
    printf("publishing company: %s\n", book.publishing_company);
    printf("publishing year: %d\n", book.publishing_year);
    printf("type: %s\n", book.type);
    printf("price: %d\n", book.price);
    printf("stock: %d\n", book.amount);
    printf("----------------------------- \n\n");
}

// Hàm so sánh ID
bool compare_book_ISBN(struct Book a, struct Book b) {
    return a.ISBN == b.ISBN;
}

// Hàm so sánh tên
bool compare_book_name(struct Book a, struct Book b) {
    return strcmp(a.name, b.name) == 0;
}

//Hàm tìm kiếm trong member
int find_in_books(struct Book book[], int size, bool (*compare)(struct Book, struct Book), char compare_function_name[MAX_NAME_LENGTH]) {
    struct Book find_this;
    if(strcmp(compare_function_name, "compare_book_ISBN") == 0){
    printf("Enter ISBN to search: ");
    if (scanf(" %d", &find_this.ISBN) != 1) {
        // Người dùng không nhập số, đặt ISBN thành một giá trị không hợp lệ
        find_this.ISBN = -1;
    }
    getchar();
    } else if(strcmp(compare_function_name, "compare_book_name") == 0){
        printf("Enter name to search: ");
        fgets(&find_this.name, MAX_NAME_LENGTH, stdin);
        find_this.name[strlen(find_this.name)-1] = '\0';  // Loại bỏ ký tự xuống dòng
    }

    for (int i = 0; i < size; i++) {
        if (compare(book[i], find_this)) {
            return i;
        }
    }
    return -1;
}

int writeToBook(struct Book *book,struct CurrentIndex *currentIdx){
    // int index = number_of_current_book_index;
    printf("Enter book_ISBN: ");
    scanf(" %d", &book[currentIdx->book_index].ISBN);
    getchar();

    printf("Enter book_name: ");
    fgets(book[currentIdx->book_index].name, MAX_NAME_LENGTH, stdin);
    book[currentIdx->book_index].name[strlen(book[currentIdx->book_index].name)-1] = '\0'; // bỏ \n

    printf("Enter book_author: ");
    fgets(book[currentIdx->book_index].author, MAX_NAME_LENGTH, stdin);
    book[currentIdx->book_index].author[strlen(book[currentIdx->book_index].author)-1] = '\0'; // bỏ \n

    printf("Enter book_publishing_company: ");
    fgets(book[currentIdx->book_index].publishing_company, MAX_NAME_LENGTH, stdin);
    book[currentIdx->book_index].publishing_company[strlen(book[currentIdx->book_index].publishing_company)-1] = '\0'; // bỏ \n

    printf("Enter book_publishing_year: ");
    scanf(" %d", &book[currentIdx->book_index].publishing_year);
    getchar();

    printf("Enter book_type: ");
    fgets(book[currentIdx->book_index].type, MAX_NAME_LENGTH, stdin);
    book[currentIdx->book_index].type[strlen(book[currentIdx->book_index].type)-1] = '\0'; // bỏ \n

    printf("Enter book_price: ");
    scanf(" %d", &book[currentIdx->book_index].price);
    getchar();

    printf("Enter book_amount: ");
    scanf(" %d", &book[currentIdx->book_index].amount);
    getchar();

    return ++currentIdx->book_index;
}


int changeBookinfo(struct Book *book, int index) {
    printf("Enter info to change (book_ISBN, book_author, book_publishing_company, book_publishing_year, book_type, book_price, book_amount, book_name): ");
    char info_to_change[MAX_NAME_LENGTH];
    fgets(info_to_change, MAX_NAME_LENGTH, stdin);
    info_to_change[strcspn(info_to_change, "\n")] = '\0'; // bỏ \n

    if(strcmp(info_to_change, "book_ISBN") == 0){
        printf("Enter new ISBN: ");
        scanf(" %d", &book[index].ISBN);
        getchar();
    }
    else if(strcmp(info_to_change, "book_author") == 0){
        printf("Enter new author: ");
        fgets(book[index].author, MAX_NAME_LENGTH, stdin);
        book[index].author[strlen(book[index].author)-1] = '\0'; // bỏ \n
    }
    else if(strcmp(info_to_change, "book_publishing_company") == 0){
        printf("Enter new publishing_company: ");
        fgets(book[index].publishing_company, MAX_NAME_LENGTH, stdin);
        book[index].publishing_company[strlen(book[index].publishing_company)-1] = '\0'; // bỏ \n
    }
    else if(strcmp(info_to_change, "book_publishing_year") == 0){
        printf("Enter new publishing_year: ");
        scanf(" %d", &book[index].publishing_year);
        getchar();
    }
    else if(strcmp(info_to_change, "book_type") == 0){
        printf("Enter new type: ");
        fgets(book[index].type, MAX_NAME_LENGTH, stdin);
        book[index].type[strcspn(book[index].type, "\n")] = '\0'; // bỏ \n
    }
    else if(strcmp(info_to_change, "book_price") == 0){
        printf("Enter new price: ");
        scanf(" %d", &book[index].price);
        getchar();
    }
    else if(strcmp(info_to_change, "book_amount") == 0){
        printf("Enter new amount: ");
        scanf(" %d", &book[index].amount);
        getchar();
    }
    else if (strcmp(info_to_change, "book_name") == 0) { // Đổi tên sách
        printf("Enter new name: ");
        fgets(book[index].name, MAX_NAME_LENGTH, stdin);
        book[index].name[strlen(book[index].name) - 1] = '\0'; // bỏ \n
    }
    else{
        printf("Invalid info to change\n");
        return -1;
    }
return 0;
}

void deleteBook(struct Book *book,int index , int amount_of_current_book){
    /*HANDLE 'DELETING FUNCTION' FOR N BOOK*/
    //index is where to delete
    for (int i = index; i < amount_of_current_book ; i++) {
        book[i]= book[i+1];
    }
}

// void book_management() {
           
// }