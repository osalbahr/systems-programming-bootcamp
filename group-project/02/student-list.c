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
    Student *student = (Student*)malloc(sizeof(Student));
    student->id = id;
    student->name = (char*)malloc(strlen(name) + 1);
    strcpy(student->name, name);
    student->age = age;
    student->next = NULL;
    student->previous = NULL;

    return student;
}

void print_students(Student *head)
{
    for (Student *student = head; student != NULL; student = student->next) {
        printf("id: %d, name: %s, age: %d\n", student->id, student->name, student->age);
    }
    
}

int main()
{
    Student *head = create_student(0, "A", 15);
    Student *s2 = create_student(1, "B", 16);
    Student *s3 = create_student(2, "C", 17);
    head->next = s2;
    s2->next = s3;
    print_students(head);
}
