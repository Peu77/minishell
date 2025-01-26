/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:43:05 by eebert            #+#    #+#             */
/*   Updated: 2025/01/26 14:13:59 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char* create_prompt(void) {
	char *user = get_env_value("USER");
	if (!user)
		user = "User";
	int exit_code = get_shell()->exit_status;
	char *prompt = gc_malloc(256);
	const char *exit_color = (exit_code == 0) ? "\033[1;32m" : "\033[1;31m";
	strcpy(prompt, "\033[1;32m");
	strcat(prompt, user);
	strcat(prompt, "\033[0m \033[1;34m→\033[0m ");
	strcat(prompt, exit_color);
	char exit_code_str[12];
	sprintf(exit_code_str, "%d", exit_code);
	strcat(prompt, exit_code_str);
	strcat(prompt, "\033[0m \033[1;34m→\033[0m \033[1;33mMinishell\033[0m$ ");
	return prompt;
}

int	get_user_prompt_value(char **value)
{
	char* prompt;

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
