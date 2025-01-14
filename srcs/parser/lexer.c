/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:34:29 by eebert            #+#    #+#             */
/*   Updated: 2025/01/12 10:41:55 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include "parse.h"
#include "libft.h"
#include <stdbool.h>
#include <stdio.h>

static t_token_type is_redirect(const char *str) {
    int i;

    i = 0;
    while (str[i] && ft_isdigit(str[i]))
        i++;

    if (ft_strncmp(str + i, "<<", 2) == 0)
        return TOKEN_REDIRECT_INPUT_APPEND;
    if (ft_strncmp(str + i, ">>", 2) == 0)
        return TOKEN_REDIRECT_APPEND;
    if (*(str + i) == '<')
        return TOKEN_REDIRECT_INPUT;
    if (*(str + i) == '>')
        return TOKEN_REDIRECT_OUTPUT;
    return TOKEN_NONE;
}

static t_token_type get_token_type(const char *str, bool in_quote) {
    if (in_quote)
        return TOKEN_STRING;
    if (ft_strncmp(str, "&&", 2) == 0)
        return TOKEN_AND;
    if (ft_strncmp(str, "||", 2) == 0)
        return TOKEN_OR;
    if (*str == '|')
        return TOKEN_PIPE;
    if (*str == ';')
        return TOKEN_SEMICOLON;

    const t_token_type redirect = is_redirect(str);
    if (redirect != TOKEN_NONE)
        return redirect;
    if (*str == '(')
        return TOKEN_PARENTHESES_OPEN;
    if (*str == ')')
        return TOKEN_PARENTHESES_CLOSE;
    if (*str == '\0')
        return TOKEN_END;
    return TOKEN_STRING;
}

static bool add_token(t_list **tokens, t_token_type type, char *value) {
    t_token *new_token;
    t_list *new_node;

    new_token = create_token(type, value, NULL);
    if (!new_token)
        return false;

    new_node = ft_lstnew(new_token);
    if (!new_node)
        return (free(new_token), false);
    ft_lstadd_back(tokens, new_node);
    return true;
}

bool lex_tokens(char *input, t_list **tokens) {
    t_token_type type;
    const size_t len = ft_strlen(input);
    size_t i;
    int string_i;
    char start_quote = 0;
    bool in_quote = false;

    i = 0;
    string_i = 0;
    while (i < len) {
        type = get_token_type(input + i, in_quote);

        if (is_redirect_token(type)) {
            if (!parse_redirect_to_token(tokens, input, type, &i))
                break;
            continue;
        }

        if (type != TOKEN_STRING) {
            if (!add_token(tokens, type, NULL))
                break;
            if (type == TOKEN_END)
                break;
            i++;
            // skip second character if it's a double character token
            if (type >= TOKEN_AND) {
                i++;
            }
            continue;
        }

        string_i = 0;

        while (input[i + string_i]) {
            if (start_quote == 0)
                in_quote = false;

            if (start_quote == input[i + string_i] && in_quote) {
                start_quote = 0;
            } else if ((input[i + string_i] == '\'' || input[i + string_i] == '\"') && start_quote == 0) {
                in_quote = true;
                start_quote = input[i + string_i];
            }

            type = get_token_type(input + i + string_i, in_quote);
            if (type != TOKEN_STRING)
                break;
            string_i++;
        }
        if (start_quote == 0)
            in_quote = false;
        if (string_i > 0) {
            if (!add_token(tokens, TOKEN_STRING, ft_substr(input, i, string_i)))
                break;
            i += string_i;
        }
    }

    if (i != len) {
        ft_lstclear(tokens, free_token);
        return false;
    }

    if (in_quote) {
        ft_lstclear(tokens, free_token);
        return pe("parse error near `\\n'"), false;
    }

    print_tokens(*tokens);
    return true;
}


/*
 * compile with: cc lexer.c ../../libft/libft.a ../error/error.c redirects.c token_utils.c -I ../../includes && ./a.out
 *
 */


/*
int main() {
    t_list* tokens = NULL;
    char* input = "1< test echo hello 1>&1 filename test && echo 'test && echo () test > || test' () world";

    lex_tokens(input, &tokens);
    return 0;
}
*/
