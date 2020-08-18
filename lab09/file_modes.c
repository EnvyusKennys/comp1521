// comp1521 lab09

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void printmode(mode_t mode, char *file);
int main(int argc, char *argv[])
{
    struct stat s;
    int i = 1;
    while (i < argc)
    {
        if (stat(argv[i], &s) == -1)
        {
            break;
        }
        stat(argv[i], &s);
        mode_t mode = s.st_mode;
        printmode(mode, argv[i]);
        i++;
    }
    return 0;
}

void printmode(mode_t mode, char *file)
{
    if ((mode & S_IFREG) == S_IFREG)
    {
        printf("-");
    }
    else if ((mode & S_IFDIR) == S_IFDIR)
    {
        printf("d");
    }
    if ((mode & S_IRUSR) == S_IRUSR)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if ((mode & S_IWUSR) == S_IWUSR)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if ((mode & S_IXUSR) == S_IXUSR)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    if ((mode & S_IRGRP) == S_IRGRP)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if ((mode & S_IWGRP) == S_IWGRP)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if ((mode & S_IXGRP) == S_IXGRP)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    if ((mode & S_IROTH) == S_IROTH)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if ((mode & S_IWOTH) == S_IWOTH)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if ((mode & S_IXOTH) == S_IXOTH)
    {
        printf("x ");
    }
    else
    {
        printf("- ");
    }
    printf("%s\n", file);
}