/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:09:02 by eebert            #+#    #+#             */
/*   Updated: 2025/01/27 14:13:27 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <minishell.h>
#include <stdio.h>

t_ast_node	*parse_primary(t_list **tokens);

t_ast_node	*parse_pipe(t_list **tokens)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;

	left = parse_primary(tokens);
	while (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN_PIPE)
	{
		pipe_node = create_ast_node(AST_PIPE, NULL, NULL);
		*tokens = (*tokens)->next;
		if (!left)
		{
			get_shell()->exit_status = 2;
			return (pec("Invalid pipe node: missing children"), NULL);
		}
		pipe_node->left = left;
		pipe_node->right = parse_primary(tokens);
		left = pipe_node;
	}
	return (left);
}

t_ast_node	*parse_logical(t_list **tokens)
{
	t_ast_node	*left;
	t_ast_type	logical_type;
	t_token		*current;
	t_ast_node	*logical_node;

	left = parse_pipe(tokens);
	while (*tokens)
	{
		current = (*tokens)->content;
		if (current->type == TOKEN_AND)
			logical_type = AST_AND;
		else if (current->type == TOKEN_OR)
			logical_type = AST_OR;
		else if (current->type == TOKEN_SEMICOLON)
			logical_type = AST_SEMICOLON;
		else
			break ;
		*tokens = (*tokens)->next;
		logical_node = create_ast_node(logical_type, NULL, NULL);
		logical_node->left = left;
		logical_node->right = parse_pipe(tokens);
		left = logical_node;
	}
	return (left);
}

t_ast_node	*parse_parentheses(t_list **tokens)
{
	t_ast_node	*parentheses_node;

	while (*tokens && is_empty_str_token((*tokens)->content))
		*tokens = (*tokens)->next;
	if (!*tokens
		|| ((t_token *)(*tokens)->content)->type != TOKEN_PARENTHESES_OPEN)
		return (NULL);
	*tokens = (*tokens)->next;
	parentheses_node = create_ast_node(AST_PARENTHESES, NULL, NULL);
	parentheses_node->left = parse_logical(tokens);
	if (!*tokens
		|| ((t_token *)(*tokens)->content)->type != TOKEN_PARENTHESES_CLOSE)
		return (free_ast_node(parentheses_node), NULL);
	*tokens = (*tokens)->next;
	if ((*tokens) && ((t_token *)(*tokens)->content)->type == TOKEN_STRING)
	{
		parentheses_node->value = gc_add(ft_strdup(((t_token *)
						(*tokens)->content)->value));
		(*tokens) = (*tokens)->next;
	}
	return (parentheses_node);
}

t_ast_node	*parse_primary(t_list **tokens)
{
	t_ast_node	*parentheses_node;

	parentheses_node = parse_parentheses(tokens);
	if (parentheses_node)
		return (parentheses_node);
	return (parse_command(tokens));
}

t_ast_node	*parse(char *input)
{
	t_list		*tokens;
	t_list		*tokens_cpy;
	t_ast_node	*result;

	tokens = NULL;
	lex_tokens(input, &tokens);
	if (!tokens)
		return (NULL);
	tokens_cpy = tokens;
	result = parse_logical(&tokens);
	gc_list_clear(&tokens_cpy, free_token);
	if (DEBUG)
		print_ast_node(result, 0);
	return (result);
}

/*

	* compile with: cc lexer.c parser.c ../../libft/libft.a ../error/error.c
		redirects.c ast_utils.c token_utils.c
	-g -I ../../includes
 *
 */

/*
int	main(void) {
	t_ast_node *node = parse("echo hello world >&4 | cat -e | wc
			-l 7>&5 3<<&4");
	if(node == NULL) {
		printf("failed to parse lol\n");
		return (1);
	}
	if(node == PARSE_ERROR) {
		printf("parse error\n");
		return (1);
	}

	printf("result: %d\n", node->type);
	print_ast_node(node, 0);
	free_ast_node(node);
	return (0);
}
*/
