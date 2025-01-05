/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:00:04 by eebert            #+#    #+#             */
/*   Updated: 2025/01/05 16:09:44 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool handle_dollar_sign(char *str, int *i, t_list **result_chars, int* char_count) {
    int start;
    int end;
    t_list *new_node;
    char *sub_str;
    char* env_value;

    start = *i;
    end = *i;
    while (str[end] && ft_isalnum(str[end]))
        end++;
    sub_str = ft_substr(str, start, end - start);
    if (!sub_str)
        return (pe("malloc failed"), false);
    env_value = getenv(sub_str);
    if(env_value)
        env_value = ft_strdup(env_value);
    else
        env_value = ft_strdup("");
    new_node = ft_lstnew(env_value);
    free(sub_str);
    if (!new_node)
        return (ft_lstclear(result_chars, free), pe("malloc failed"), false);
    ft_lstadd_back(result_chars, new_node);
    *char_count += ft_strlen(new_node->content);
    *i = end;
    return true;
}

static char* strlst_to_str(t_list *lst, int char_count) {
    char* result;
    int cpy_offset;

    cpy_offset = 0;
    result = malloc(char_count + 1);
    if (!result)
        return (pe("malloc failed"), NULL);
    result[char_count] = '\0';
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
    int char_count;

    char_count = 0;
    result_chars = NULL;

    i = 0;
    str = node->value;
    while (str[i]) {
        if (str[i] == '\'') {
            i++;
            while (str[i] && str[i] != '\'') {
                new_node = ft_lstnew(ft_substr(str, i, 1));
                char_count++;
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
                if(str[i] == '$') {
                    i++;
                    if (!handle_dollar_sign(str, &i, &result_chars, &char_count))
                        return (ft_lstclear(&result_chars, free), false);
                    continue;
                }
                new_node = ft_lstnew(ft_substr(str, i, 1));
                char_count++;
                if (!new_node)
                    return (ft_lstclear(&result_chars, free), pe("malloc failed"), false);
                ft_lstadd_back(&result_chars, new_node);
                i++;
            }
            i++;
            continue;
        }

        if(str[i] == '$') {
            i++;
            if (!handle_dollar_sign(str, &i, &result_chars, &char_count))
                return (ft_lstclear(&result_chars, free), false);
            continue;
        }

        new_node = ft_lstnew(ft_substr(str, i, 1));
        char_count++;
        if (!new_node)
            return (ft_lstclear(&result_chars, free), pe("malloc failed"), false);
        ft_lstadd_back(&result_chars, new_node);

        i++;
    }

    free(node->value);
    printf("char_count: %d\n", char_count);
    node->value = strlst_to_str(result_chars, char_count);

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


