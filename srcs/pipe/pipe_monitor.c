#include "../../includes/minishell.h"

static int count_pipe(char *str)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

void pipe_monitor(char *user_prompt)
{
	int number_pipe;

	number_pipe = count_pipe(user_prompt);

	printf("there is actually %d pipe\n", number_pipe);
}
