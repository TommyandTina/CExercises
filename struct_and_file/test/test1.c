#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_BOOK 10

// Định nghĩa struct CurrentIndex
struct CurrentIndex {
    int member_index;
    int book_index;
    int ticket_index;
};

// Định nghĩa struct Member
struct Member {
    int cur_index;
    int id;
    char name[MAX_NAME_LENGTH];
    int citizen_ID;
    int dayOfBirth;
    char email[MAX_NAME_LENGTH];
    char gender[MAX_NAME_LENGTH];
    int register_date;
    int expired_date;
    int borrowed_ISBN[MAX_BOOK];
    int borrowed_book;
};

// Định nghĩa mã định danh
enum Identifier {
    MEMBER,
    CURRENT_INDEX
};

int main() {
    FILE *outfile;

    // Mở file để ghi
    outfile = fopen("data.dat", "wb");
    if (outfile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        return 1;
    }

    // Tạo và ghi struct vào file
    struct Member member = {1, 123, "Nguyen Van A", 123456789, 19900101, "nguyenvana@gmail.com", "Male", 20220101, 20230101, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10};
    struct CurrentIndex currentIndex = {1, 2, 3};

    enum Identifier memberId = MEMBER;
    fwrite(&memberId, sizeof(enum Identifier), 1, outfile);
    fwrite(&member, sizeof(struct Member), 1, outfile);

    enum Identifier currentIndexId = CURRENT_INDEX;
    fwrite(&currentIndexId, sizeof(enum Identifier), 1, outfile);
    fwrite(&currentIndex, sizeof(struct CurrentIndex), 1, outfile);

    // Đóng file
    fclose(outfile);

    // Mở file để đọc
    FILE *infile;
    infile = fopen("data.dat", "rb");
    if (infile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        return 1;
    }

    // Đọc struct từ file
    struct Member readMember;
    struct CurrentIndex readCurrentIndex;
    enum Identifier readId;

    while (fread(&readId, sizeof(enum Identifier), 1, infile)) {
        switch (readId) {
            // case CURRENT_INDEX:
            //     fread(&readCurrentIndex, sizeof(struct CurrentIndex), 1, infile);
            //     printf("CurrentIndex: member_index = %d, book_index = %d, ticket_index = %d\n", readCurrentIndex.member_index, readCurrentIndex.book_index, readCurrentIndex.ticket_index);
            //     break;
            case MEMBER:
                fread(&readMember, sizeof(struct Member), 1, infile);
                printf("Member: cur_index = %d, id = %d, name = %s\n", readMember.cur_index, readMember.id, readMember.name);
                break;

        }
    }
    // Dời con trỏ về đầu file
    fseek(infile, 0, SEEK_SET);

    while (fread(&readId, sizeof(enum Identifier), 1, infile)) {
        switch (readId) {
            case CURRENT_INDEX:
                fread(&readCurrentIndex, sizeof(struct CurrentIndex), 1, infile);
                printf("CurrentIndex: member_index = %d, book_index = %d, ticket_index = %d\n", readCurrentIndex.member_index, readCurrentIndex.book_index, readCurrentIndex.ticket_index);
                break;
            case MEMBER:
                fread(&readMember, sizeof(struct Member), 1, infile);
                printf("Member: cur_index = %d, id = %d, name = %s\n", readMember.cur_index, readMember.id, readMember.name);
                break;

        }
    }


    // Đóng file
    fclose(infile);

    return 0;
}
