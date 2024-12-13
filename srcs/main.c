#include "../includes/minishell.h"


int g_last_exit_status = 0;

void minishell_interactive(t_env *env)
{
    char *user_prompt = NULL;
    while (1)
    {
        //main_signals();
        t_command_test *command = NULL;
        if (!get_user_prompt(&user_prompt))
            break;
        t_ast_node *node = parse(user_prompt);
        if (node == NULL)
        {
            free(user_prompt);
            pec("failed to parse\n");
            continue;
        }
        if (node == PARSE_ERROR)
        {
            free(user_prompt);
            pec("parse error\n");
            continue;
        }
        printf("result: %d\n", node->type);
        print_ast_node(node, 0);
        tree_monitor(node, command, env);
        free_ast_node(node);
        free_command(&command);
        free(user_prompt);
        printf("last exit status is %d\n", g_last_exit_status);
    }
}

void minishell_non_interactive(t_env *env)
{
    char *line = NULL;
 	t_command_test *command;
	t_ast_node *node;

    while ((line = readline(NULL)) != NULL)
    {
        if (*line == '\0')
        {
            free(line);
            continue;
        }
        command = NULL;
        node = parse(line);
        if (node == NULL || node == PARSE_ERROR)
        {
            pec("parse error\n");
            free(line);
            continue;
        }
        tree_monitor(node, command, env);
        free_ast_node(node);
        free_command(&command);
        free(line);
    }
    free(line);
}

void minishell_non_interactive_argument(t_env *env, char *line)
{

    t_command_test *command;
	t_ast_node *node;

	node = parse(line);
	command = NULL;
    if (line == NULL)
       return pev("No input provided for non-interactive mode.\n");
    if (node == NULL || node == PARSE_ERROR)
        return pev("parse error\n");
    tree_monitor(node, command, env);
    free_ast_node(node);
    free_command(&command);
}

int main(int argc, char **argv, char **envp)
{
    t_env *env;

	env = initialise_env(envp);
    pe("WELCOME TO MINISHELL");
    if (argc == 2)
    {
        printf("Non-interactive mode with argument: %s\n", argv[1]);
   		minishell_non_interactive_argument(env, argv[1]);
    }
    else if (isatty(STDIN_FILENO))
    {
        printf("Interactive mode\n");
        minishell_interactive(env);
    }
    else
    {
        printf("Non-interactive mode\n");
        minishell_non_interactive(env);
    }
    return (EXIT_SUCCESS);
}
