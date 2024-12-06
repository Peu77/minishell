#include "../../includes/minishell.h"

int pwd(void) 
{
    char *buffer = malloc(MAX_PATH);
    if (buffer == NULL)
        return (0);
    if (getcwd(buffer, MAX_PATH) == NULL)
	{
		pe("error with getting path");
        free(buffer);
        return (0);
    }
	printf("%s \n", buffer);
	return (1);
}
