/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:04:52 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/24 17:06:17 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	convert_pointer_to_string(char *str, void *ptr)
{
	unsigned long int	nb;
	int					i;

	nb = 0;
	i = 0;
	nb = (unsigned long int)ptr;
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	str[i] = '\0';
}
