/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greeting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:03 by eebert            #+#    #+#             */
/*   Updated: 2025/01/26 14:01:50 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <minishell.h>
#include <unistd.h>

static double get_random_number() {
    const int random_fd = open("/dev/random", O_RDONLY);
    if (random_fd < 0)
        return (pe("Failed to open /dev/random"), -1.0);

    unsigned int random_value;
    if (read(random_fd, &random_value, sizeof(random_value)) < 0)
        return (perror("Failed to read from /dev/random"), close(random_fd), -1.0);
    close(random_fd);
    return (double) random_value / ((double) UINT_MAX);
}

static void send_banner(void) {
    const char *banner = "██████   ██████  ███              ███          █████               ████  ████\n"
            "░░██████ ██████  ░░░              ░░░          ░░███               ░░███ ░░███\n"
            "░███░█████░███  ████  ████████   ████   █████  ░███████    ██████  ░███  ░███\n"
            "░███░░███ ░███ ░░███ ░░███░░███ ░░███  ███░░   ░███░░███  ███░░███ ░███  ░███\n"
            "░███ ░░░  ░███  ░███  ░███ ░███  ░███ ░░█████  ░███ ░███ ░███████  ░███  ░███\n"
            "░███      ░███  ░███  ░███ ░███  ░███  ░░░░███ ░███ ░███ ░███░░░   ░███  ░███\n"
            "█████     █████ █████ ████ █████ █████ ██████  ████ █████░░██████  █████ █████\n"
            "░░░░░     ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░ ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░\n";
    printf("%s\n", banner);
}

void send_greeting(void) {
    const char *greetings[] = {
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
    const int total_greetings = sizeof(greetings) / sizeof(greetings[0]);
    const double random_number = get_random_number();
    const char *user;

    if (random_number < 0)
        return;
    user = get_env_value("USER");
    if (!user)
        user = "User";

    int index = (int) (random_number * total_greetings);
    if (index >= total_greetings)
        index = total_greetings - 1;
    send_banner();
    printf("👹 %s%s, %s%s 👹\n\n",GREEN, greetings[index], user, RESET);
}
