/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:36:00 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 13:14:33 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "libft.h"
# include <stdbool.h>

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

bool					lex_tokens(const char *input, t_list **tokens);

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

char*					expand_string(const char* str);

int						get_wildcard_len(const char *str);

bool					expand_wildcard(const char *old_pattern,
							size_t pattern_len, t_list **list);

bool					is_wildcard_separator(const char c);

char					*expand_env_vars(const char *input, size_t len);

bool					get_files_in_dir(const char *path, t_list **list,
							size_t *amount);

size_t						*get_char_count(void);

bool					handle_dollar_sign(const char *str, int *i,
							t_list **result_chars);

bool					parse_redirect_to_token(t_list **tokens,
							const char *str, t_token_type redirect_type,
							size_t *i);

t_token_type			is_redirect(const char *str);

t_token_type			get_token_type(const char *str, size_t i, bool in_quote);

bool					add_token(t_list **tokens, t_token_type type,
							char *value);

bool					parse_redirects_for_parenteses(t_list **tokens,
							t_ast_node *parentheses_node);

t_ast_node				*parse_command(t_list **tokens);

bool					handle_tilde_expansion(int *i, t_list **result_chars);

bool					add_char_to_result(const char *str, size_t *i,
							t_list **result_chars);

bool					is_empty_string_token(t_token *token);

bool	parse_redirect(t_list **redirects, const char *str,
		t_token_type redirect_type, size_t *i);

char	*strlst_to_str(t_list *result_chars);

char	*ft_unescape_string(char *str);

char	**split_quotes(char const *str);

char* filter_and_get_redirects(const char* input, t_list** redirects);

bool is_escaped(const char *str, size_t i);

bool skip_quotes(const char *str, size_t *i);

char* expand_wildcars(const char *str);
#endif
