/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:35:30 by eebert            #+#    #+#             */
/*   Updated: 2025/01/25 16:11:23 by eebert           ###   ########.fr       */
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

static void	handle_shell_input(char *line)
{
	t_command	*command;
	t_ast_node	*node;

	command = NULL;
	node = parse(line);
	if (node == NULL)
	{
		if (get_shell()->exit_status == EXIT_SUCCESS)
			get_shell()->exit_status = EXIT_FAILURE;
		return (gc_free_ptr(line));
	}
	if (!traverse_heredocs(node))
	{
		free_ast_node(node);
		gc_free_ptr(line);
		if (get_shell()->exit_status == EXIT_SUCCESS)
			get_shell()->exit_status = EXIT_FAILURE;
		return ;
	}
	tree_monitor(node, command);
	free_ast_node(node);
	gc_free_ptr(line);
}

void	minishell_interactive(void)
{
	char	*user_prompt;

	user_prompt = NULL;
	main_signals();
	while (!get_shell()->should_exit)
	{
		if (!get_user_prompt(&user_prompt))
			break ;
		gc_add(user_prompt);
		handle_shell_input(user_prompt);
	}
}

void	minishell_non_interactive(void)
{
	char	*line;

	while (!get_shell()->should_exit)
	{
		line = get_next_line(fileno(stdin));
		if (line == NULL)
			break ;
		if (*line == '\0')
		{
			gc_free_ptr(line);
			continue ;
		}
		handle_shell_input(line);
	}
}

void	minishell_non_interactive_argument(char **args, int argc)
{
	char	*line;

	line = join_str_array(args, argc);
	handle_shell_input(line);
}
