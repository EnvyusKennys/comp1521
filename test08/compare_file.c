#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *f1 = fopen(argv[1], "r");
    if (f1 == NULL)
    {
        perror(argv[1]);
        return 1;
    }
    FILE *f2 = fopen(argv[2], "r");
    if (f2 == NULL)
    {
        perror(argv[2]);
        return 1;
    }
    int c1 = fgetc(f1);
    int c2 = fgetc(f2);
    int i = 0;
    int x = 0;
    while (c1 != EOF && c2 != EOF)
    {
        if (c1 != c2)
        {
            printf("Files differ at byte %d\n", i);
            x = 1;
            break;
        }
        i++;
        c1 = fgetc(f1);
        c2 = fgetc(f2);
    }
    if (c1 == EOF)
    {
        if (c2 != EOF)
        {
            printf("EOF on %s\n", argv[1]);
            return 0;
        }
    }
    else if (c2 == EOF)
    {
        if (c1 != EOF)
        {
            printf("EOF on %s\n", argv[2]);
            return 0;
        }
    }

    if (x == 0)
    {
        printf("Files are identical\n");
    }
    fclose(f1);
    fclose(f2);
    return 0;
}