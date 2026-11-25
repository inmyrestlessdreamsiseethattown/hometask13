#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
void getDates(char d1[], char d2[]);
int writefile(const char *surname, const char *book,
              const char *d1, const char *d2);
int main(void)
{
    char surname[50];
    char book[100];
    char d1[16];
    char d2[16];
    printf("Программа библиотечной выдачи\n");
    printf("Введите фамилию читателя: ");
    if (scanf("%49s", surname) != 1)
    {
        printf("Ошибка ввода\n");
        return 1;
    }
    printf("Введите название книги: ");
    if (scanf("%99s", book) != 1)
    {
        printf("Ошибка ввода\n");
        return 1;
    }

    getDates(d1, d2);
    if (writefile(surname, book, d1, d2) == 0)
    {
        printf("Ошибка записи файла\n");
        return 1;
    }
    printf("\nФамилия: %s\n", surname);
    printf("Книга: %s\n", book);
    printf("Дата выдачи: %s\n", d1);
    printf("Дата возврата: %s\n", d2);
    printf("\nДанные сохранены в library.txt\n");
    return 0;
}

void getDates(char d1[], char d2[])
{
    time_t now = time(NULL);
    time_t back = now + 14 * 24 * 60 * 60;
    strftime(d1, 16, "%Y-%m-%d", localtime(&now));
    strftime(d2, 16, "%Y-%m-%d", localtime(&back));
}

int writefile(const char *surname, const char *book,
              const char *d1, const char *d2)
{
    FILE *out = fopen("library.txt", "a");
    if (out == NULL)
    {
        return 0;
    }

    if (fprintf(out, "%s %s выдано:%s вернуть:%s\n",
                surname, book, d1, d2) < 0)
    {
        fclose(out);
        return 0;
    }

    if (fclose(out) != 0)
    {
        return 0;
    }
    return 1;
}
