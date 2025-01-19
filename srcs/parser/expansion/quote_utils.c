/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:59:17 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 13:02:15 by eebert           ###   ########.fr       */
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
