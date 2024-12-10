#include "../includes/minishell.h"

/*
volatile sig_atomic_t sigint_flag = 0;

void handle_sigint(int sig)
{
    (void)sig; // Unused parameter
    sigint_flag = 1; // Set the flag when SIGINT (Ctrl+C) is pressed
    printf("\n"); // Print a new line and prompt
}
*/

int main(int argc, char **argv, char **envp)
{
	pe("WELCOME TO MINISHELL");
	char *user_prompt;
	(void)argc;
	(void)argv;

    //signal(SIGINT, handle_sigint);
	while (1)
	{
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
