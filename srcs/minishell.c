/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:35:30 by eebert            #+#    #+#             */
/*   Updated: 2025/01/25 00:38:34 by eebert           ###   ########.fr       */
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
		gc_free_ptr(user_prompt);
		return (1);
	}
	return (0);
}

void	minishell_interactive(void)
{
	char		*user_prompt;
	t_command	*command;
	(void) command;
	t_ast_node	*ast_node;

	user_prompt = NULL;
	command = NULL;
	main_signals();
	while (!get_shell()->should_exit)
	{
		if (!get_user_prompt(&user_prompt))
			break ;
		gc_add(user_prompt);
		ast_node = parse(user_prompt);
		if (handle_parse_errors(user_prompt, ast_node))
			continue ;
		if (!traverse_heredocs(ast_node)) {
			free_ast_node(ast_node);
			gc_free_ptr(user_prompt);
				if (get_shell()->exit_status == 0)
			get_shell()->exit_status = 1;
			continue;
		}

		tree_monitor(ast_node, command);
		free_ast_node(ast_node);
		gc_free_ptr(user_prompt);
	}
}

void	minishell_non_interactive(void)
{
	char		*line;
	t_command	*command;
	t_ast_node	*node;

	while (1)
	{
		line = get_next_line(fileno(stdin));
		if (line == NULL)
			break ;
		if (*line == '\0')
		{
			gc_free_ptr(line);
			continue ;
		}
		command = NULL;
		node = parse(line);
		if (handle_parse_errors(line, node))
			continue ;
		if (!traverse_heredocs(node)) {
			free_ast_node(node);
			gc_free_ptr(line);
			if (get_shell()->exit_status == 0)
				get_shell()->exit_status = 1;
			continue;
		}
		tree_monitor(node, command);
		free_ast_node(node);
		gc_free_ptr(line);
	}
}

int	minishell_non_interactive_argument(char **args, int argc)
{
	t_command	*command;
	t_ast_node	*node;
	char		*line;

	line = join_str_array(args, argc);
	if (line == NULL)
		return (EXIT_FAILURE);
	node = parse(line);
	command = NULL;
	if (node == NULL)
		return (gc_free_ptr(line), EXIT_FAILURE);
	if (!traverse_heredocs(node)) {
		free_ast_node(node);
		gc_free_ptr(line);
		if (get_shell()->exit_status == 0)
			get_shell()->exit_status = 1;
		return 0;
	}
	return (tree_monitor(node, command), free_ast_node(node), gc_free_ptr(line),
		EXIT_SUCCESS);
}
