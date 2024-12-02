/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:09:02 by eebert            #+#    #+#             */
/*   Updated: 2024/12/02 20:53:28 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include "libft.h"

#include "parse.h"

t_ast_node *parse_primary(t_list **tokens);

void print_ast_type(t_ast_type type) {
    if(type == AST_COMMAND)
        printf("command");
    if(type == AST_PIPE)
        printf("pipe");
    if(type == AST_SEMICOLON)
        printf("semicolon");
    if(type == AST_REDIRECT_INPUT)
        printf("redirect input");
    if(type == AST_REDIRECT_OUTPUT)
        printf("redirect output");
    if(type == AST_PARENTHESES)
        printf("parentheses");
    if(type == AST_AND)
        printf("and");
    if(type == AST_OR)
        printf("or");
    if(type == AST_REDIRECT_APPEND)
        printf("redirect append");
}

void print_ast_node(t_ast_node *node, int depth) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf("Node: %s, Type: ", node->value);
    print_ast_type(node->type);
    printf("\n");

    print_ast_node(node->left, depth + 1);
    print_ast_node(node->right, depth + 1);
}

t_ast_node *parse_command(t_list **tokens) {
    t_ast_node *cmd_node = NULL;

    while (*tokens && ((t_token *) (*tokens)->content)->type == TOKEN_STRING) {
        if (!cmd_node) {
            cmd_node = malloc(sizeof(t_ast_node));
            cmd_node->type = AST_COMMAND;
            cmd_node->value = ft_strdup(((t_token *) (*tokens)->content)->value);
            cmd_node->left = NULL;
            cmd_node->right = NULL;
        } else {
            // append argument to existing command
            // TODO: handle memory leaks
            size_t len = ft_strlen(cmd_node->value) + ft_strlen(((t_token *) (*tokens)->content)->value) + 2;
            char *new_value = malloc(len);
            ft_strlcpy(new_value, cmd_node->value, len);
            new_value[ft_strlen(cmd_node->value)] = ' ';
            ft_strlcpy(new_value + ft_strlen(cmd_node->value) + 1, ((t_token *) (*tokens)->content)->value, len);
            free(cmd_node->value);
            cmd_node->value = new_value;
        }

        *tokens = (*tokens)->next;
    }

    return cmd_node;
}

t_ast_node *parse_pipe(t_list **tokens) {
    t_ast_node *left = parse_primary(tokens);

    while (*tokens && ((t_token *) (*tokens)->content)->type == TOKEN_PIPE) {
        t_ast_node *pipe_node = malloc(sizeof(t_ast_node));
        pipe_node->type = AST_PIPE;
        *tokens = (*tokens)->next;

        pipe_node->left = left;
        pipe_node->right = parse_primary(tokens);

        left = pipe_node;
    }

    return left;
}

t_ast_node *parse_logical(t_list **tokens) {
    t_ast_node *left = parse_pipe(tokens);

    while (*tokens) {
        t_ast_type logical_type;

        t_token *current = (*tokens)->content;
        if (current->type == TOKEN_AND) {
            logical_type = AST_AND;
        } else if (current->type == TOKEN_OR) {
            logical_type = AST_OR;
        } else {
            break;
        }

        *tokens = (*tokens)->next;

        t_ast_node *logical_node = malloc(sizeof(t_ast_node));
        logical_node->type = logical_type;
        logical_node->left = left;
        logical_node->right = parse_pipe(tokens);

        left = logical_node;
    }

    return left;
}



t_ast_node *parse_parentheses(t_list **tokens) {
    if (!*tokens || ((t_token *) (*tokens)->content)->type != TOKEN_PARENTHESES_OPEN) {
        return NULL;
    }

    *tokens = (*tokens)->next;

    t_ast_node *parentheses_node = malloc(sizeof(t_ast_node));
    parentheses_node->type = AST_PARENTHESES;

    parentheses_node->left = parse_logical(tokens);

    if (!*tokens || ((t_token *) (*tokens)->content)->type != TOKEN_PARENTHESES_CLOSE) {
        free(parentheses_node->value);
        free(parentheses_node);
        return NULL;
    }

    *tokens = (*tokens)->next;

    return parentheses_node;
}

t_ast_node *parse_primary(t_list **tokens) {
    t_ast_node *parentheses_node = parse_parentheses(tokens);
    if (parentheses_node) {
        return parentheses_node;
    }

    return parse_command(tokens);
}

t_ast_node *parse(char *input) {
    t_list *tokens = NULL;

    lex_tokens(input, &tokens);

    if (!tokens) {
        return NULL;
    }

    return parse_logical(&tokens);
}

/*
 * compile with: cc lexer.c parser.c ../../libft/libft.a -I ../../includes && ./a.out
 *
 */


int main() {
    t_ast_node *node = parse("ls la | (grep test && echo hello) || echo world");
    printf("result: %d\n", node->type);
    print_ast_node(node, 0);
    return 0;
}

