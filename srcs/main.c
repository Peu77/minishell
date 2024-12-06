#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	pe("WELCOME TO MINISHELL");
	char *user_prompt;
	(void)argc;
    (void)argv;
	while (1)
	{
		t_pipe *pipe = malloc(sizeof(t_pipe));
		t_command *command = NULL;
		user_prompt = NULL;
		if(!get_user_prompt(&user_prompt))
			return free_all(&pipe, &command);
		//1 . STEP 1 PARSING
		//2. STEP 2 . EXECUTION
		//PIPING

	    if(!initialise_monitor(&pipe, &command, user_prompt, envp))
			return free_all(&pipe, &command);
		pipe_monitor(pipe, command, user_prompt);
		free(user_prompt);		// ctrl + d / ctrl + c / ctrl + /	}
		free_all(&pipe, &command);
	}
	return (EXIT_SUCCESS);
}

