#include "../../includes/minishell.h"

void restore_stdout(t_command_test *command)
{
    if (dup2(command->saved_stdout, STDOUT_FILENO) == -1)
    {
        perror("dup2 restore STDOUT failed");
        exit(EXIT_FAILURE);
    }
    close(command->saved_stdout);
    command->saved_stdout = 0; // Réinitialiser après restauration.
}

int execution_monitor(t_command_test *command)
{
    char *list_builtin[NUM_BUILTINS] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
    int i = -1;
    int result = 0;

    if (command->fd_redirection)
        redirection_output(command);
    while (++i < NUM_BUILTINS)
    {
        if (ft_strncmp(command->command_name, list_builtin[i], ft_strlen(list_builtin[i]) + 1) == 0)
        {
            if (i == 0)
                result = cd(command);
            else if (i == 1)
                result = echo(command, 0);
            else if (i == 2)
                result = env(command);
            else if (i == 3)
                result = exit_command(command);
            else if (i == 4)
                result = export_command(command);
            else if (i == 5)
                result = pwd();
            else if (i == 6)
                result = unset(command);
            if (command->saved_stdout)
                restore_stdout(command);

            return result;
        }
    }
    result = prepare_execution_command(command);
    if (command->saved_stdout)
        restore_stdout(command);

    return result;
}
