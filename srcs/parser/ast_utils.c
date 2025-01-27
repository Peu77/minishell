/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:15:33 by eebert            #+#    #+#             */
/*   Updated: 2025/01/25 18:32:38 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <minishell.h>

void	free_ast_node(void *content)
{
	t_ast_node	*node;

	node = content;
	if (node->left)
		free_ast_node(node->left);
	if (node->right)
		free_ast_node(node->right);
	gc_free_ptr(node->value);
	node->value = NULL;
	if (node->heredoc_filename)
	{
		unlink(node->heredoc_filename);
		gc_free_ptr(node->heredoc_filename);
		node->heredoc_filename = NULL;
	}
	if (node->type == AST_COMMAND)
	{
		gc_list_clear(&node->redirects, free_redirect);
		node->redirects = NULL;
	}
	gc_free_ptr(node);
}

t_ast_node	*create_ast_node(t_ast_type type, char *value, t_list *redirects)
{
	t_ast_node	*node;

	node = gc_malloc(sizeof(t_ast_node));
	node->type = type;
	node->value = value;
	node->redirects = redirects;
	node->heredoc_filename = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

bool	parse_redirects_from_node(t_ast_node *node, int *redirect_exit_code)
{
	char	*tmp;

	if (!node->value)
		return (true);
	tmp = filter_and_get_redirects(node->value, &node->redirects,
			redirect_exit_code);
	gc_free_ptr(node->value);
	node->value = tmp;
	if (*redirect_exit_code != 0)
	{
		get_shell()->exit_status = *redirect_exit_code;
		if (*redirect_exit_code == 258)
			pe("parse error, each redirect should have an filename");
		return (1);
	}
	return (0);
}

void	expand_ast_node(t_ast_node *node)
{
	char	*tmp;

	if (node->value == NULL)
		return ;
	tmp = expand_string(node->value);
	gc_free_ptr(node->value);
	node->value = tmp;
	tmp = expand_wildcards(node->value);
	gc_free_ptr(node->value);
	node->value = tmp;
}
