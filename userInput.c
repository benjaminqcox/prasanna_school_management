#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 64


char * getStringInput()
{
    size_t size = 0;
    size_t len  = 0;
    size_t last = 0;
    char *buf = NULL;

    do {
        size += BUFSIZ; /* BUFSIZ is defined as "the optimal read size for this platform" */
        buf = realloc(buf, size); /* realloc(NULL,n) is the same as malloc(n) */            
        /* Actually do the read. Note that fgets puts a terminal '\0' on the
           end of the string, so we make sure we overwrite this */
        if (buf == NULL)
        {
            fprintf(stderr, "Could not reallocate memory\n");
            exit(EXIT_FAILURE);
        }
        fgets(buf + last, BUFSIZ, stdin);
        len = strlen(buf);
        last = len - 1;
    } while (!feof(stdin) && buf[last] != '\n');
    return buf;
}

int getIntInput()
{
    char * endPtr;
    long chosenVal = strtol(getStringInput(), &endPtr, 10);
    return (int)chosenVal;
}

int getIntInputInRange(int low, int high)
{
    return 0;
}
