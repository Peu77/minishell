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
	if(number_pipe == 0)
		execution_monitor(user_prompt);
	else
		printf("too much pipe for the moment (building)");
}
