/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:15:33 by eebert            #+#    #+#             */
/*   Updated: 2024/12/16 11:32:39 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include "parse.h"

void free_ast_node(void *content) {
    t_ast_node *node;

    node = content;

    if(node->left)
        free_ast_node(node->left);

    if(node->right)
        free_ast_node(node->right);

    if(node->type == AST_COMMAND) {
        ft_lstclear(&node->redirects, free_redirect);
    }
    free(node->value);
    free(node);
}

t_ast_node* create_ast_node(t_ast_type type, char *value, t_list* redirects) {
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if(!node)
        return (NULL);
    node->type = type;
    node->value = value;
    node->redirects = redirects;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// TODO: handle memory leaks
bool parse_env_variables(t_ast_node* node) {
    if(node->type != AST_COMMAND)
        return (pe("tried to parse env variables in a non command node"),false);

    char* str;
    int i;
    int k;
    char* sub_str;

     i = 0;
    str = node->value;
    while(str[i]) {
        if(str[i] == '$') {
            k = 0;
            while(ft_isalnum(str[i + k + 1]))
                k++;

            sub_str = ft_substr(str, i + 1, k);
            if(!sub_str)
                return false;
            char* env_value = getenv(sub_str);
            if(env_value) {
                char* new_str = ft_strjoin(ft_substr(str, 0, i), env_value);
                if(!new_str)
                    return (free(sub_str), false);
                char* tmp = ft_strjoin(new_str, str + i + k + 1);
                if(!tmp)
                    return (free(sub_str), free(new_str), false);
                free(node->value);
                node->value = tmp;
                i += ft_strlen(env_value);
                str = node->value;
            }
        }else
        i++;
    }
    return true;
}