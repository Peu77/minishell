#include "../../includes/minishell.h"

char *pwd() 
{
    char *buffer = malloc(MAX_PATH);
    if (buffer == NULL)
        return NULL;
    if (getcwd(buffer, MAX_PATH) == NULL)
	{
		pe("error with getting path");
        free(buffer);
        return NULL;
    }
    return (buffer);
}
