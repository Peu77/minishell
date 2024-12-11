#include "../includes/minishell.h"
#include <termios.h>

/*

void handle_sigint(int sig)
{
    (void)sig;
    printf("\n >>>> Minishell");
}



void configure_terminal()
{
    struct termios term_settings;

    if (tcgetattr(STDIN_FILENO, &term_settings) == -1)
    {
        perror("Erreur lors de la récupération des paramètres du terminal");
        exit(EXIT_FAILURE);
    }

    term_settings.c_lflag &= ~ECHOCTL;
    term_settings.c_lflag &= ~(ISIG);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term_settings) == -1)
    {
        perror("Erreur lors de la configuration des paramètres du terminal");
        exit(EXIT_FAILURE);
    }
}
*/

int main(int argc, char **argv, char **envp)
{
	pe("WELCOME TO MINISHELL");
	char *user_prompt;
	(void)argc;
	(void)argv;

 //   signal(SIGINT, handle_sigint);
  //  signal(SIGQUIT, SIG_IGN);
	while (1)
	{
//		configure_terminal();
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
