/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:18:25 by eebert            #+#    #+#             */
/*   Updated: 2024/12/11 16:20:07 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

void print_ast_type(const t_ast_type type) {
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

void print_ast_node(t_ast_node *node, int depth) {
    if (!node || node == PARSE_ERROR) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    if (node->type == AST_COMMAND) {
        printf("command: %s\n", node->value);

        t_list *redirects = node->redirects;
        while (redirects) {
            for (int i = 0; i < depth; i++) {
                printf("  ");
            }
            t_redirect *redirect = redirects->content;
            printf("Redirect: %d, %d, %s\n", redirect->fd_left, redirect->fd_right, redirect->file);
            redirects = redirects->next;
        }
    } else {
        printf("Node: %s, Type: ", node->value);
        print_ast_type(node->type);
        printf("\n");
    }


    print_ast_node(node->left, depth + 1);
    print_ast_node(node->right, depth + 1);
}

void print_tokens(t_list* tokens){

    t_token* node;

    while(tokens)
    {
        node = tokens->content;

        if(is_redirect_token(node->type))
            printf("TOKEN_REDIRECT: %d, %d, %d, %s\n", node->type, ((t_redirect*)node->data)->fd_left, ((t_redirect*)node->data)->fd_right, ((t_redirect*)node->data)->file);
        else if(node->type == TOKEN_STRING)
            printf("TOKEN_STRING: %s\n", node->value);
        else
            printf("TOKEN: %d\n", node->type);
        tokens = tokens->next;
    }
}
