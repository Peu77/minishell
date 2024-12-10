#include "../../includes/minishell.h"

int get_user_prompt(char **user_prompt)
{
		size_t len;
		ssize_t nread;

		len = 0;
		printf(">>>> Minishell>$ ");
		nread = getline(user_prompt, &len, stdin);
		if (nread == -1) 
    	{
    	    printf("exit\n");
    	    return 0;
    	}
		if (nread == -1)
			return pe(ERROR_GET_LINE);
		remove_newline(*user_prompt);
	return (1);
}
