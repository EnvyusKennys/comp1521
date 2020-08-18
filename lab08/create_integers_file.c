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
    int x = atoi(argv[2]);
    int y = atoi(argv[3]);
    while (x <= y)
    {
        fprintf(f, "%d\n", x);
        x++;
    }
}