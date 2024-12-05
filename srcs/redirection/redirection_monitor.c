#include "../../includes/minishell.h"


void redirection_monitor(t_command *command, t_pipe *pipe)
{
	char redirection_token = '>';
	printf("we found this redirection : %s \n", command->redirection);
	if (redirection_token == '>')
		redirection_output(command, pipe);
	// a for append( >>)
	else if (redirection_token == 'a')
			redirection_append(command, pipe);
	else if (redirection_token == '<')
			redirection_output(command, pipe);
	else if (redirection_token == 'h')
			redirection_heredoc("eof");
	else
		return ;
}
