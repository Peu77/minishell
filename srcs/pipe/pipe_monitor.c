#include "../../includes/minishell.h"

void pipe_monitor(char *user_prompt)
{
    t_pipe *pipe = malloc(sizeof(t_pipe));
	t_command *command = NULL;
    if (!user_prompt || *user_prompt == '\0')
    {
        return;
    }
    if (!pipe)
    {
        perror("Failed to allocate memory for pipe structure");
        return;
    }
    initialise_pipe(&pipe, &command, user_prompt);
    printf("Number of pipes: %d\n", pipe->number_pipe);
    printf("Number of commands: %d\n", pipe->number_command);

    if (pipe->number_pipe == 0)
        execution_monitor(command);
    else
        printf("Too many pipes for the moment (building)\n");

    free(pipe);
}

