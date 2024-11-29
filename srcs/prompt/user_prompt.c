#include "../../includes/minishell.h"

int get_user_prompt(char **user_prompt)
{
		size_t len;
		ssize_t nread;

		len = 0;
		printf(">>>> Minishell>$ ");
		nread = getline(user_prompt, &len, stdin);
		if (nread == -1)
			return pe("Problem with getting line");
		if ((*user_prompt)[nread - 1] == '\n')
			(*user_prompt)[nread - 1] = '\0';
	return (1);
}
