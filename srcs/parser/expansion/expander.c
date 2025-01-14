/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:00:04 by eebert            #+#    #+#             */
/*   Updated: 2025/01/14 14:38:56 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *get_char_count() {
    static int char_count = 0;

    return &char_count;
}

static char *strlst_to_str(t_list *lst) {
    char *result;
    int cpy_offset;

    cpy_offset = 0;
    result = malloc(*get_char_count() + 1);
    if (!result)
        return (pe("malloc failed"), NULL);
    result[*get_char_count()] = '\0';
    while (lst) {
        ft_strlcpy(result + cpy_offset, lst->content, ft_strlen(lst->content) + 1);
        cpy_offset += ft_strlen(lst->content);
        lst = lst->next;
    }
    return result;
}

bool interpret_command_string(t_ast_node *node) {
    if (node->type != AST_COMMAND)
        return (pe("tried to parse env variables in a non command node"), false);

    char *str;
    int i;
    t_list *result_chars;
    t_list *new_node;
    *get_char_count() = 0;
    result_chars = NULL;

    i = 0;
    str = node->value;
    while (str[i]) {
        if (str[i] == '\'') {
            i++;
            while (str[i] && str[i] != '\'') {
                new_node = ft_lstnew(ft_substr(str, i, 1));
                (*get_char_count())++;
                if (!new_node)
                    return (ft_lstclear(&result_chars, free), pe("malloc failed"), false);
                ft_lstadd_back(&result_chars, new_node);
                i++;
            }
            i++;
            continue;
        }

        if (str[i] == '\"') {
            i++;
            while (str[i] && str[i] != '\"') {
                if (str[i] == '$') {
                    i++;
                    if (!handle_dollar_sign(str, &i, &result_chars))
                        return (ft_lstclear(&result_chars, free), false);
                    continue;
                }
                new_node = ft_lstnew(ft_substr(str, i, 1));
                (*get_char_count())++;
                if (!new_node)
                    return (ft_lstclear(&result_chars, free), pe("malloc failed"), false);
                ft_lstadd_back(&result_chars, new_node);
                i++;
            }
            i++;
            continue;
        }

        int wildcard_len = get_wildcard_len(str + i);
        if (wildcard_len > 0) {
            if (!expand_wildcard(str + i, wildcard_len, &result_chars))
                return (ft_lstclear(&result_chars, free), false);
            i += wildcard_len;
            continue;
        }

        if (str[i] == '$') {
            i++;
            if (!handle_dollar_sign(str, &i, &result_chars))
                return (ft_lstclear(&result_chars, free), false);
            continue;
        }

        new_node = ft_lstnew(ft_substr(str, i, 1));
        (*get_char_count())++;
        if (!new_node)
            return (ft_lstclear(&result_chars, free), pe("malloc failed"), false);
        ft_lstadd_back(&result_chars, new_node);

        i++;
    }

    free(node->value);
    node->value = strlst_to_str(result_chars);
    ft_lstclear(&result_chars, free);

    return true;
}

/*
int main() {
    t_ast_node node;
    node.type = AST_COMMAND;
    node.value = ft_strdup("echo '$PATH': paaath: \"$gfweio $PATH\"");
    node.redirects = NULL;
    interpret_command_string(&node);
    printf("result: %s\n", node.value);
    free(node.value);
    return 0;
}
*/
