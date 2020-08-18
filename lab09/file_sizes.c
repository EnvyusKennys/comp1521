// comp1521 lab09

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct stat s;
    int i = 1;
    long int size = 0;
    while (i < argc)
    {
        if (stat(argv[i], &s) == -1)
        {
            break;
        }
        printf("%s: %ld bytes\n", argv[i], s.st_size);
        size = size + s.st_size;
        i++;
    }

    printf("Total: %ld bytes\n", size);
    return 0;
}
