/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:43:05 by eebert            #+#    #+#             */
/*   Updated: 2025/01/27 14:09:20 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_nb_len(int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static size_t	get_prompt_length(const char *user, int exit_code)
{
	size_t	len;

	len = 0;
	len += ft_strlen(GREEN);
	len += ft_strlen(user);
	len += ft_strlen("\033[0m \033[1;34m→\033[0m \033[1;33mMinishell\033[0m");
	len += ft_strlen(GREEN) + 1;
	len += ft_nb_len(exit_code) + 1;
	len += ft_strlen(RESET);
	len += 3;
	return (len);
}

static void	append_exit(char *prompt, int exit_code, size_t len)
{
	char	*nb_str;
	char	*exit_color;

	if (exit_code == 0)
		exit_color = "\033[1;32m";
	else
		exit_color = "\033[1;31m";
	if (exit_code != 0)
	{
		ft_strlcat(prompt, " ", len);
		ft_strlcat(prompt, exit_color, len);
		nb_str = gc_add(ft_itoa(exit_code));
		ft_strlcat(prompt, nb_str, len);
		ft_strlcat(prompt, " ", len);
		gc_free_ptr(nb_str);
	}
}

char	*create_prompt(void)
{
	const int	exit_code = get_shell()->exit_status;
	size_t		len;
	char		*user;
	char		*prompt;

	user = get_env_value("USER");
	if (!user)
		user = "User";
	len = get_prompt_length(user, exit_code);
	prompt = gc_add(ft_calloc(len + 1, sizeof(char)));
	ft_strlcat(prompt, GREEN, len);
	ft_strlcat(prompt, user, len);
	ft_strlcat(prompt, "\033[0m \033[1;34m→\033[0m \033[1;33mMinishell\033[0m",
		len);
	append_exit(prompt, exit_code, len);
	ft_strlcat(prompt, RESET, len);
	ft_strlcat(prompt, "$ ", len);
	return (prompt);
}

int	get_user_prompt_value(char **value)
{
	char	*prompt;

	prompt = create_prompt();
	*value = readline(prompt);
	gc_free_ptr(prompt);
	if (*value == NULL)
	{
		clear_history();
		printf("exit\n");
		gc_free_ptr(*value);
		destroy_minishell(0);
	}
	add_history(*value);
	return (1);
}
