/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:36:00 by eebert            #+#    #+#             */
/*   Updated: 2025/01/14 15:34:27 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "libft.h"
# include <stdbool.h>

#define MAX_VAR_LEN 256

typedef enum e_token_type
{
	TOKEN_NONE = -1,
	TOKEN_STRING = 0,
	TOKEN_PIPE = 1,
	TOKEN_SEMICOLON = 2,
	TOKEN_REDIRECT_INPUT = 3,
	TOKEN_REDIRECT_OUTPUT = 4,
	TOKEN_PARENTHESES_OPEN = 5,
	TOKEN_PARENTHESES_CLOSE = 6,
	TOKEN_END = 7,
	TOKEN_AND = 8,
	TOKEN_OR = 9,
	TOKEN_REDIRECT_APPEND = 10,
	TOKEN_REDIRECT_INPUT_APPEND = 11
}						t_token_type;

typedef struct s_redirect
{
	int					fd_left;
	int					fd_right;
	char				*file;
	t_token_type		type;
}						t_redirect;

typedef struct e_token
{
	char				*value;
	void				*data;
	t_token_type		type;
}						t_token;

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_SEMICOLON,
	AST_PARENTHESES,
	AST_AND,
	AST_OR
}						t_ast_type;

typedef struct s_ast_node
{
	char				*value;
	t_ast_type			type;
	t_list				*redirects;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_list_data
{
	t_list				**list;
	size_t				count;
}						t_list_data;

t_ast_node				*parse(char *input);

bool					lex_tokens(char *input, t_list **tokens);

# define PARSE_ERROR ((void *)-1)

t_list					*parse_redirects_tokens_to_tree(t_list **redirects,
							t_list *tokens);

bool					is_redirect_token(t_token_type type);

void					free_redirect(void *redirect);

t_redirect				*create_redirect(int fd_left, int fd_right,
							t_token_type type, char *file);

t_ast_node				*create_ast_node(t_ast_type type, char *value,
							t_list *redirects);

void					free_ast_node(void *content);

void					free_token(void *content);

t_token					*create_token(t_token_type type, char *value,
							void *data);

void					print_tokens(t_list *tokens);

void					print_ast_node(t_ast_node *node, int depth);

void					print_ast_type(const t_ast_type type);

bool					interpret_command_string(t_ast_node *node);

int						get_wildcard_len(const char *str);

bool						expand_wildcard(const char *old_pattern, size_t pattern_len, t_list **list);

bool is_wildcard_separator(const char c);

char *expand_env_vars(const char *input, size_t len);

bool get_files_in_dir(const char* path, t_list **list, size_t* amount);

int* get_char_count();

bool handle_dollar_sign(const char *str, int *i, t_list **result_chars);
#endif
