/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:25:23 by eebert            #+#    #+#             */
/*   Updated: 2025/01/25 17:31:14 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tree_monitor(t_ast_node *node, t_command *command)
{
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (pipe_monitor(node));
	if (node->type == AST_AND)
		return (and_monitor(node, command));
	if (node->type == AST_OR)
		return (or_monitor(node, command));
	if (node->type == AST_SEMICOLON)
		return (semicolon_monitor(node, command));
	if (node->type == AST_PARENTHESES)
		return (parentheses_monitor(node, command));
	if (node->type == AST_COMMAND)
		return (command_monitor(node, command));
	return (0);
}

static bool	process_heredoc(t_list *redirects, t_ast_node *node)
{
	t_list		*current;
	t_redirect	*redirect;

	current = redirects;
	while (current)
	{
		redirect = (t_redirect *)current->content;
		if (redirect->type == TOKEN_REDIRECT_INPUT_APPEND)
		{
			if (!redirection_heredoc(redirect->file, node))
				return (false);
		}
		current = current->next;
	}
	return (true);
}

static bool	handle_parenteses(const char *tmp, t_ast_node *node)
{
	if (node->type != AST_PARENTHESES || is_empty_str(tmp))
		return (true);
	get_shell()->exit_status = 258;
	write(STDERR_FILENO, RED, ft_strlen(RED));
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 48);
	write(STDERR_FILENO, tmp, ft_strlen(tmp));
	write(STDERR_FILENO, "'", 1);
	write(STDERR_FILENO, RESET, ft_strlen(RESET));
	write(STDERR_FILENO, "\n", 1);
	return (false);
}

bool	traverse_heredocs(t_ast_node *node)
{
	t_list	*redirects;
	int		exit_code;
	char	*tmp;
	bool	result;

	if (!node)
		return (true);
	if (node->type != AST_COMMAND)
	{
		if (!traverse_heredocs(node->left))
			return (false);
		if (!traverse_heredocs(node->right))
			return (false);
		if(!(node->type == AST_PARENTHESES && node->value))
		return (true);
	}
	redirects = NULL;
	tmp = filter_and_get_redirects(node->value, &redirects, &exit_code);
	if (!handle_parenteses(tmp, node))
		return (gc_free_ptr(tmp), gc_list_clear(&redirects, free_redirect),
			false);
	gc_free_ptr(tmp);
	result = process_heredoc(redirects, node);
	gc_list_clear(&redirects, free_redirect);
	return (result);
}
