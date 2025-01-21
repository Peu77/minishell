/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:08:16 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 17:26:54 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <readline/readline.h>
#include <stdlib.h>

void	destroy_minishell(int status)
{
	gc_list_clear(&get_shell()->env, free_env_entry);
	rl_clear_history();
	gc_close_fds();
	gc_free();
	exit(status);
}
