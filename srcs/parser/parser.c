/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:09:02 by eebert            #+#    #+#             */
/*   Updated: 2024/12/08 11:34:51 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include "libft.h"

#include "parse.h"

t_ast_node *parse_primary(t_list **tokens);

void print_ast_type(t_ast_type type) {
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

t_ast_node *parse_command(t_list **tokens) {
    t_ast_node *cmd_node = NULL;
    t_list *redirects = NULL;
    char *cmd_value_cpy;

    t_list *last_valid_token_node = parse_redirects(&redirects, *tokens);


    if (last_valid_token_node == PARSE_ERROR) {
        printf("failed to parse redirects\n");
        return (ft_lstclear(&redirects, free_redirect), PARSE_ERROR);
    }

    while (*tokens && ((t_token *) (*tokens)->content)->type == TOKEN_STRING) {
        if (!cmd_node) {
            cmd_value_cpy = ft_strdup(((t_token *) (*tokens)->content)->value);
            if (!cmd_value_cpy) {
                pe("failed to allocate memory");
                return (ft_lstclear(&redirects, free_redirect), PARSE_ERROR);
            }
            cmd_node = create_ast_node(AST_COMMAND, cmd_value_cpy, redirects);
        } else {
            // append argument to existing command
            size_t len = ft_strlen(cmd_node->value) + ft_strlen(((t_token *) (*tokens)->content)->value) + 2;
            char *new_value = malloc(len);
            if (!new_value) {
                pe("failed to allocate memory");
                return (free_ast_node(cmd_node), PARSE_ERROR);
            }
            ft_strlcpy(new_value, cmd_node->value, len);
            new_value[ft_strlen(cmd_node->value)] = ' ';
            ft_strlcpy(new_value + ft_strlen(cmd_node->value) + 1, ((t_token *) (*tokens)->content)->value, len);
            free(cmd_node->value);
            cmd_node->value = new_value;
        }

        *tokens = (*tokens)->next;
    }

    if (!cmd_node && redirects)
        return (pe("Error parsing, no command found after redirect"), ft_lstclear(&redirects, free_redirect),
                PARSE_ERROR);
    *tokens = last_valid_token_node;

    return cmd_node;
}

t_ast_node *parse_pipe(t_list **tokens) {
    t_ast_node *left = parse_primary(tokens);

    while (*tokens && ((t_token *) (*tokens)->content)->type == TOKEN_PIPE) {
        t_ast_node *pipe_node = create_ast_node(AST_PIPE, NULL, NULL);
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

        t_ast_node *logical_node = create_ast_node(logical_type, NULL, NULL);
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

    t_ast_node *parentheses_node = create_ast_node(AST_PARENTHESES, NULL, NULL);
    if(!parentheses_node)
        return PARSE_ERROR;

    parentheses_node->left = parse_logical(tokens);

    if (!*tokens || ((t_token *) (*tokens)->content)->type != TOKEN_PARENTHESES_CLOSE) {
        free_ast_node(parentheses_node);
        return PARSE_ERROR;
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

    t_list *tokens_cpy = tokens;

    t_ast_node *result = parse_logical(&tokens);
    ft_lstclear(&tokens_cpy, free_token);
    return result;
}

/*
 * compile with: cc lexer.c parser.c ../../libft/libft.a ../error/error.c redirects.c ast_utils.c token_utils.c -g -I ../../includes
 *
 */

/*
int main() {
    t_ast_node *node = parse("echo hello world >&4 | cat -e | wc -l 4>>&3");
    if(node == NULL) {
        printf("failed to parse lol\n");
        return 1;
    }
    if(node == PARSE_ERROR) {
        printf("parse error\n");
        return 1;
    }

    printf("result: %d\n", node->type);
    print_ast_node(node, 0);
    free_ast_node(node);
    return 0;
}
*/

