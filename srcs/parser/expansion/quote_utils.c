/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:59:17 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 15:31:28 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool skip_quotes(const char *str, size_t *i) {
    if (str[*i] == '\'' && !is_escaped(str, *i)) {
        (*i)++;
        while (str[*i] && (str[*i] != '\'' || is_escaped(str, *i)))
            (*i)++;
        (*i)++;
        return true;
    }
    if (str[*i] == '\"' && !is_escaped(str, *i)) {
        (*i)++;
        while (str[*i] && (str[*i] != '\"' || is_escaped(str, *i)))
            (*i)++;
        (*i)++;
        return true;
    }
    return false;
}

bool skip_safe_quotes(const char* str, size_t* i, t_list** str_list) {
    size_t start_i;

    start_i = *i;
    if (str[*i] == '\'' && !is_escaped(str, *i)) {
        (*i)++;
        while (str[*i] && (str[*i] != '\'' || is_escaped(str, *i)))
            (*i)++;
        (*i)++;
        add_str_to_result(str, &start_i, str_list, *i - start_i);
        return true;
    }
    if (str[*i] == '\"' && !is_escaped(str, *i)) {
        (*i)++;
        while (str[*i] && (str[*i] != '\"' || is_escaped(str, *i)))
            (*i)++;
        (*i)++;
        add_str_to_result(str, &start_i, str_list, *i - start_i);
        return true;
    }
    return false;
}
