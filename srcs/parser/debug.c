/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:18:25 by eebert            #+#    #+#             */
/*   Updated: 2025/01/27 14:13:50 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

void	print_ast_type(const t_ast_type type)
{
	if (type == AST_COMMAND)
		printf("command");
	if (type == AST_PIPE)
		printf("pipe");
	if (type == AST_SEMICOLON)
		printf("semicolon");
	if (type == AST_PARENTHESES)
		printf("parentheses");
	if (type == AST_AND)
		printf("and");
	if (type == AST_OR)
		printf("or");
}

void	print_ast_node(t_ast_node *node, int depth)
{
	int	i;

	if (node == NULL)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	print_ast_type(node->type);
	printf("\n");
	print_ast_node(node->left, depth + 1);
	print_ast_node(node->right, depth + 1);
}

void	print_tokens(t_list *tokens)
{
	t_token	*node;

	while (tokens)
	{
		node = tokens->content;
		if (is_redirect_token(node->type))
			printf("TOKEN_REDIRECT: %d, %d, %d, %s\n", node->type,
				((t_redirect *)node->data)->fd_left,
				((t_redirect *)node->data)->fd_right,
				((t_redirect *)node->data)->file);
		else if (node->type == TOKEN_STRING)
			printf("TOKEN_STRING: %s\n", node->value);
		else
			printf("TOKEN: %d\n", node->type);
		tokens = tokens->next;
	}
}
