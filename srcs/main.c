#include "../includes/minishell.h"

int main(void)
{
	pe("WELCOME TO MINISHELL");
	char *user_prompt;

	while (1)
	{
		user_prompt = NULL;
		if(!get_user_prompt(&user_prompt))
			return (EXIT_FAILURE);
		//1 . STEP 1 PARSING
		//2. STEP 2 . EXECUTION
		//PIPING
		pipe_monitor(user_prompt);
		free(user_prompt);		// ctrl + d / ctrl + c / ctrl + /	}
	}
	return (EXIT_SUCCESS);
}

