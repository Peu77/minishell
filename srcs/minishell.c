/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:33 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 20:12:55 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_command_test(t_command_test *command)
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

void	minishell_interactive(void)
{
	char			*user_prompt;
	t_command_test	*command;
	t_ast_node		*node;

	printf("inter intere");
	user_prompt = NULL;
	command = NULL;
	// main_signals();
	while (1)
	{
		if (!get_user_prompt(&user_prompt))
			break ;
		node = parse(user_prompt);
		if (node == NULL)
		{
			free(user_prompt);
			continue ;
		}
		if (node == PARSE_ERROR)
		{
			free(user_prompt);
			pec("parse error\n");
			continue ;
		}
		print_ast_node(node, 0);
		tree_monitor(node, command);
		free_ast_node(node);
		free(user_prompt);
	}
}

void	minishell_non_interactive(void)
{
	char			*line;
	t_command_test	*command;
	t_ast_node		*node;

	line = NULL;
	while ((line = readline(NULL)) != NULL)
	{
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		command = NULL;
		node = parse(line);
		if (node == NULL || node == PARSE_ERROR)
		{
			pec("parse error\n");
			free(line);
			continue ;
		}
		tree_monitor(node, command);
		free_ast_node(node);
		free(line);
	}
	free(line);
}

void	minishell_non_interactive_argument(char *line)
{
	t_command_test	*command;
	t_ast_node		*node;

	node = parse(line);
	command = NULL;
	if (line == NULL)
		return (pev("No input provided for non-interactive mode.\n"));
	if (node == NULL || node == PARSE_ERROR)
		return (pev("parse error\n"));
	tree_monitor(node, command);
	free_ast_node(node);
}
