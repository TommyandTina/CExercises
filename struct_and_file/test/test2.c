#include <stdio.h>

#define MAX_NAME_LENGTH 100
#define MAX_BOOK 10
#define MAX_MEMBERS 100

struct Member
{
    int id;
    char name[MAX_NAME_LENGTH];
    // int citizen_ID;
    // int dayOfBirth;
    // char email[MAX_NAME_LENGTH];
    // char gender[MAX_NAME_LENGTH];
    // int register_date;
    // int expired_date;
    // int borrowed_ISBN[MAX_BOOK];
    // int borrowed_book;
};

struct Member member[MAX_MEMBERS];

void save_to_file(struct Member *member) {
    FILE *file = fopen("member_data.bin", "wb");
    if (file != NULL) {
        fwrite(member, sizeof(struct Member), MAX_MEMBERS, file);
        fclose(file);
    } else {
        printf("Không thể mở file để ghi\n");
    }
}

void load_from_file(struct Member *member) {
    FILE *file = fopen("member_data.bin", "rb");
    if (file != NULL) {
        
        fread(member, sizeof(struct Member), MAX_MEMBERS, file);
        fseek(file, 0, SEEK_SET);
        fclose(file);
    } else {
        printf("Không thể mở file để đọc\n");
    }
}

int main() {
    // struct Member member[MAX_MEMBERS] = {123, "Nguyen Van A"};
    // save_to_file(member);

    struct Member member2[MAX_MEMBERS];
    load_from_file(member2);
    printf("Member: id = %d, name = %s\n", member2[0].id, member2[0].name);
    

    return 0;
}
