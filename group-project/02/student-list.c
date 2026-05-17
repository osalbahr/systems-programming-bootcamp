#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student Student;

struct Student {
    int id;
    char *name;
    int age;
    Student *next;
    Student *previous;
};

Student *create_student(int id, const char *name, int age)
{   
    Student *student = (Student *)malloc(sizeof(Student));
    student->id = id;
    student->name = (char *)malloc(strlen(name) + 1);
    strcpy(student->name, name);
    student->age = age;
    student->next = NULL;
    student->previous = NULL;

    return student;
}

void print_students(Student *head)
{
    for (Student *s = head; s != NULL; s = s->next) {
        printf("id: %d, name: %s, age: %d\n", s->id, s->name, s->age);
    }
}

Student *insert_student_first(Student *head, Student *new_head)
{
    if (head == NULL) {
        return new_head;
    }

    Student *ptr = head;

    while (ptr != NULL && ptr->id != new_head->id) {
        ptr = ptr->next;
    }

    if (ptr == NULL){
        new_head->next = head;
    } else {
        printf("student number %d is already in the list\n",new_head->id);
    }

    return new_head;
}

void insert_student_last(Student *head, Student *last)
{
    if (head == NULL) {
        return;
    }

    Student *s = head;
    while (s->next != NULL) {
        s = s->next;
    }

    s->next = last;
}

void update_student_age(Student *head, int id, int new_age)
{
    if (head == NULL) {
        return;
    }

    Student *s = head;

    while (s != NULL && s->id != id) {
        s = s->next;
    }

    if (s == NULL) {
        printf("The student number %d doesn't exist\n", id);
    } else {
        s->age = new_age;
    }
}

int main()
{
    Student *head = create_student(0, "A", 15);
    Student *s2 = create_student(1, "B", 16);
    insert_student_last(head, s2);
    Student *s3 = create_student(2, "C", 17);
    insert_student_last(head, s3);
    Student *s4 = create_student(3, "D", 18);

    print_students(head);

    puts("-----");

    update_student_age(head, 2, 19);
    head = insert_student_first(head,s4);
    print_students(head);
}
