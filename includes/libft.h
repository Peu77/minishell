/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:24:23 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/22 14:58:17 by ftapponn         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *list);
t_list				*ft_lstlast(t_list *list);
void				ft_lstadd_front(t_list **lst, t_list *new_element);
void				ft_lstadd_back(t_list **lst, t_list *new_element);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));

// char classification
int					ft_ascii(int c);
int					ft_isprint(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isspace(int c);

// char manipulation
int					ft_tolower(int c);
int					ft_toupper(int c);

// string examination
size_t				ft_strlen(const char *str);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t n);
char				*ft_strdup(const char *s1);
int					ft_atoi(const char *str);
float				ft_atof(const char *str);
double				ft_atod(const char *str);
char				*ft_itoa(int n);

// memory manipulation
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

// dynamic memory manipulation
void				*ft_calloc(size_t element_count, size_t element_size);

//Print file descriptor
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

// additional functions
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE <= 0
#  error "BUFFER_SIZE can't be <= 0"
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 50
# endif

char				*get_next_line(int fd);
char				*read_line(int fd, char *overflow_line);
char				*clean_overflow_line(char *overflow_line);
char				*clean_line(char *overflow_line);
char				*my_strjoin(char *s1, char *s2);
char				*ft_free(char **str);

// ft_printf
int					ft_printf(const char *format, ...);
int					ft_print_string(char *str);
int					ft_print_digit(int nb);
int					ft_print_hexa(unsigned int nb, int uppercase);
int					ft_print_unsigned(unsigned int nb);
int					ft_print_pointer(void *ptr);
int					ft_print_char(char nb);

#endif
