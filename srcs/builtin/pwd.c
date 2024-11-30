#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_PATH 1024

char *pwd() 
{
    char *buffer = malloc(MAX_PATH);
    if (buffer == NULL)
        return NULL;
    if (getcwd(buffer, MAX_PATH) == NULL)
	{
        free(buffer);
        return NULL;
    }
    return (buffer);
}
