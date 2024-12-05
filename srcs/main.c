#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	pe("WELCOME TO MINISHELL");
	char *user_prompt;
	(void)argc;
    (void)argv;
	t_pipe *pipe = malloc(sizeof(t_pipe));
	t_command *command = NULL;
	while (1)
	{
		user_prompt = NULL;
		if(!get_user_prompt(&user_prompt))
			return (EXIT_FAILURE);
		//1 . STEP 1 PARSING
		//2. STEP 2 . EXECUTION
		//PIPING

	    if(!initialise_monitor(&pipe, &command, user_prompt, envp))
			return 0;
		pipe_monitor(pipe, command, user_prompt);
		free(user_prompt);		// ctrl + d / ctrl + c / ctrl + /	}
		free_command(&command);
	}
	return (EXIT_SUCCESS);
}

