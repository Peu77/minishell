/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:35:04 by eebert            #+#    #+#             */
/*   Updated: 2025/01/27 23:36:05 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

void disable_ctrl_c_echo() {
    struct termios t;

    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void reset_terminal_settings() {
    struct termios t;

    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
