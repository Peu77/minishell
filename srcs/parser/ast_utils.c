/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:15:33 by eebert            #+#    #+#             */
/*   Updated: 2024/12/04 14:01:43 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void free_ast_node(void *content) {
    t_ast_node *node;

    node = content;
    if(node->type == AST_COMMAND) {
        ft_lstclear(&node->redirects, free_redirect);
    }
    free(node->value);
    free(node);
}

