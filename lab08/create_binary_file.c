// comp1521 lab08
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "w");
    if (f == NULL)
    {
        perror(argv[1]);
        return 1;
    }
    int i;
    for (i = 2; i < argc; i++)
    {
        int c = atoi(argv[i]);
        fputc(c, f);
    }
    fclose(f);
    return 0;
}