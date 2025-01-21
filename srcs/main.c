/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:34:50 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 13:34:15 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	if (env && !initialise_env(env))
		destroy_minishell(EXIT_FAILURE);
	if (argc >= 2)
		minishell_non_interactive_argument(argv + 1, argc - 1);
	else if (isatty(STDIN_FILENO))
		minishell_interactive();
	else
		minishell_non_interactive();
	destroy_minishell(get_shell()->exit_status);
}
