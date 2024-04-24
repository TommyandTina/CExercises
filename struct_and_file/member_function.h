#ifndef MEMBER_FUNCTION_H_
#define MEMBER_FUNCTION_H_

#include "setting.h"

struct Member
{
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

void printMember(struct Member *member);
int writeToMember(struct Member *member,struct CurrentIndex *currentIdx);
int find_in_members(struct Member member[MAX_MEMBERS], int size, bool (*compare)(struct Member, struct Member));
bool compare_Citizen_id(struct Member a, struct Member b);
bool compare_name(struct Member a, struct Member b);
void changeMemberinfo(struct Member *member, int index);
void deleteMember(struct Member *member,int index , int amount_of_current_member);

#endif