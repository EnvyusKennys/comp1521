#include <stdio.h>

#include "get_string.h"

// print a line from stream using fgetc (only)
// reads  in at  most one less than size characters from stream and stores them into the
// buffer pointed to by s.  Reading stops after an EOF or a newline.  If a newline is read, it  is
// stored  into  the buffer.  A terminating null byte ('\0') is stored after the last character in the buffer.
void get_string(char *s, int size, FILE *stream)
{
    int c = fgetc(stream);
    int i = 0;
    while (i < size)
    {
        if (c == EOF)
        {
            break;
        }
        else if (c == '\n')
        {
            s[i] = c;
            i++;
            break;
        }
        else
        {
            s[i] = c;
        }
        c = fgetc(stream);
        i++;
    }
    if (i >= size)
    {
        s[i - 1] = '\0';
    }
    else
    {
        s[i] = '\0';
    }
}
