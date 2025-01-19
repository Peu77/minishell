/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:28:29 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 11:07:47 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>

static bool	command_token_ast_node(t_ast_node **cmd_node, t_token *token,
		t_list *redirects)
{
	char	*cmd_value_cpy;
	size_t	len;
	char	*new_value;

	if (!*cmd_node)
	{
		cmd_value_cpy = token->value;
		token->value = NULL;
		*cmd_node = create_ast_node(AST_COMMAND, cmd_value_cpy, redirects);
	}
	else
	{
		len = ft_strlen((*cmd_node)->value) + ft_strlen(token->value) + 2;
		new_value = malloc(len);
		if (!new_value)
			return (free_ast_node(*cmd_node), pe(ERROR_MALLOC), false);
		ft_strlcpy(new_value, (*cmd_node)->value, len);
		new_value[ft_strlen((*cmd_node)->value)] = ' ';
		ft_strlcpy(new_value + ft_strlen((*cmd_node)->value) + 1, token->value,
			len);
		free((*cmd_node)->value);
		(*cmd_node)->value = new_value;
	}
	return (true);
}

t_ast_node	*parse_command(t_list **tokens)
{
	t_ast_node	*cmd_node;
	t_list		*redirects;

	cmd_node = NULL;
	redirects = NULL;
	while (*tokens && (((t_token *)(*tokens)->content)->type == TOKEN_STRING))
	{
		if (!command_token_ast_node(&cmd_node, (*tokens)->content, redirects))
			return (ft_lstclear(&redirects, free_redirect), NULL);
		*tokens = (*tokens)->next;
	}
	return (cmd_node);
}
