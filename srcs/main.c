#include "../includes/minishell.h"

/*
void sighandler(int sig)
{
    (void)sig;
    rl_on_new_line();
    rl_replace_line("", 0);
	rl_redisplay();
    printf("\n>>>> Minishell>$ ");
}

void handle_signals(void)
{
    signal(SIGINT, sighandler); 
    signal(SIGQUIT, SIG_IGN);
}
*/

int main(int argc, char **argv, char **envp)
{
	pe("WELCOME TO MINISHELL");
	char *user_prompt;
	(void)argc;
	(void)argv;

	while (1)
	{
		//handle_signals();
		t_command_test *command = NULL;
		user_prompt = NULL;
		if(!get_user_prompt(&user_prompt))
			break;
		t_ast_node  *node = parse(user_prompt);
		if(node == NULL)
		{
			free(user_prompt);
			return pec("failed to parse\n");
		}
		if(node == PARSE_ERROR)
		{
			free(user_prompt);
			return pec("parse error\n");
		}
		printf("result: %d\n", node->type);
		print_ast_node(node, 0);
		tree_monitor(node, command, envp);
		free_ast_node(node);	
		free_command(&command);
		free(user_prompt);
	}
	return (EXIT_SUCCESS);
}

