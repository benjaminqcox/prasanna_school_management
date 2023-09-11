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

    do
    {
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
    char * endPtr = NULL;
    char * strVal = getStringInput();
    int chosenVal = (int)strtol(strVal, &endPtr, 10);
    // while chosenVal == 0 and the user didn't input 0, keep looping
    // strtol fills invalid inputs with 0
    while (chosenVal == 0 && strncmp(strVal, "0", 1) != 0)
    {
        endPtr = NULL;
        strVal = getStringInput();
        chosenVal = (int)strtol(strVal, &endPtr, 10);
    }

    return chosenVal;
}

int getIntInputInRange(int low, int high)
{
    int chosenVal = getIntInput();
    while (chosenVal < low || chosenVal > high)
    {
        chosenVal = getIntInput();
    }
    return chosenVal;
}
