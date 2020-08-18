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
    int c = fgetc(f);
    int i = 0;
    int x = 0;
    while (c != EOF)
    {
        if (c >= 128 && c <= 255)
        {
            x = 1;
            printf("%s: byte %d is non-ASCII\n", argv[1], i);
            break;
        }
        i++;
        c = fgetc(f);
    }
    if (x == 0)
    {
        printf("%s is all ASCII\n", argv[1]);
    }
    fclose(f);
    return 0;
}
