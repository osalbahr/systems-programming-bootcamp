#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Flags {
    // 01 -> int
    // 10 -> string
    // 11 -> Student
    unsigned int type:3;
} Flags;

typedef struct Node Node;

typedef struct Node {
    void *data;
    int size;
    Node *next;
    Node *previous;
    Flags flags;
} Node;

typedef struct List {
    Node *first;
    Node *last;
    int count;
} List;

typedef struct Student {
    char *name;
    int age;
} Student;

Node *create_node(void *data, int size, Flags flags)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = malloc(size);
    memcpy(n->data, data, size);
    n->size = size;
    n->next = NULL;
    n->previous = NULL;
    n->flags = flags;
    return n;
}

Student *create_student(char *name, int age)
{
    Student *s = (Student *)malloc(sizeof(Student));
    s->name = (char *)malloc(strlen(name) + 1);
    strcpy(s->name, name);
    s->age = age;
    return s;
}

bool list_add_first(List *lst, Node *n)
{
    if (lst->first == NULL) {
        lst->first = n;
        lst->last = n;
        lst->count++;
        return true;
    }

    n->next = lst->first;
    lst->first->previous = n;
    lst->first = n;
    lst->count++;
    return true;
}

void print_student(Student *s)
{
    printf("data = (Student{'%s', %d})\n", s->name, s->age);
}

void print_node(Node *n)
{
    switch (n->flags.type) {
        case 0b01:
            printf("data = (%d)\n", *((int *)n->data));
            break;
        case 0b10:
            printf("data = ('%s')\n", (char *)n->data);
            break;
        case 0b11:
            print_student((Student *)n->data);
            break;
    }
}

void print_list(List *lst)
{
    for (Node *n = lst->first; n != NULL; n = n->next) {
        print_node(n);
    }
}

List *create_list()
{
    List *lst = (List *)malloc(sizeof(List));
    lst->first = NULL;
    lst->last = NULL;
    lst->count = 0;
    return lst;
}

int main()
{
    List *lst = create_list();
    
    int num = 5;
    Flags num_flags;
    num_flags.type = 0b01;
    Node *num_node = create_node(&num, sizeof(int), num_flags);
    list_add_first(lst, num_node);

    char *name = "Hello";
    Flags name_flags;
    name_flags.type = 0b10;
    Node *name_node = create_node(name, strlen(name) + 1, name_flags);
    list_add_first(lst, name_node);

    Student *s = create_student("Ali", 15);
    Flags student_flags;
    student_flags.type = 0b11;
    Node *student_node = create_node(s, sizeof(Student), student_flags);
    list_add_first(lst, student_node);

    print_list(lst);
}
