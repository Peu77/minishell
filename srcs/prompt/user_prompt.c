/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:06:59 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 17:34:21 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_user_prompt(char **user_prompt, t_env *env)
{
	(void)(env);
    *user_prompt = readline(">>>> Minishell>$ ");

    if (*user_prompt == NULL) 
    {
        clear_history();
        printf("exit\n");
        free(*user_prompt);
        return 0;
    }
    add_history(*user_prompt);
    remove_newline(*user_prompt);
    return 1;
}
