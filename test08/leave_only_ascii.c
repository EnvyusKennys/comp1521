#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        perror(argv[1]);
        return 1;
    }
    FILE *new = fopen("new", "w");
    int c = fgetc(f);
    while (c != EOF)
    {
        if (c < 128 || c > 255)
        {
            fputc(c, new);
        }
        c = fgetc(f);
    }
    fclose(f);
    fclose(new);

    FILE *new1 = fopen("new", "r");
    FILE *f1 = fopen(argv[1], "w");

    c = fgetc(new1);
    while (c != EOF)
    {
        fputc(c, f1);
        c = fgetc(new1);
    }
    fclose(f1);
    fclose(new1);
    remove("new");

    return 0;
}