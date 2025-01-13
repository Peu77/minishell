/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:35:30 by eebert            #+#    #+#             */
/*   Updated: 2025/01/13 19:34:30 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:33 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:51:23 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	print_command(t_command *command)
{
	if (!command)
		return ;
	if (command->path)
		printf("Path: %s\n", command->path);
	else
		printf("Path: NULL\n");
	if (command->argument)
		printf("Argument: %s\n", command->argument);
	else
		printf("Argument: NULL\n");
	if (command->command_name)
		printf("Command Name: %s\n", command->command_name);
	else
		printf("Command Name: NULL\n");
	if (command->redirect)
		printf("Redirect: (Not NULL, need further handling)\n");
	else
		printf("Redirect: NULL\n");
	if (command->saved_stdout)
		printf("Saved Stdout: %d\n", command->saved_stdout);
	else
		printf("Saved Stdout: 0\n");
	if (command->saved_stdin)
		printf("Saved Stdin: %d\n", command->saved_stdin);
	else
		printf("Saved Stdin: 0\n");
}
*/

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}

static int	handle_parse_errors(char *user_prompt, t_ast_node *node)
{
	if (node == NULL)
	{
		free(user_prompt);
		return (1);
	}
	if (node == PARSE_ERROR)
	{
		free(user_prompt);
		return (pec("parse error\n"));
	}
	return (0);
}

void	minishell_interactive(void)
{
	char		*user_prompt;
	t_command	*command;
	t_ast_node	*node;

	user_prompt = NULL;
	command = NULL;
	main_signals();
	while (1)
	{
		if (!get_user_prompt(&user_prompt))
			break ;
		node = parse(user_prompt);
		if (handle_parse_errors(user_prompt, node))
			continue ;
		print_ast_node(node, 0);
		tree_monitor(node, command);
		free_ast_node(node);
		free(user_prompt);
	}
}

void    minishell_non_interactive(void)
{
    char        *line;
    t_command   *command;
    t_ast_node  *node;

    while (1)
    {
        line = readline(NULL);
        if (line == NULL)
            break;
        if (*line == '\0')
        {
            free(line);
            continue ;
        }
        command = NULL;
        node = parse(line);
        if (handle_parse_errors(line, node))
			continue;
        tree_monitor(node, command);
        free_ast_node(node);
        free(line);
    }
}

void	minishell_non_interactive_argument(char *line)
{
	t_command	*command;
	t_ast_node	*node;

	node = parse(line);
	command = NULL;
	if (line == NULL)
		return (pev("No input provided for non-interactive mode.\n"));
	if (node == NULL || node == PARSE_ERROR)
		return (pev("parse error\n"));
	tree_monitor(node, command);
	free_ast_node(node);
}
