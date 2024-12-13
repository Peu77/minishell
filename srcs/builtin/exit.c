#include "../../includes/minishell.h"


long ft_atol(const char *str)
{
    long result = 0;
    int sign = 1;

    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\v' || *str == '\f')
        str++;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
        str++;
    while (ft_isdigit(*str))
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * sign);
}

int exit_command(t_command_test *command)
{
    char **cmd;
    long exit_code;
    int i = -1;

    if (command->argument == NULL)
        exit(EXIT_SUCCESS);
    cmd = ft_split(command->argument, ' ');
    if (!cmd)
        return pec(ERROR_SPLIT);
    if (cmd[1])
    {
		free_command_split(cmd);
        return pec(ERROR_TOO_ARGUMENT);
    }
    while (cmd[0][++i] != '\0')
    {
        if (!ft_isdigit(cmd[0][i]))
        {
            free_command_split(cmd);
            return pec(ERROR_DIGIT_ARGUMENT);
        }
	}
    exit_code = ft_atol(cmd[0]) % 255;
	printf("Exit code : %d \n", (int)exit_code);
    free_command_split(cmd);
    exit((int)exit_code);
}
