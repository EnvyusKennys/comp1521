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
    int x = 0;
    int print[3] = {0};
    int end = 0;

    while (c != EOF)
    {
        if (isprint(c) != 0)
        {
            if (count < 3)
            {
                print[count] = c;
            }
            else
            {
                if (x == 0)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        printf("%c", print[i]);
                    }
                    x = 1;
                }
                printf("%c", c);
            }
            count++;
        }
        else
        {
            if (count > 3)
            {
                printf("\n");
                end++;
            }
            count = 0;
            x = 0;
        }
        c = fgetc(f);
    }

    if (count > 3 && end == 0)
    {
        printf("\n");
    }

    return 0;
}