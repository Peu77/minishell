/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:34:29 by eebert            #+#    #+#             */
/*   Updated: 2024/12/08 11:33:02 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include "parse.h"
#include "libft.h"
#include <stdbool.h>
#include <stdio.h>

static t_token_type is_redirect(const char* str) {
    int i;

    i = 0;
    while (str[i] && ft_isdigit(str[i]))
        i++;

    if(ft_strncmp(str + i, ">>", 2) == 0)
        return TOKEN_REDIRECT_APPEND;
    if(*(str + i) == '<')
        return TOKEN_REDIRECT_INPUT;
    if(*(str + i) == '>')
        return TOKEN_REDIRECT_OUTPUT;
    return TOKEN_NONE;
}

static t_token_type get_token_type(const char* str)
{
    if(ft_strncmp(str, "&&", 2) == 0)
        return TOKEN_AND;
    if(ft_strncmp(str, "||", 2) == 0)
        return TOKEN_OR;
    if(*str == '|')
        return TOKEN_PIPE;
    if(*str == ';')
        return TOKEN_SEMICOLON;

    const t_token_type redirect = is_redirect(str);
    if(redirect != TOKEN_NONE)
        return redirect;
    if(*str == '(')
        return TOKEN_PARENTHESES_OPEN;
    if(*str == ')')
        return TOKEN_PARENTHESES_CLOSE;
    if(*str == '\0')
        return TOKEN_END;
    return TOKEN_STRING;
}

static bool add_token(t_list** tokens, t_token_type type, char* value)
{
    t_token* new_token;
    t_list* new_node;

    new_token = malloc(sizeof(t_token));
    if(!new_token)
        return false;

    new_token->type = type;
    new_token->value = value;
    new_node = ft_lstnew(new_token);
    if(!new_node)
        return (free(new_token), false);
    ft_lstadd_back(tokens, new_node);
    return true;
}

// TODO: handle memory leaks
static bool parse_redirect_to_token(t_list** tokens, const char* str, t_token_type redirect_type, size_t* i)
{
    t_redirect* redirect;
    t_token* token;
    t_list* new_node;

    redirect = malloc(sizeof(t_redirect));
    token = malloc(sizeof(t_token));
    if(!redirect || !token)
        return (free(redirect), free(token), false);
    redirect->fd_left = 0;
    redirect->fd_right = 0;
    redirect->file = NULL;
    redirect->type = redirect_type;
    if(ft_isdigit(str[*i]))
    {
        redirect->fd_left = ft_atoi(str);
        while(ft_isdigit(str[*i]))
            (*i)++;
    }

    // skip redirect char like <, >, >>
    (*i)++;
    if(redirect_type == TOKEN_REDIRECT_APPEND)
        (*i)++;

    if(str[*i] == 0 || (str[*i] == '&' && str[*i + 1] == 0))
        return (pe("parse error near `\\n'"), free(redirect),free(token), false);

    if(str[*i] == '&') {
        (*i)++;
        redirect->fd_right = ft_atoi(str + *i);
        while(str[*i] && ft_isdigit(str[*i]))
            (*i)++;

    }else {
        // in case if filename is provided
        while (str[*i] && ft_isspace(str[*i]))
            (*i)++;

        int filename_len = 0;
        while(str[*i + filename_len] && !ft_isspace(str[*i + filename_len]))
            filename_len++;

        if(filename_len == 0)
            return (pe("parse error near `\\n'"), free(redirect),free(token), false);


        redirect->file = ft_substr(str, *i, filename_len);
        if(redirect->file == NULL)
            return (free(redirect),free(token), false);
        *i += filename_len;
    }

    token->value = NULL;
    token->type = redirect_type;
    token->data = redirect;
    new_node = ft_lstnew(token);
    if(!new_node)
        return (free_redirect(redirect),free(token), false);
    ft_lstadd_back(tokens, new_node);

    return true;
}


static void print_tokens(t_list* tokens){

    t_token* node;

    while(tokens)
    {
        node = tokens->content;

        if(node->type == TOKEN_REDIRECT_OUTPUT || node->type == TOKEN_REDIRECT_INPUT || node->type == TOKEN_REDIRECT_APPEND)
            printf("TOKEN_REDIRECT: %d, %d, %d, %s\n", node->type, ((t_redirect*)node->data)->fd_left, ((t_redirect*)node->data)->fd_right, ((t_redirect*)node->data)->file);
        else if(node->type == TOKEN_STRING)
            printf("TOKEN_STRING: %s\n", node->value);
        else
            printf("TOKEN: %d\n", node->type);
        tokens = tokens->next;
    }
}

bool parse_single_quote(char *input, size_t *i, t_list** tokens)
{
    int j;
    char* sub_str;
    bool add_token_result;

    j = 0;
    while(input[*i + j] && input[*i + j] != '\'')
        j++;

    if(input[*i + j] != '\'')
    {
        pe("Error: missing closing quote");
        return false;
    }
    sub_str = ft_substr(input, *i, j);
    if(!sub_str)
        return false;
    add_token_result = add_token(tokens, TOKEN_STRING, sub_str);
    if(!add_token_result)
        return (free(sub_str),false);
    *i += j + 1;
    return true;
}

// TODO: handle $var
bool lex_tokens(char *input, t_list** tokens)
{
    t_token_type type;
    const size_t len = ft_strlen(input);
    size_t i;
    int string_i;

    i = 0;
    string_i = 0;
    while(i < len)
    {
        if(ft_isspace(input[i]))
        {
            i++;
            continue;
        }
        if(input[i] == '\'') {
            i++;
            if(!parse_single_quote(input, &i, tokens))
                break;
        }

        type = get_token_type(input + i);
        if(is_redirect_token(type))
        {
            if(!parse_redirect_to_token(tokens, input, type, &i))
                break;
            continue;
        }

        if(type != TOKEN_STRING) {
            if(!add_token(tokens, type, NULL))
                break;
            if(type == TOKEN_END)
                break;
            i++;
            // skip second character if it's a double character token
            if(type >= TOKEN_AND) {
                i++;
            }
            continue;
        }

        string_i = 0;
        while(type == TOKEN_STRING && input[i + string_i] && input[i + string_i] != '\'')
        {
            string_i++;
            type = get_token_type(input + i + string_i);
        }
        if(string_i > 0)
        {
            if(!add_token(tokens, TOKEN_STRING, ft_substr(input, i, string_i)))
                break;
            i += string_i;
        }
    }

    if(i != len) {
        ft_lstclear(tokens, free_token);
        return false;
    }

    print_tokens(*tokens);
    return true;
}



/*
 * compile with: cc lexer.c ../../libft/libft.a ../error/error.c redirects.c -I ../../includes && ./a.out
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


