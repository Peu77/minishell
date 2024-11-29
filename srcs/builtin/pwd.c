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

int main()
{
	char *current_dir = pwd();
	if (current_dir != NULL)
	{
		printf("Current Directory: %s\n", current_dir);
		free(current_dir);  // Don't forget to free the allocated memory
	}
	else
	{
		perror("Error getting current directory");
	}
	return 0;
}
