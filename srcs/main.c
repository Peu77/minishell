#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	pe("WELCOME TO MINISHELL");
	char *user_prompt;
	(void)argc;
    (void)argv;
	while (1)
	{
		//t_pipe *pipe = malloc(sizeof(t_pipe));
		t_command_test *command = NULL;
		user_prompt = NULL;
		if(!get_user_prompt(&user_prompt))
			return (1);
		//return free_all(&pipe, &command);
		//1 . STEP 1 PARSING
		//2. STEP 2 . EXECUTION
		//PIPING
		/*
	    if(!initialise_monitor(&pipe, &command, user_prompt, envp))
			return free_all(&pipe, &command);
		if(!pipe_monitor(pipe, command, user_prompt))
			return free_all(&pipe, &command);
		free(user_prompt);		// ctrl + d / ctrl + c / ctrl + /	
		free_all(&pipe, &command);
		*/
    t_ast_node  *node = parse(user_prompt);
	if(node == NULL)
	{
        printf("failed to parse\n");
        return 1;
    }
    if(node == PARSE_ERROR) {
        printf("parse error\n");
        return 1;
    }

    printf("result: %d\n", node->type);
    print_ast_node(node, 0);
	tree_monitor(node, command, envp);
    free_ast_node(node);	
	}
	return (EXIT_SUCCESS);
}
