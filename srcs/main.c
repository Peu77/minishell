#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	pe("WELCOME TO MINISHELL");
	char *user_prompt;
	(void)argc;
    (void)argv;
	while (1)
	{
		user_prompt = NULL;
		if(!get_user_prompt(&user_prompt))
			return (EXIT_FAILURE);
		//1 . STEP 1 PARSING
		//2. STEP 2 . EXECUTION
		//PIPING
		pipe_monitor(user_prompt, envp);
		free(user_prompt);		// ctrl + d / ctrl + c / ctrl + /	}
	}
	return (EXIT_SUCCESS);
}

