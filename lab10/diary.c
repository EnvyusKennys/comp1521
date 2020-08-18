// comp1521
// lab10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *value = getenv("HOME");
    char *env = strcat(value, "/.diary");

    FILE *f = fopen(env, "a");
    if (f == NULL)
    {
        perror("HOME");
        return 1;
    }
    for (int i = 1; i < argc; i++)
    {
        fprintf(f, "%s", argv[i]);
        fprintf(f, " ");
    }
    fprintf(f, "\n");
    return 0;
}