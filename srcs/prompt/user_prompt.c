/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:06:59 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/14 14:25:06 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_user_prompt(char **user_prompt)
{
	*user_prompt = readline(">>>> Minishell>$ ");
	if (*user_prompt == NULL)
	{
		clear_history();
		printf("exit\n");
		gc_free_ptr(*user_prompt);
		return (0);
	}
	add_history(*user_prompt);
	return (1);
}
