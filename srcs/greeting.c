/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greeting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:03 by eebert            #+#    #+#             */
/*   Updated: 2025/01/27 16:05:11 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

static double	get_random_number(void)
{
	const int		random_fd = open("/dev/random", O_RDONLY);
	unsigned int	random_value;

	if (random_fd < 0)
		return (pe("Failed to open /dev/random"), -1.0);
	if (read(random_fd, &random_value, sizeof(random_value)) < 0)
		return (perror("Failed to read from /dev/random"), close(random_fd),
			-1.0);
	close(random_fd);
	return ((double)random_value / ((double)UINT_MAX));
}

static char	**get_greetings(void)
{
	static char	*greetings[] = {
		"Hello, welcome to the minishell",
		"Hola, ¡bienvenido al minishell",
		"Bonjour, bienvenue dans le minishell",
		"Hallo, willkommen beim Minishell",
		"Ciao, benvenuto al minishell",
		"こんにちは、minishellへようこそ",
		"Привет, добро пожаловать в минишелл",
		"您好，欢迎来到minishell",
		"안녕하세요, minishell에 오신 것을 환영합니다",
		"Olá, bem-vindo ao minishell",
		"Hei, velkommen til minishell",
		"Hej, välkommen till minishell",
		"Merhaba, minishell'e hoş geldiniz",
		"Halo, selamat datang di minishell",
		"Salut, bienvenue dans le minishell",
		"שלום, ברוך הבא למינישל",
		"سلام، خوش آمدید به مینی‌شل",
	};

	return (greetings);
}

void	send_greeting(void)
{
	const double	random_number = get_random_number();
	const char		*user;
	int				index;

	if (random_number < 0)
		return ;
	user = get_env_value("USER");
	if (!user)
		user = "User";
	index = (int)(random_number * 17);
	if (index >= (17))
		index = 0;
	printf("%s\n", BANNER);
	printf("👹 %s%s, %s%s 👹\n\n", GREEN, get_greetings()[index], user, RESET);
}
