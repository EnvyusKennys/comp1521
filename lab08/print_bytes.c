// comp1521 lab08
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        perror(argv[1]);
        return 1;
    }
    int c = fgetc(f);
    int count = 0;
    while (c != EOF)
    {
        if (isprint(c) != 0)
        {
            printf("byte %4d: %3d 0x%02x '%c'\n", count, c, c, c);
        }
        else
        {
            printf("byte %4d: %3d 0x%02x \n", count, c, c);
        }
        count++;
        c = fgetc(f);
    }
    return 0;
}