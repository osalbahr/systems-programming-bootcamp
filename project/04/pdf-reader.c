#include <stdio.h>
#include <stdlib.h>

typedef struct PDF_Info {
    // %PDF-
    char magic_code[5 + 1];
    int major_version;
    int minor_version;
    int page_count;
} PDF_Info;

PDF_Info read_pdf_info(char *filename)
{
    PDF_Info info;

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("ERROR: Cannot open '%s'.\n", filename);
        exit(1);
    }

    for (int i = 0; i < 5; i++) {
        info.magic_code[i] = getc(fp);
    }
    info.magic_code[5] = '\0';

    fscanf(fp, "%d.%d", &info.major_version, &info.minor_version);

    for (;;) {
        if (getc(fp) == 'C') {
            if (getc(fp) == 'o') {
                if (getc(fp) == 'u') {
                    if (getc(fp) == 'n') {
                        if (getc(fp) == 't') {
                            fscanf(fp, "%d", &info.page_count);
                            break;
                        }
                    }
                }
            }
        }
    }

    fclose(fp);

    return info;
}

int main()
{
    char *filenames[] = {
        "Thompson_1984_ReflectionsonTrustingTrust.pdf",
        "To the Budget Council concerning Haskell.pdf",
    };

    int count = sizeof(filenames) / sizeof(*filenames);
    for (int i = 0; i < count; i++) {
        PDF_Info info = read_pdf_info(filenames[i]);
        printf("Filename: %s\n", filenames[i]);
        printf("Magic code: %5s\n", info.magic_code);
        printf("PDF version: %d.%d\n", info.major_version, info.minor_version);
        printf("Page count: %d\n", info.page_count);
        
        if (i != count - 1) {
            puts("");
        }
    }
    
}
