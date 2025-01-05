/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:15:33 by eebert            #+#    #+#             */
/*   Updated: 2025/01/05 14:24:30 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include "parse.h"

void free_ast_node(void *content) {
    t_ast_node *node;

    node = content;

    if (node->left)
        free_ast_node(node->left);

    if (node->right)
        free_ast_node(node->right);

    if (node->type == AST_COMMAND) {
        ft_lstclear(&node->redirects, free_redirect);
    }
    free(node->value);
    free(node);
}

t_ast_node *create_ast_node(t_ast_type type, char *value, t_list *redirects) {
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->value = value;
    node->redirects = redirects;
    node->left = NULL;
    node->right = NULL;
    return node;
}
