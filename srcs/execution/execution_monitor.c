#include "../../includes/minishell.h"

void execution_monitor(char *user_prompt)
{
    char *list_builtin[NUM_BUILTINS] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
    int i = 0;

	while (i < NUM_BUILTINS)
	{
		if (ft_strnstr(user_prompt, list_builtin[i], ft_strlen(user_prompt)))
		{
			printf("Found built-in: %s\n So we will use a builtins command \n", list_builtin[i]);
			return ;
		}
		i++;
	}
	printf("No built-in command found.\n So we will use execve command \n");
	execution_command(user_prompt);
}
