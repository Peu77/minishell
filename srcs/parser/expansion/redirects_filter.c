/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_filter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:00:01 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 21:16:12 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>

char* filter_and_get_redirects(const char* input, t_list** redirects) {
    size_t i;
    t_token_type type;
    t_list* str_list;
    size_t str_len;

    *get_char_count() = 0;
    str_list = NULL;
    i = 0;
    while (input[i] != '\0') {
        str_len = 0;
       while (input[str_len] != '\0') {
            type = is_redirect(input + str_len);
           if(type != TOKEN_NONE)
               break;
            str_len++;
        }
        if (str_len > 0) {
            ft_lstadd_back(&str_list, gc_add(ft_lstnew(gc_add(ft_substr(input, i, str_len)))));
            *get_char_count() += str_len;

            i += str_len;
        }
        if(type != TOKEN_NONE && input[i] != '\0')
            parse_redirect(redirects, input, type, &i);
    }
    return strlst_to_str(str_list);
}