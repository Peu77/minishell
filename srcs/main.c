/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:34:50 by eebert            #+#    #+#             */
/*   Updated: 2025/01/17 19:16:09 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	if (env && !initialise_env(env))
		return (pec(ERROR_MALLOC), ft_lstclear(&get_shell()->env,
				free_env_entry), EXIT_FAILURE);
	if (argc >= 2)
		minishell_non_interactive_argument(argv + 1, argc - 1);
	else if (isatty(STDIN_FILENO))
		minishell_interactive();
	else
		minishell_non_interactive();
	ft_lstclear(&get_shell()->env, free_env_entry);
	rl_clear_history();
	return (get_shell()->exit_status);
}
