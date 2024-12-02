/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:34:29 by eebert            #+#    #+#             */
/*   Updated: 2024/12/02 19:41:50 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include <stdbool.h>
#include <stdio.h>

static t_token_type get_token_type(const char* str)
{
    if(*str == '|')
        return TOKEN_PIPE;
    if(*str == ';')
        return TOKEN_SEMICOLON;
    if(ft_strncmp(str, "&&", 2) == 0)
        return TOKEN_AND;
    if(ft_strncmp(str, "||", 2) == 0)
        return TOKEN_OR;
    if(*str == '<')
        return TOKEN_REDIRECT_INPUT;
    if(*str == '>')
        return TOKEN_REDIRECT_OUTPUT;
    if(ft_strncmp(str, ">>", 2) == 0)
        return TOKEN_REDIRECT_APPEND;
    if(*str == '(')
        return TOKEN_PARENTHESES_OPEN;
    if(*str == ')')
        return TOKEN_PARENTHESES_CLOSE;
    if(ft_isalnum(*str))
        return TOKEN_STRING;
    if(*str == '\0')
        return TOKEN_END;
    return TOKEN_NONE;
}

static bool add_token(t_list** tokens, t_token_type type, char* value)
{
    t_token* node;

    node = malloc(sizeof(t_token));
    if(!node)
        return false;

    node->type = type;
    node->value = value;
    ft_lstadd_back(tokens, ft_lstnew(node));
    return true;
}

// TODO: handle $var
void lex_tokens(char *input, t_list** tokens)
{
    t_token_type type;
    int i;
    int string_i;

    i = 0;
    string_i = 0;
    while(input[i])
    {
        if(ft_isspace(input[i]))
        {
            i++;
            continue;
        }
        string_i = 0;
        if(input[i] == '\'') {
            // TODO: handle escaped quotes
            while(input[i + string_i + 1] && input[i + string_i + 1] != '\'')
                string_i++;

            add_token(tokens, TOKEN_STRING, ft_substr(input, i + 1, string_i - 1));
            i += string_i + 2;
        }

        string_i = 0;
        while(ft_isalpha(input[i + string_i]))
            string_i++;

        if(string_i > 0)
        {
            add_token(tokens, TOKEN_STRING, ft_substr(input, i, string_i));
            i += string_i;
        }

        type = get_token_type(input + i);
        if(type != TOKEN_NONE) {
            add_token(tokens, type, NULL);
            if(type == TOKEN_END)
                break;
            i++;
            // skip second character if it's a double character token
            if(type >= TOKEN_AND) {
                i++;
            }
        }
    }
}

/*
static void print_tokens(t_list* tokens){

    t_token* node;

    while(tokens)
    {
        node = tokens->content;
        if(node->type == TOKEN_STRING)
            printf("TOKEN_STRING: %s\n", node->value);
        else
            printf("TOKEN: %d\n", node->type);
        tokens = tokens->next;
    }
}
*/

/*
 * compile with: cc lexer.c ../../libft/libft.a -I ../../includes && ./a.out
 *
 */


/*
int main() {
    t_list* tokens = NULL;
    char* input = "echo hello && echo 'test && echo () test > || test' () world";

    lex_tokens(input, &tokens);

    print_tokens(tokens);

    return 0;
}
*/