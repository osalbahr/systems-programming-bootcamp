#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct User User;

typedef struct User {
    unsigned int uid;
    char *uname;
    User *next;
} User;

typedef struct UserList {
    User *head;
} UserList;

typedef struct Follow Follow;

struct Follow {
    unsigned int src_uid;
    unsigned int dest_uid;
    Follow *next;
};

typedef struct FollowList {
    Follow *head;
} FollowList;

UserList *user_list = NULL;
FollowList *follow_list = NULL;

bool insert_user(unsigned int uid, char *uname)
{
    User *new_user = (User *)malloc(sizeof(User));
    new_user->uid = uid;
    new_user->uname = (char *)malloc(strlen(uname) + 1);
    strcpy(new_user->uname, uname);
    new_user->next = NULL;

    if (user_list->head == NULL) {
        user_list->head = new_user;
        return true;
    }

    User *ptr = user_list->head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    ptr->next = new_user;
    return true;
}

bool follow(unsigned int src_uid, unsigned int dest_uid)
{
    Follow *new_follow = (Follow *)malloc(sizeof(Follow));
    new_follow->src_uid = src_uid;
    new_follow->dest_uid = dest_uid;
    new_follow->next = NULL;

    if (follow_list->head == NULL) {
        follow_list->head = new_follow;
        return true;
    }

    Follow *ptr = follow_list->head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    ptr->next = new_follow;
    return true;
}

char *get_name(unsigned int uid)
{
    for (User *u = user_list->head; u != NULL; u = u->next) {
        if (u->uid == uid) {
            return u->uname;
        }
    }

    printf("Error: Cannot find user with uid %d\n", uid);
    exit(1);
}

void print_follow_list()
{
    for (Follow *f = follow_list->head; f != NULL; f = f->next) {
        printf("%d (%s) follows %d (%s)\n",
            f->src_uid, get_name(f->src_uid),
            f->dest_uid, get_name(f->dest_uid));
    }
}

void print_user_report(unsigned int uid)
{
    printf("%d (%s) following: ", uid, get_name(uid));
    for (Follow *f = follow_list->head; f != NULL; f = f->next) {
        if (f->src_uid == uid) {
            printf("%d (%s) ", f->dest_uid, get_name(f->dest_uid));
        }
    }
    puts("");

    printf("%d (%s) followers: ", uid, get_name(uid));
    for (Follow *f = follow_list->head; f != NULL; f = f->next) {
        if (f->dest_uid == uid) {
            printf("%d (%s) ", f->src_uid, get_name(f->src_uid));
        }
    }
    puts("");
}

int main()
{
    user_list = (UserList *)malloc(sizeof(UserList));
    user_list->head = NULL;

    follow_list = (FollowList *)malloc(sizeof(FollowList));
    follow_list->head = NULL;

    insert_user(1, "Ali");
    insert_user(2, "Bob");
    insert_user(3, "Carl");
    insert_user(4, "Danny");
    insert_user(5, "Eagel");
    insert_user(6, "Fatima");

    follow(1, 2);
    follow(1, 3);
    follow(1, 4);

    follow(2, 1);
    follow(2, 4);

    follow(3, 5);

    follow(4, 1);
    follow(4, 2);

    follow(5, 6);
    
    follow(6, 1);

    print_follow_list();

    puts("----------------");

    for (int i = 1; i <= 6; i++) {
        print_user_report(i);
        if (i != 6) {
            puts("----------------");
        }
    }
}

