#include <stdio.h>
#include <stdlib.h>

typedef struct StudentInfo
{
    char initials[3];
    int age;
} StudentInfo;

int main()
{
    // Write {"OA", 99} to a file
    StudentInfo info = {"OA", 99};
    FILE *writer = fopen("file.ia", "wb");
    if (!writer) {
        printf("Error: cannot open 'file.ia' for writing\n");
        exit(1);
    }
    fwrite(&info, sizeof(StudentInfo), 1, writer);
    fclose(writer);

    // Read and output the saved data
    StudentInfo *mallocInfo = (StudentInfo *)malloc(sizeof(StudentInfo));
    if (!mallocInfo) {
        printf("Error: cannot allocate memory\n");
        exit(1);
    }

    FILE *reader = fopen("file.ia", "rb");
    if (!reader) {
        printf("Error: cannot open 'file.ia' for reading\n");
        exit(1);
    }
    fread(mallocInfo, sizeof(StudentInfo), 1, reader);
    fclose(reader);

    printf("Initials = %s, Age = %d\n", mallocInfo->initials, mallocInfo->age);

    free(mallocInfo);
}
