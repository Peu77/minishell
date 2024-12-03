/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:34:29 by eebert            #+#    #+#             */
/*   Updated: 2024/12/03 15:00:52 by eebert           ###   ########.fr       */
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
    t_token* node;

    node = malloc(sizeof(t_token));
    if(!node)
        return false;

    node->type = type;
    node->value = value;
    ft_lstadd_back(tokens, ft_lstnew(node));
    return true;
}

// TODO: handle memory leaks
static int parse_redirect(t_list** tokens, const char* str, t_token_type redirect_type)
{
    t_redirect* redirect;
    t_token* node;
    int i;

    i = 0;
    redirect = malloc(sizeof(t_redirect));
    node = malloc(sizeof(t_token));
    if(!redirect || !node)
        return (free(redirect), free(node), -1);
    redirect->fd_left = 0;
    redirect->fd_right = 0;
    redirect->file = NULL;
    if(ft_isdigit(*str))
    {
        redirect->fd_left = ft_atoi(str);
        while(ft_isdigit(str[i]))
            i++;
    }

    i++;

    if(str[i] == 0) {
        pe("parse error near `newline'");
        return (free(redirect),free(node), -1);
    }

    if(str[i] == '&') {
        // TODO: possbile sigsegv if no number is provided
        i++;
        redirect->fd_right = ft_atoi(str + i);
        while(ft_isdigit(str[i]))
            i++;
    }else {
        // in case if filename is provided
        while (str[i] && ft_isspace(str[i]))
            i++;

        //TODO: handle special case if ' &1' is provided

        int len_until_space = 0;
        while(str[i + len_until_space] && !ft_isspace(str[i + len_until_space]))
            len_until_space++;

        redirect->file = ft_substr(str, i, len_until_space);
        i += len_until_space;
    }

    node->type = redirect_type;
    node->data = redirect;
    ft_lstadd_back(tokens, ft_lstnew(node));

    return i;
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

            add_token(tokens, TOKEN_STRING, ft_substr(input, i + 1, string_i));
            i += string_i + 2;
        }

        type = get_token_type(input + i);
        if(type == TOKEN_REDIRECT_APPEND || type == TOKEN_REDIRECT_INPUT || type == TOKEN_REDIRECT_OUTPUT)
        {
            i += parse_redirect(tokens, input + i, type);
            continue;
        }

        if(type != TOKEN_STRING) {
            add_token(tokens, type, NULL);
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
            add_token(tokens, TOKEN_STRING, ft_substr(input, i, string_i));
            i += string_i;
        }
    }
}



/*
 * compile with: cc lexer.c ../../libft/libft.a ../error/error.c -I ../../includes && ./a.out
 *
 */


/*
int main() {
    t_list* tokens = NULL;
    char* input = "1< test echo hello 1>&1 filename test && echo 'test && echo () test > || test' () world";

    lex_tokens(input, &tokens);

    print_tokens(tokens);

    t_list* tokens2 = NULL;
    char* input_redirect = " >&4234fwef dffew";
    int offset = parse_redirect(&tokens2, input_redirect, TOKEN_REDIRECT_OUTPUT);
    printf("offset: %d\n", offset);
    printf("token type: %d\n", ((t_token*)tokens2->content)->type);
    printf("fd_left: %d\n", ((t_redirect*)((t_token*)tokens2->content)->data)->fd_left);
    printf("fd_right: %d\n", ((t_redirect*)((t_token*)tokens2->content)->data)->fd_right);
    printf("file: %s\n", ((t_redirect*)((t_token*)tokens2->content)->data)->file);

    return 0;
}
*/
