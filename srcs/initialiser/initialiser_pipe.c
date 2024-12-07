#include "../../includes/minishell.h"

static int count_pipe(char *str)
{
	int count;
	int i;

	count = 0;
	i = -1;
	while(str[++i])
	{
		if (str[i] == '|')
			count++;
	}
	return (count);
}

int initialise_pipe(t_pipe **pipe, char *user_prompt)
{
	(*pipe)->pid_signal = getpid();
	(*pipe)->number_pipe = count_pipe(user_prompt);
	(*pipe)->number_command = (*pipe)->number_pipe + 1;
	(*pipe)->saved_stdout = 0;
	(*pipe)->should_exit = false;
	return (1);
}
